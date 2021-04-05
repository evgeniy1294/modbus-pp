#pragma once

#include <optional>
#include "spec.hpp"



namespace modbus {

  class NodeBase {
    friend Logic;
    
    public:    
      NodeBase( ModbusId id, Logic* logic = nullptr, Subscriber* subscriber = nullptr );
     
      void Subscribe( Subscriber* s );
      void Unsubscribe( Subscriber* s );
      void CreateRequest( void* context, FunctionCode fc, std::uint8_t* ptr, std::size_t sz ); 
      void Connect ( Logic* logic );
      void Disconnect ( ); 
  
    private:
      virtual void Notify( void* context, FunctionCode fc, ExceptionId ei, std::uint8_t* ptr, std::size_t sz ) = 0;
    

    private:
      Logic* logic;
      Subscriber* subscriber;
      const ModbusId id;
  };

  
  
  
  

  class Node: public NodeBase {
    public:
      struct MemoryModel {
        std::size_t DiscreteInputStartAddr;
        std::size_t DiscreteInputCount;
        std::size_t CoilStartAddr;
        std::size_t CoilCount;
        std::size_t InputRegsStartAddr;
        std::size_t InputRegsCount;
        std::size_t HoldingRegsStartAddr; 
        std::size_t HoldingRegsCount;
      };
  
      Node( ModbusId id, const MemoryModel&& map, Logic* logic, Subscriber* subscriber );
      ~Node();

    public:
      std::optional< std::uint16_t > Get( std::size_t reg );
      void Set( std::size_t reg, std::uint16_t value );   // TODO: Must return Error
    
    
    private:
      void Notify( void* context, FunctionCode fc, ExceptionId ei, std::uint8_t* ptr, std::size_t sz );
      
      
    private:
      const std::size_t CoilsStartAddr;
      const std::size_t CoilsEndAddr;
      const std::size_t DiscreteInputsStartAddr;
      const std::size_t DiscreteInputsEndAddr;
      const std::size_t InputRegsStartAddr;
      const std::size_t InputRegsEndAddr;
      const std::size_t HoldingRegsStartAddr; 
      const std::size_t HoldingRegsEndAddr;
      
      Coil*            Coils;
      DiscreteInput*   DiscreteInputs;
      InputRegister*   InputRegisters;
      HoldingRegister* HoldingRegisters;
      
      Coil*            CoilsTmp;
      HoldingRegister* HoldingRegistersTmp;
  };
  
} // namespace modbus





