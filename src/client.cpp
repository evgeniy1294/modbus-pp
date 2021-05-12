#include "client.hpp"
#include <iostream>



using namespace modbus;


Client::Client( std::function< Error ( Buffer& ) > ReadIncomingMessage,
                std::function< Error ( Buffer& ) > StartTransaction,
                std::function< Error ( Buffer& ) > GetTransmitBuffer )
{
  _ReadIncomingMessage = ReadIncomingMessage;
  _StartTransaction    = StartTransaction; 
  _GetTransmitBuffer   = GetTransmitBuffer;
}








Error Client::PushCommand( Command* cmd )
{
  _CommandQueue.push( cmd );

  return ERROR_NONE;
}






Error Client::AttachUnit( Unit* unit )
{
  _UnitList.push_back( unit );
  return ERROR_NONE;
}







void Client::DetachUnit( Unit* unit )
{
  // Удалить команды юнита из списка

  // Удалить unit из списка

  return;
}



    
    



void Client::Process()
{
  switch ( _state ) {
    case State::Request:
      RequestStateProcess();
      break;

    case State::Response:
      ResponseStateProcess();
      break;
  }
}







void Client::RequestStateProcess()
{
  Buffer buf;

  if ( !_CommandQueue.empty() )
  {
    if ( _GetTransmitBuffer(buf) == ERROR_NONE )
    {
      Command* cmd = _CommandQueue.front();
      Error err = _strategy->CreateAdu(buf, cmd );

      if ( err == ERROR_NONE )
      {
        _StartTransaction( buf );
      }
      else
      {
        _CommandQueue.pop();
        delete cmd;
      }
    }
  }
}







void Client::ResponseStateProcess()
{
  using namespace std::chrono;
  Buffer buf;

  if ( high_resolution_clock::now() < timestamp + 200ms )
  {
    if ( _ReadIncomingMessage( buf ) == ERROR_NONE )
    {
      // Extract Result
    }
  }
  else
  {
    // Start retransmission
  }

}











/*
void  Client::Process()
{
  switch ( _state ) {
    case State::Request:
      {
        if ( !_RequestQueue.empty() )
        {
          Command* cmd = _RequestQueue.front();

          if ( _GetTransmitBuffer(buf) == ERROR_NONE )
          {
            Error err = _strategy->CreateAdu( buf, cmd );
          
            if ( err == ERROR_NONE )
            {
              err = _StartTransaction( buf );
              _state = ( err == ERROR_NONE ) ? State::Response : State::Request;
            }
            else
            {
              _RequestQueue.pop();
              delete cmd;         // Кто должен убить команду?
            }
          
            if ( err != ERROR_NONE )
              std::cout << "Client:Process:Request: " << toString(err) << std::endl;
          }
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

*/



      
      
      
      
