#pragma once
#include "unit.hpp"
#include "strategies.hpp"

namespace modbus {
  
  class Logic {
    public:
      void SetStrategy( AduStrategy* strategy );

    public:
      virtual Error AttachUnit ( Unit* unit ) = 0;
      virtual void  DetachUnit ( Unit* unit ) = 0;
      virtual Error PushCommand( Command* cmd ) = 0;

     protected:
      AduStrategy* _strategy;
  };
  
  
} // namespace modbus
