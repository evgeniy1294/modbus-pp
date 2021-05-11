#pragma once
#include <functional>
#include "logic.hpp"

// Temporary include
#include <queue>

namespace modbus {
  
  class Client: public Logic {
    public:
      Client( std::function< Error ( Buffer& ) > ReadIncomingMessage,
              std::function< Error ( Buffer& ) > StartTransaction,
              std::function< Error ( Buffer& ) > GetTransmitBuffer );
     ~Client(); 
      
    public:
      Error CreateNode ( ModbusId id, Storage* storage, Observer* observer );
      //Error InitiateRequest ( Node* node, FunctionCode fc, std::uint8_t* ptr, std::size_t reg, std::size_t count ) override;
      void  Process();
      
    private:
      enum class State { Request, Response } _state = State::Request;
      
    private:
      Error SerializeRequest( Buffer& buf, Request req );
      Error DeserializeResponse( Buffer& buf );
      
    private:
      std::function< Error ( Buffer& ) > _ReadIncomingMessage;
      std::function< Error ( Buffer& ) > _StartTransaction;
      std::function< Error ( Buffer& ) > _GetTransmitBuffer;
      Buffer buf;

      std::queue < Command* > _RequestQueue;
      std::vector< Node > _NodeList;
  };
  
} // namespace modbus


