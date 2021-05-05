#pragma once
#include "node.hpp"
#include "strategies.hpp"

namespace modbus {
  
  class Logic {
    public:
      void SetStrategy( AduStrategy* strategy ) {
        _strategy = strategy;   // TODO: сохранять во временную переменную/сбрасывать текущий запрос. Может привести к проблемам в многопоточном приложении.  
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
      AduStrategy* _strategy;
  };
  
  
} // namespace modbus
