#pragma once
#include <functional>
#include <chrono>
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
      Error PushCommand( Command* cmd ) override;
      Error AttachUnit ( Unit* unit )   override;
      void  DetachUnit ( Unit* unit )   override;
      void  Process();
      
    private:
      enum class State { Request, Response } _state = State::Request;
      std::chrono::time_point<std::chrono::high_resolution_clock> timestamp;
      
    private:
      Unit* FindUnitById( std::uint8_t unit_id );
      void RequestStateProcess();
      void ResponseStateProcess();


    private:
      std::function< Error ( Buffer& ) > _ReadIncomingMessage;
      std::function< Error ( Buffer& ) > _StartTransaction;
      std::function< Error ( Buffer& ) > _GetTransmitBuffer;

      std::queue < Command* > _CommandQueue;
      std::vector< Unit* > _UnitList;
  };
  
} // namespace modbus


