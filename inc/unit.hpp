#pragma once

#include "error.hpp"
#include "defs.hpp"
#include "commands.hpp"
#include "result.hpp"



namespace modbus
{
  class Unit
  {
    public:
      void SetLogic(Logic* logic) { _logic = logic; }
      std::uint8_t GetUnitId() { return _id; }

    public:
      virtual Result* Execute(Command* cmd) = 0;
      virtual void Accept (Result* result)  = 0;
      virtual MsgBuilder* GetCmdBuilder()   = 0;
      virtual MsgBuilder* GetRsltBuilder()  = 0;

    private:
      std::uint8_t _id;
      Logic* _logic;
  };
}
