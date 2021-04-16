#include "client.hpp"
#include <iostream>
#include <cstring>

using namespace modbus;


Client::Client( std::function< std::pair< std::uint8_t*, std::size_t >() > ReadIncomingMessage,
                std::function< Error ( std::uint8_t* ptr, std::size_t sz ) > StartTransaction,
                std::function< std::uint8_t*(std::size) > GetTransmitBuffer )
{
  _ReadIncomingMessage = ReadIncomingMessage;
  _StartTransaction    = StartTransaction; 
  _GetTransmitBuffer   = GetTransmitBuffer;
}





auto Client::CreateNode ( ModbusId id, Storage* storage, Observer* observer ) -> Error 
{
  _NodeList.emplace_back( id, this, storage, observer );  
  return ERROR_NONE;
}
    


    
    
    
auto  Client::InitiateRequest ( Node* node, FunctionCode fc, std::uint8_t* ptr, std::size_t reg, std::size_t count ) -> Error
{
  _RequestQueue.emplace( node, fc, ptr, reg, count );
  return ERROR_NONE;
}








void  Client::Process()
{
  switch ( _state ) {
    case State::Request:
      {
        if ( !_RequestQueue.empty() )
        {
          auto ptr = GetTransmitBuffer( 256 );
          if ( ptr ! nullptr ) {
            Request r = _RequestQueue.front();
            auto   sz = _strategy->Serialize ( ptr, 256, r );
            Error err = StartTransaction ( ptr, r );
            
            if ( err != ERROR_NONE )
            {
              std::cout << "Client::Process::Response::Error StartTransaction " << (uint32_t)err << std::endl;
            }
            else
            {
              _state = State::Response;
            }
          }
        }
        
      } break;
      
      
    case State::Response:
      ResponseHandler( );
      break;
      
  };
  
  return;
}






void Client::ResponseHandler( )
{
  auto [ ptr, sz ] = ReadIncomingMessage();
  if ( ( ptr != nullptr ) && ( sz != 0 ) )
  {       
    auto [ node, fc, ptr, reg, count ] = _RequestQueue.front();
 
    // Проверка адреса      
    if ( IsExpectedAddress( ptr, node->_id ) )    
    {
      
      if ( IsValidPacket( ptr, sz ) ) {
    
        if ( IsExpectedResponse( ptr, fc, reg, count ) ) {
    
          ExceptionId ei = Handling( ptr, sz );
    
    
          // Оповещение наблюдателя
          Error err = node->Update( fc, ei, reg, count );
          if ( err != ERROR_NONE )
          {
            std::cout << "Client::Process::Response::Error node->Update" << (uint32_t)err << std::endl;
          }
        } // IsExpectedResponse?
      } // IsValidPacket?
    } // IsExpectedAddress?
  }
  
  return;  
}







bool Client::IsValidPacket( std::uint8_t* ptr, std::size_t sz, Request& r ) {
  bool ret = false;
  
  if ( _mode == Mode::ASCII )
  {
    ret = IsValidAsciiPacket( ptr, sz, r ); 
  }
  else if ( _mode == Mode::RTU )
  {
    ret = IsValidRtuPacket( ptr, sz, r );
  }
  else
  {
    ret = IsValidTcpPacket( ptr, sz, r );
  }
  
  return ( _mode == Mode::ASCII ) ?  : IsValidModbusPacket( ptr, sz, r ); 
}





bool Client::IsValidModbusAsciiPacket( std::uint8_t* ptr, std::size_t sz, Request& r ) {
  auto [ node, r_fc, r_ptr, r_reg, r_count ] = r;
  bool ret = false;
  
  if ( sz >= 9u )  // 0x3a + NodeId(2) + ExceptionCode(2) + LCRC8(2) + 0x0D + 0x0A = 9;
  { 
    ModbusId id = ((ptr[1] - 0x30) << 4) | (ptr[2] - 0x30);
    FunctionCode fc = static_cast<FunctionCode>(*(ptr+1) & 0x7f);
  }
  
  return ret;
}





bool Client::IsValidModbusPacket( std::uint8_t* ptr, std::size_t sz, Request& r ) {
  auto [ node, r_fc, r_ptr, r_reg, r_count ] = r;
  bool ret = false;
   
  if ( sz >= 5u )       // NodeId + FunctionCode + ExceptionCode + CRC16 = 5
  {
    ModbusId id     = *ptr;
    FunctionCode fc = static_cast<FunctionCode>(*(ptr+1) & 0x7f);
    
    if ( id == node->_id ) 
    {
      if ( fc == r_fc ) {
        if ( CalculateCrc16( ptr, sz ) == 0)
        {
          ret = true;
        }
      } // fc == r_fc ? 
    } // id == node->_id ?
  } // sz >= 5u ?
   
  return ret;
}


      
      
      
      
      
      
