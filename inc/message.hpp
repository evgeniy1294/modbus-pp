#pragma once

#include "error.hpp"


namespace modbus 
{
  class Message
  {
    public:
      std::uint8_t GetUnitId() { return _unit_id; }

    public:
      virtual std::uint8_t GetCode () = 0;
      virtual std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) = 0;
      
   // protected:
      virtual ~Message() = default;
    
    protected:
      std::uint8_t _unit_id;
  }; 
    
    
} // namespace message
