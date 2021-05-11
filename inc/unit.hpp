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
      Unit ( std::uint8_t id, Logic* logic, Storage* storage, Observer* observer = nullptr );
      Result* Execute(Command* cmd);
      void Accept (Result* result);
      Error Sync( std::size_t reg, std::size_t count, Access op );

    public:
      // std::uint16_t& operator[]( const std::size_t addr );

    private:
      std::uint8_t _id;
      Logic* _logic;
      Storage* _storage;
      Observer* _observer;
  };
}
