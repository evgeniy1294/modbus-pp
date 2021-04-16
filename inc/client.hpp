#pragma once
#include <functional>
#include <utility>
#include "logic.hpp"

// Temporary include
#include <queue>

namespace modbus {
  
  class Client:: public Logic, public CommunicationInterface {
    public:
      Client( std::function< std::pair< std::uint8_t*, std::size_t >() > ReadIncomingMessage,
              std::function< Error ( std::uint8_t* ptr, std::size_t sz ) > StartTransaction,
              std::function< std::uint8_t*(std::size) > GetTransmitBuffer );
     ~Client(); 
      
    public:
      Error CreateNode ( ModbusId id, Storage* storage, Observer* observer );
      Error InitiateRequest ( Node* node, FunctionCode fc, std::uint8_t* ptr, std::size_t reg, std::size_t count ) override;
      void  Process();
      
    private:
      enum class State { Request, Response } _state = State::Request;
      
    private:
      void ResponseHandler( );
      bool Check( std::uint8_t* ptr, std::size_t sz );
      
    private:
      std::function< std::pair< std::uint8_t*, std::size_t > > _ReadIncomingMessage;
      std::function< Error ( std::uint8_t* ptr, std::size_t sz ) > _StartTransaction;
      std::function< std::uint8_t*(std::size) > _GetTransmitBuffer;
      std::queue < Request > _RequestQueue;
      std::vector< Node > _NodeList;
  };
  
} // namespace modbus


