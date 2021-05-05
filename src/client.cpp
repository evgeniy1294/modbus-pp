#include "client.hpp"
#include <iostream>
#include <cstring>

using namespace modbus;


Client::Client( std::function< Error ( AduContext& ) > ReadIncomingMessage,
                std::function< Error ( AduContext& ) > StartTransaction,
                std::function< Error ( AduContext& ) > GetTransmitBuffer )
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
          Buffer adu;
          Request r = _RequestQueue.front();
          if ( SendRequest( r ) == ERROR_NONE )
          {
            _state = State::Response;
          }
        }
        
      } break;
      
      
    case State::Response:
      ResponseHandler( );
      break;
      
  };
  
  return;
}







auto Client::SerializeRequest( Request& r ) -> Error
{
  Error err = ERROR_FAILED;
  
  auto [node, r_ptr, r_fc, r_addr, r_count] = r; 
  auto [pdu, maxsz] = _strategy->GetPduSectionRange( RequestAdu );
  std::uint16_t tid = 0;
  
  if ( (pdu != nullptr) && (maxsz != 0) )
  {
    switch( fc )
    {
      case ReadCoils: 
        [[fallthrough]]
      case ReadDiscreteInputs:  
        [[fallthrough]]
      case ReadHoldingRegisters:
        [[fallthrough]]
      case case ReadInputRegister:
        *pdu++ = static_cast< std::uint8_t >(fc);
        *pdu++ = (r_addr >> 8) & 0xffu;
        *pdu++ = r_addr & 0xffu;
        *pdu++ = (r_count >> 8) & 0xffu;
        *pdu++ = r_count & 0xffu;
        err = _strategy->CreateAdu( RequestAdu, node->id, tid, 5u );
        
        break;
      
      
      
      case WriteSingleCoil:
        std::uint8_t coil = ( ( ( byte >> ( addr & 0b111 ) ) & 0b1u ) == 0 ) ? 0x00u : 0xFFu;
        
        *pdu++ = static_cast< std::uint8_t >(fc);
        *pdu++ = (r_addr >> 8) & 0xffu;
        *pdu++ = r_addr & 0xffu; 
        *pdu++ = coil;
        *pdu++ = 0x00;
        err = _strategy->CreateAdu( RequestAdu, node->id, tid, 5u );
        
        break;
  
        
        
      case WriteSingleRegister:
        *pdu++ = static_cast< std::uint8_t >(fc);
        *pdu++ = (r_addr >> 8) & 0xffu;
        *pdu++ = r_addr & 0xffu; 
        *pdu++ = *(r_ptr+1);
        *pdu++ = *r_ptr;
        err = _strategy->CreateAdu( RequestAdu, node->id, tid, 5u );
        
        break;
      
        
      
      case WriteMultipleCoil:
      {
        std::size_t count = r_ptr + ( r_count >> 3 );
        std::size_t tail  = r_count & 0b111;
        
        *pdu++ = static_cast< std::uint8_t >(fc);
        *pdu++ = (r_addr >> 8) & 0xffu;
        *pdu++ = r_addr & 0xffu; 
        *pdu++ = (r_count >> 8) & 0xffu;
        *pdu++ = r_count & 0xffu;
        *pdu++ = count + ( ( tail != 0 ) ? 1u : 0u );
        
        for ( std::uint8_t* end = pdu+count; pdu < end; pdu++, r_ptr++)
        {
          *pdu = *r_ptr; 
        }
          
        if ( tail != 0 )
        { 
          *pdu++ = *r_ptr & (0xFF >> ( 8u - tail ));
          count++;
        }
        
        err = _strategy->CreateAdu( RequestAdu, node->id, tid, 5u + count );
        
      } break;
      
      
      
      
      case WriteMultipleRegisters:
      {
        std::uint8_t byte_count = r_count << 1u;
        std::uint8_t r_ptr_end  = r_ptr + byte_count;
        
        *pdu++ = static_cast< std::uint8_t >(fc);
        *pdu++ = (r_addr >> 8) & 0xffu;
        *pdu++ = r_addr & 0xffu; 
        *pdu++ = (r_count >> 8) & 0xffu;
        *pdu++ = r_count & 0xffu;
        *pdu++ = byte_count;
        
        while( r_ptr < r_ptr_end )
        {
          *pdu++ = *(r_ptr + 1);  // TODO: Только Little-Endian! Исправить
          *pdu++ = *r_ptr;
           r_ptr = r_ptr + 2;
        }
        
        err = _strategy->CreateAdu( RequestAdu, node->id, tid, 5u + byte_count );
        
      } break;
      
      
      
      
      
      case ReadWriteMultipleRegisters:
        
        break;
      
      case MaskWriteRegister:
        err = ERROR_NOT_IMPLEMENTED;
        break;
      
      case ReadFifoQueue:
        err = ERROR_NOT_IMPLEMENTED;
        break;
      
      case ReadFileRecord:
        err = ERROR_NOT_IMPLEMENTED;
        break;
      
      case WriteFileRecord:
        err = ERROR_NOT_IMPLEMENTED;
        break;
      
      case ReadExceptionStatus:
      case GetComEventCounter:
      case GetComEventLog:
      case ReportServerId:
        *pdu++ = static_cast< std::uint8_t >(fc);
        err = _strategy->CreateAdu( RequestAdu, node->id, tid, 0u );
        break;
      
      case Diagnostic:
        err = ERROR_NOT_IMPLEMENTED;
        break;
            
      case ReadDeviceIdentification:
        err = ERROR_NOT_IMPLEMENTED;
        break;
      
      default:
        err = SerializeUserDefinedRequest( r );
    }  
  }
  
  
  return err; 
}





      
      
      
      
