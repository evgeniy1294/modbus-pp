#pragma once


#include <cstdint>


namespace modbus {
  
  
  class Logic;
  class Node;
  class Observer;
  class Storage;
  

  
  constexpr std::uint8_t  kDummyUnitId = 0;
  constexpr std::uint16_t kDummyTransactionId = 0;
  
  
  
  
  struct Buffer {
    std::uint8_t* begin   = nullptr;
    std::uint8_t* adu_end = nullptr;
    std::uint8_t* end     = nullptr;
  };
  
} // namespace modbus



