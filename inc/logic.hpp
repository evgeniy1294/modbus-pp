#pragma once
#include "node.hpp"


namespace modbus {
  
  class Logic {
    public:
      enum class Mode { RTU, TCP, ASCII };
    
    public:
      void SetMode( Mode mode ) {
        _mode = mode;  
      }
      
      virtual Error InitiateRequest( Node* node, FunctionCode fc, std::uint8_t* ptr, std::size_t reg, std::size_t count ) = 0;
      

    private:
       struct Request {
         Node* context;               ///< Pointer to Node 
         std::uint8_t* ptr;           ///< Pointer to data
    
         // Meta
         FunctionCode fc;             ///< Modbus function code 
         std::size_t addr;            ///< Modbus data logic address
         std::size_t count;           ///< Data length
      };
    
    private:
      Mode _mode = Mode::RTU;
  };
  
  
} // namespace modbus
