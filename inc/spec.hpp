#pragma once


#include <cstdint>


namespace modbus {
  
  using DiscreteInput   = std::uint8_t;     // Single-bit, Read-Only
  using Coil            = std::uint8_t;     // Single-bit, Read-Write
  using InputRegister   = std::uint16_t;    // 16-bit, Read-Only
  using HoldingRegister = std::uint16_t;    // 16-bit, Read-Write
  using DataAddress     = std::uint16_t; 
  using ModbusId        = std::uint8_t;

  
  enum class RegisterType { 
    Coil,                          ///< RW, 1-bit  size 
    DiscreteInput,                 ///< RO, 1-bit  size
    HoldingReg,                    ///< RW, 16-bit size
    InputReg,                      ///< RO, 16-bit size
  };
  
  
  
  
  enum class FunctionCode: std::uint8_t {
    // Bit access
    ReadCoils                       = 0x01u, 
    ReadDiscreteInputs              = 0x02u,
    WriteSingleCoil                 = 0x05u,
    WriteMultipleCoil               = 0x0Fu,
    
    // 16-bit access
    ReadInputRegister               = 0x04u,
    ReadHoldingRegisters            = 0x03u,
    WriteSingleRegister             = 0x06u,
    WriteMultipleRegisters          = 0x10u,
    ReadWriteMultipleRegisters      = 0x17u,
    MaskWriteRegister               = 0x16u,
    ReadFifoQueue                   = 0x18u,
    
    // File record access
    ReadFileRecord                  = 0x14u,
    WriteFileRecord                 = 0x15u,
    
    // Diagnostics
    ReadExceptionStatus             = 0x07u,
    Diagnostic                      = 0x08u,
    GetComEventCounter              = 0x0Bu,
    GetComEventLog                  = 0x0Cu,
    ReportServerId                  = 0x11u,
    ReadDeviceIdentification        = 0x2Bu,
  };
  
  
  
  
  
  enum class ExceptionId: std::uint8_t {
    None                                   = 0x00u,
    IllegalFunction                        = 0x01u,
    IllegalDataAddress                     = 0x02u,
    IllegalDataValue                       = 0x03u,
    ServerDeviceFailure                    = 0x04u,
    Acknowledge                            = 0x05u,
    ServerDeviceBusy                       = 0x06u,
    MemoryParityError                      = 0x08u,
    GatewayPathUnavailable                 = 0x0Au,
    GatewayTargetDeviceFailedToRespond     = 0x0Bu,
  };
  

  class Logic;
  class Subscriber;
  class NodeBase;

  struct Request {
    NodeBase* context;
    FunctionCode fc;
    std::uint8_t* ptr;
    std::size_t sz;
    void* user;
    std::uint8_t status;
  };
  
} // namespace modbus