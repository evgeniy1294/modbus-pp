#pragma once

#include <cstdint>
#include <optional>
#include <utility>

#include "spec.hpp"
#include "error.hpp"


namespace modbus {
  
 class Storage {
   public:
     virtual Error Update( std::uint8_t* ptr, std::size_t sz ) = 0;
     
   public:
     virtual Error Set( std::size_t reg, std::uint16_t value ) = 0;
     virtual std::optional< std::uint16_t > Get( std::size_t reg ) = 0;
     virtual std::pair< std::uint8_t*, FunctionCode > Data( std::size_t reg, std::size_t count, Access access ) = 0;
     
   private:
     virtual std::uint16_t& operator[]( const std::size_t addr ) = 0;
 };
  
} // namespace modbus

