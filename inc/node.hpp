#pragma once

#include <optional>
#include "spec.hpp"



namespace modbus {

  class Node {
    friend Logic;
          
    public:
      Error Sync( std::size_t reg, std::size_t   count, op );
      // Diagnostic
      Error Set ( std::size_t reg, std::uint16_t value );
      std::optional< std::uint16_t > Get( std::size_t reg );
      
    private:    
      ~Node() = default;
      Node ( ModbusId id, Logic* logic, Storage* storage, Observer* observer = nullptr );
      
    private:
      Error Update( FunctionCode fc, ExceptionId ei, std::uint8_t* ptr, std::size_t sz );
    

    private:
      Logic* _logic;
      Observer* _observer;
      Storage* _storage;
      const ModbusId _id;
  };

  
  
} // namespace modbus





