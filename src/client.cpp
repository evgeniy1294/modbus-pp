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
          Command* cmd = _RequestQueue.front();
          Error err = _strategy->CreateAdu( cmd, adu );  // adu - буфер для adu { start, end, end_adu }
          
          if ( err == ERROR_NONE )
          {
            err = Send( adu );
            _state = ( err == ERROR_NONE ) ? State::Response : State::Request;
          }
          else
          {
            _RequestQueue.pop();
            delete cmd;
          }
          
          
          if ( err != ERROR_NONE )
            std::cout << "Client:Process:Request: " << toString(err) << std::endl;   
        }
        
      } break;
      
      
    case State::Response:
      // _ReadIncomingMessage(adu)
      // if adu contain message {
        Command* cmd = _RequestQueue.front();
        auto [id, tid] = _strategy->GetAduInfo( adu );
        
        if ( command->GetNode()->id == id )  // TODO: Нужно обрабатывать как ошибку. Т.е минимальную выждать паузу и повторить запрос.
        {
          if ( _strategy->CheckAdu( adu ) == ERROR_NONE)  
          {
            auto [ptr, size] = _strategy->ExtractPdu( adu );
            Error err = cmd->HandlePdu( ptr, size );  // За обработку данных отвечает команда, она и должна оповестить ноду
            // Оповестить ноду ?
          }
          else
          {
            _state = State::Request; //  Повторный запрос. TODO: нужен счетчик   
          }
        }
      // }
        
      break;
      
  };
  
  return;
}





      
      
      
      
