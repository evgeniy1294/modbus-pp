#pragma once


#include <cstdint>


namespace modbus {
  
  
  class Logic;
  class Node;
  class Observer;
  class Storage;
  
  
  
  using DiscreteInput   = std::uint8_t;     // Single-bit, Read-Only
  using Coil            = std::uint8_t;     // Single-bit, Read-Write
  using InputRegister   = std::uint16_t;    // 16-bit, Read-Only
  using HoldingRegister = std::uint16_t;    // 16-bit, Read-Write
  using DataAddress     = std::uint16_t; 
  using ModbusId        = std::uint8_t;
  
  
  constexpr std::uint8_t  kDummyUnitId = 0;
  constexpr std::uint16_t kDummyTransactionId = 0;
  
  

  
  
  
  enum class Access {
    RO,                          ///< Read access
    WO,                          ///< Write access
    RW,                          ///< Read Write access
    MW                           ///< Modify Write access
  };
  
  
  
  struct Buffer {
    std::uint8_t* begin   = nullptr;
    std::uint8_t* adu_end = nullptr;
    std::uint8_t* end     = nullptr;
  };
  
} // namespace modbus



