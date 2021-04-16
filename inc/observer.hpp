#pragma once
#include <cstdint>


namespace modbus {
  
  class Observer {
    public:
      virtual void Update( Error err, std::size_t reg, std::size_t count ) = 0;
  };
  
  
  
} // namespace modbus



