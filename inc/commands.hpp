#pragma once

#include "message.hpp"


namespace modbus 
{

  using Command = Message;
  
  
  class ReadCoils: public Command
  {
    public:
      constexpr static std::uint8_t kCode = 0x01u;
      constexpr static std::size_t  kRequestPduSize = 5u;
    
    public:
      ReadCoils(void* context, std::uint8_t* ptr, std::size_t addr, std::size_t count);    
      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;
      
    //private:
      ~ReadCoils() = default;
    
    private:
      std::uint8_t*  _ptr;           ///< Pointer to data
      std::size_t   _addr;           ///< Modbus data logic address
      std::size_t   _count;          ///< Data length  
  };
  
  
  
  
  class ReadDiscreteInputs: public Command
  {
    public:
      constexpr static std::uint8_t kCode = 0x02u;
      constexpr static std::size_t  kRequestPduSize = 5u;
    
    public:
      ReadDiscreteInputs(void* context, std::uint8_t* ptr, std::size_t addr, std::size_t count);    
      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;
    
    //private:
      ~ReadDiscreteInputs() = default;
    
    private:
      std::uint8_t*  _ptr;           ///< Pointer to data
      std::size_t   _addr;           ///< Modbus data logic address
      std::size_t  _count;           ///< Data length  
  };
  
  


  
    
  class ReadHoldingRegisters: public Command
  {
     public:
      constexpr static std::uint8_t kCode = 0x03u;
      constexpr static std::size_t  kRequestPduSize = 5u;
    
    public:
      ReadHoldingRegisters(void* context, std::uint8_t* ptr, std::size_t addr, std::size_t count);   
      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;
    
    //private:
      ~ReadHoldingRegisters() = default;
    
    private:
      std::uint8_t*  _ptr;           ///< Pointer to data
      std::size_t   _addr;           ///< Modbus data logic address
      std::size_t  _count;           ///< Data length   
  };
  
  
  
  
  
  
  class ReadInputRegisters: public Command
  {
    public:
      constexpr static std::uint8_t kCode = 0x04u;
      constexpr static std::size_t  kRequestPduSize = 5u;
    
    public:
      ReadInputRegisters(void* context, std::uint8_t* ptr, std::size_t addr, std::size_t count);
      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;
    
    //private:
      ~ReadInputRegisters() = default;
    
    private:
      std::uint8_t*  _ptr;           ///< Pointer to data
      std::size_t   _addr;           ///< Modbus data logic address
      std::size_t  _count;           ///< Data length   
  };
  
  
  
  
  
  
  
  class WriteSingleCoil: public Command
  {
    public:
      constexpr static std::uint8_t kCode = 0x05u;
      constexpr static std::size_t  kRequestPduSize = 5u;
      
    public:
      WriteSingleCoil(void* context, std::uint8_t value, std::size_t addr);   
      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;
    
   // private:
      ~WriteSingleCoil() = default;
    
    private:
      std::uint8_t  _value;          ///< Pointer to data
      std::size_t   _addr;           ///< Modbus data logic address
  };
  
  
  
  
  
  
  class WriteSingleRegister: public Command
  {
    public:
      constexpr static std::uint8_t kCode = 0x06u;
      constexpr static std::size_t  kRequestPduSize = 5u;
      
    public:
      WriteSingleRegister(void* context, std::uint16_t value, std::size_t addr);
      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;
    
   // private:
      ~WriteSingleRegister() = default;
    
    private:
      std::uint16_t  _value;
      std::size_t   _addr;
      
  };
  
  
  
  
  
  
  
  class ReadExceptionStatus: public Command
  {
    public:
      constexpr static std::uint8_t kCode = 0x07u;
      constexpr static std::size_t  kRequestPduSize = 1u;    
    
    public:
      ReadExceptionStatus(void* context);   
      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;
    
    //private:
      ~ReadExceptionStatus() = default;
  };
  
  
  
  
  
  
  
  
  class GetCommEventCounter: public Command
  {
    public:
      constexpr static std::uint8_t kCode = 0x0Bu;
      constexpr static std::size_t  kRequestPduSize = 1u;    
    
    public:
      GetCommEventCounter(void* context);   
      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;
    
   // private:
      ~GetCommEventCounter() = default;  
      
  };
  
  
  
  
  
  
  
  class GetCommEventLog: public Command
  {
    public:
      constexpr static std::uint8_t kCode = 0x0Cu;
      constexpr static std::size_t  kRequestPduSize = 1u;    
    
    public:
      GetCommEventLog(void* context);   
      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;
    
    //private:
      ~GetCommEventLog() = default;   
  };
  
  
  
  
  
  
  
  class WriteMultipleCoils: public Command
  {
    public:
      constexpr static std::uint8_t kCode = 0x0Fu;
    
    public:
      WriteMultipleCoils(void* context, std::uint8_t* ptr, std::size_t addr, std::size_t count);   
      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;
    
    //private:
      ~WriteMultipleCoils() = default;
    
    private:
      std::uint8_t*  _ptr;           ///< Pointer to data
      std::size_t   _addr;           ///< Modbus data logic address
      std::size_t  _count;           ///< Data length    
  };
  
  
  
  
  
  
  
  class WriteMultipleRegisters: public Command
  {
    public:
      constexpr static std::uint8_t kCode = 0x10u;
    
    public:
      WriteMultipleRegisters(void* context, std::uint8_t* ptr, std::size_t addr, std::size_t count);   
      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;
    
    //private:
      ~WriteMultipleRegisters() = default;
    
    private:
      std::uint8_t*  _ptr;           ///< Pointer to data
      std::size_t   _addr;           ///< Modbus data logic address
      std::size_t  _count;           ///< Data length  
  };
  
  
  
  
  
  
  class ReportSlaveId: public Command
  {
    public:
      constexpr static std::uint8_t kCode = 0x11u;
      constexpr static std::size_t  kRequestPduSize = 1u;    
    
    public:
      ReportSlaveId(void* context);   
      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;
    
   // private:
      ~ReportSlaveId() = default;    
  };
  
  
  
  
  
  
  
  
  
  class MaskWriteRegister: public Command
  {
    public:
      constexpr static std::uint8_t kCode = 0x16u;
      constexpr static std::size_t  kRequestPduSize = 7u;    
    
    public:
      MaskWriteRegister( void* context, std::size_t addr, std::uint16_t andmask, std::uint16_t ormask );   
      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;
    
   // private:
      ~MaskWriteRegister() = default;     
    
    private:
      std::size_t   _addr;
      std::uint16_t _ormask;
      std::uint16_t _andmask;
  };
  
  
  
  
  
  
  
  class ReadWriteMultipleRegisters: public Command
  {
    public:
      constexpr static std::uint8_t kCode = 0x10u;
    
    public:
      ReadWriteMultipleRegisters( void* context, 
                                  std::uint8_t* read_ptr,  std::size_t read_addr,  std::size_t read_count,
                                  std::uint8_t* write_ptr, std::size_t write_addr, std::size_t write_count );   
      
      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;
    
   // private:
      ~ReadWriteMultipleRegisters() = default;
    
    private:
      std::uint8_t* _read_ptr;          
      std::size_t   _read_addr;          
      std::size_t   _read_count;         
      std::uint8_t* _write_ptr;
      std::size_t   _write_addr;
      std::size_t   _write_count;
  };
  
  
  
  
} // namespace modbus
