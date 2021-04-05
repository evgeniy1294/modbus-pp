#include "node.hpp" 


#include <iostream>
#include <cstring>


using namespace modbus;


Node::Node( ModbusId id, const MemoryModel&& model, Logic* logic = nullptr, Subscriber* subscriber = nullptr ):
    NodeBase { id, logic, subscriber },
    
    DiscreteInputsStartAddr( model.DiscreteInputStartAddr ),
    DiscreteInputsEndAddr  ( model.DiscreteInputStartAddr + model.DiscreteInputCount ),
    
    CoilsStartAddr         ( model.CoilStartAddr ),
    CoilsEndAddr           ( model.CoilStartAddr + model.CoilCount ),
    
    InputRegsStartAddr     ( model.InputRegsStartAddr ),
    InputRegsEndAddr       ( model.InputRegsStartAddr + model.InputRegsCount ),
    
    HoldingRegsStartAddr   ( model.HoldingRegsStartAddr ),
    HoldingRegsEndAddr     ( model.HoldingRegsStartAddr + model.HoldingRegsCount )
    
{
  DiscreteInputs      = new DiscreteInput [ model.DiscreteInputCount ];
  Coils               = new Coil [ model.CoilCount ];
  InputRegisters      = new InputRegister [ model.InputRegsCount ];
  HoldingRegisters    = new HoldingRegister [ model.HoldingRegsCount ];
  
  CoilsTmp            = new Coil [ model.CoilCount ];
  HoldingRegistersTmp = new HoldingRegister [ model.HoldingRegsCount ];
}






Node::~Node() {
  
  Disconnect( );
  
  delete DiscreteInputs;   
  delete Coils;
  delete InputRegisters;
  delete HoldingRegisters;
  
  delete CoilsTmp;
  delete HoldingRegistersTmp;
}







void Node::Notify( void* context, FunctionCode fc, ExceptionId ei, std::uint8_t* ptr, std::size_t sz ) {
  std::cout << "Node: notification accepted" << std::endl;
}





std::optional< std::uint16_t > Node::Get ( std::size_t addr ) {
  
  // Discrete Inputs?
  if ( ( addr >= DiscreteInputsStartAddr ) && ( addr < DiscreteInputsEndAddr ) ) {
    return DiscreteInputs[addr - DiscreteInputsStartAddr]; 
  }
  
  // Input Registers ?
  if ( ( addr >= InputRegsStartAddr ) && ( addr < InputRegsEndAddr ) ) {
    return InputRegisters[addr - InputRegsStartAddr]; 
  }
  
  // Coils?
  if ( ( addr >= CoilsStartAddr ) && ( addr < CoilsEndAddr ) ) {
    return Coils[addr - CoilsStartAddr]; 
  }
  
  // Holding Registers
  if ( ( addr >= HoldingRegsStartAddr ) && ( addr < HoldingRegsEndAddr ) ) {
    return HoldingRegisters[addr - HoldingRegsStartAddr]; 
  }
  
  return { /* data not found */ };
}





void Node::Set ( std::size_t addr, std::uint16_t value ) {
  // Coils?
  if ( ( addr >= CoilsStartAddr ) && ( addr < CoilsEndAddr ) ) {
    CoilsTmp[addr - CoilsStartAddr] = value; 
  }
  else
  {
    // HoldingRegisters? 
    if ( ( addr >= HoldingRegsStartAddr ) && ( addr < HoldingRegsEndAddr ) ) {
      HoldingRegistersTmp[ addr - HoldingRegsStartAddr ] = value; 
    }
  }
  
  return;
}



