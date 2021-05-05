#pragma once
#include <functional>
#include "logic.hpp"

// Temporary include
#include <queue>

namespace modbus {
  
  class Client:: public Logic, public CommunicationInterface {
    public:
      Client( std::function< Error ( AduContext& ) > ReadIncomingMessage,
              std::function< Error ( AduContext& ) > StartTransaction,
              std::function< Error ( AduContext& ) > GetTransmitBuffer );
     ~Client(); 
      
    public:
      Error CreateNode ( ModbusId id, Storage* storage, Observer* observer );
      Error InitiateRequest ( Node* node, FunctionCode fc, std::uint8_t* ptr, std::size_t reg, std::size_t count ) override;
      void  Process();
      
    private:
      enum class State { Request, Response } _state = State::Request;
      
    private:
      Error SerializeRequest( Buffer& buf, Request req );
      Error DeserializeResponse( Buffer& buf );
      
    private:
      std::function< Error ( AduContext& ) > _ReadIncomingMessage;
      std::function< Error ( AduContext& ) > _StartTransaction;
      std::function< Error ( AduContext& ) > _GetTransmitBuffer;
      
      std::queue < Request > _RequestQueue;
      std::vector< Node > _NodeList;
  };
  
} // namespace modbus


