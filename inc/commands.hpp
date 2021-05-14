#pragma once

#include "message.hpp"


namespace modbus 
{

  using Command = Message;
  
  class RdCoilsCmd: public Command
  {
    public:
      constexpr static std::uint8_t kCode = 0x01u;
      constexpr static std::size_t  kRequestPduSize = 5u;
    
    public:
      RdCoilsCmd(std::uint8_t unit_id, std::size_t addr, std::size_t count);
      std::uint8_t GetCode () override { return kCode; }
      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

    //private:
      ~RdCoilsCmd() = default;

    private:
      std::size_t   _addr;           ///< Modbus data logic address
      std::size_t   _count;          ///< Data length
  };
  
  
  
  
  class RdDiscreteInputsCmd: public Command
  {
    public:
      constexpr static std::uint8_t kCode = 0x02u;
      constexpr static std::size_t  kRequestPduSize = 5u;

    public:
      RdDiscreteInputsCmd(std::uint8_t unit_id, std::size_t addr, std::size_t count);
      std::uint8_t GetCode () override { return kCode; }
      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

    //private:
      ~RdDiscreteInputsCmd() = default;

    private:
      std::size_t   _addr;           ///< Modbus data logic address
      std::size_t  _count;           ///< Data length
  };
  
  


  
    
  class RdHoldingRegsCmd: public Command
  {
     public:
      constexpr static std::uint8_t kCode = 0x03u;
      constexpr static std::size_t  kRequestPduSize = 5u;

    public:
      RdHoldingRegsCmd(std::uint8_t unit_id, std::size_t addr, std::size_t count);
      std::uint8_t GetCode () override { return kCode; }
      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

    //private:
      ~RdHoldingRegsCmd() = default;

    private:
      std::size_t   _addr;           ///< Modbus data logic address
      std::size_t  _count;           ///< Data length
  };
  
  
  
  
  
  
  class RdInputRegsCmd: public Command
  {
    public:
      constexpr static std::uint8_t kCode = 0x04u;
      constexpr static std::size_t  kRequestPduSize = 5u;

    public:
      RdInputRegsCmd(std::uint8_t unit_id, std::size_t addr, std::size_t count);
      std::uint8_t GetCode () override { return kCode; }
      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

    //private:
      ~RdInputRegsCmd() = default;

    private:
      std::size_t   _addr;           ///< Modbus data logic address
      std::size_t  _count;           ///< Data length
  };
  
  
  
  
  
  
  
  class WrCoilCmd: public Command
  {
    public:
      constexpr static std::uint8_t kCode = 0x05u;
      constexpr static std::size_t  kRequestPduSize = 5u;

    public:
      WrCoilCmd(std::uint8_t unit_id, std::uint8_t value, std::size_t addr);
      std::uint8_t GetCode () override { return kCode; }
      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

   // private:
      ~WrCoilCmd() = default;

    private:
      std::uint8_t  _value;          ///< Pointer to data
      std::size_t   _addr;           ///< Modbus data logic address
  };
  
  
  
  
  
  
  class WrRegsCmd: public Command
  {
    public:
      constexpr static std::uint8_t kCode = 0x06u;
      constexpr static std::size_t  kRequestPduSize = 5u;

    public:
      WrRegsCmd(std::uint8_t unit_id, std::uint16_t value, std::size_t addr);
      std::uint8_t GetCode () override { return kCode; }
      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

   // private:
      ~WrRegsCmd() = default;

    private:
      std::uint16_t  _value;
      std::size_t   _addr;

  };
  
  
  
  
  
  
  
  class RdExcepStatusCmd: public Command
  {
    public:
      constexpr static std::uint8_t kCode = 0x07u;
      constexpr static std::size_t  kRequestPduSize = 1u;

    public:
      RdExcepStatusCmd( std::uint8_t unit_id );
      std::uint8_t GetCode () override { return kCode; }
      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

    //private:
      ~RdExcepStatusCmd() = default;
  };
  
  
  
  
  
  
  
  
  class GetCommEventCounterCmd: public Command
  {
    public:
      constexpr static std::uint8_t kCode = 0x0Bu;
      constexpr static std::size_t  kRequestPduSize = 1u;

    public:
      GetCommEventCounterCmd( std::uint8_t unit_id );
      std::uint8_t GetCode () override { return kCode; }
      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

   // private:
      ~GetCommEventCounterCmd() = default;

  };
  
  
  
  
  
  
  
  class GetCommEventLogCmd: public Command
  {
    public:
      constexpr static std::uint8_t kCode = 0x0Cu;
      constexpr static std::size_t  kRequestPduSize = 1u;

    public:
      GetCommEventLogCmd( std::uint8_t unit_id );
      std::uint8_t GetCode () override { return kCode; }
      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

    //private:
      ~GetCommEventLogCmd() = default;
  };
  
  
  
  
  
  
  
    class WrMulCoilsCmd: public Command
    {
      public:
        constexpr static std::uint8_t kCode = 0x0Fu;

      public:
        WrMulCoilsCmd(std::uint8_t unit_id, std::uint8_t* ptr, std::size_t addr, std::size_t count);
        std::uint8_t GetCode () override { return kCode; }
        std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

      //private:
        ~WrMulCoilsCmd() = default;

      private:
        std::uint8_t*  _ptr;           ///< Pointer to data
        std::size_t   _addr;           ///< Modbus data logic address
        std::size_t  _count;           ///< Data length
    };
  
  
  
  
  
  
  
  class WrMulRegsCmd: public Command
  {
    public:
      constexpr static std::uint8_t kCode = 0x10u;

    public:
      WrMulRegsCmd(std::uint8_t unit_id, std::uint8_t* ptr, std::size_t addr, std::size_t count);
      std::uint8_t GetCode () override { return kCode; }
      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

    //private:
      ~WrMulRegsCmd() = default;

    private:
      std::uint8_t*  _ptr;           ///< Pointer to data
      std::size_t   _addr;           ///< Modbus data logic address
      std::size_t  _count;           ///< Data length
  };
  
  
  
  
  
  
  class ReportSlaveIdCmd: public Command
  {
    public:
      constexpr static std::uint8_t kCode = 0x11u;
      constexpr static std::size_t  kRequestPduSize = 1u;

    public:
      ReportSlaveIdCmd(std::uint8_t unit_id);
      std::uint8_t GetCode () override { return kCode; }
      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

   // private:
      ~ReportSlaveIdCmd() = default;
  };
  
  
  
  
  
  
  
  
  
  class MaskWrRegsCmd: public Command
  {
    public:
      constexpr static std::uint8_t kCode = 0x16u;
      constexpr static std::size_t  kRequestPduSize = 7u;

    public:
      MaskWrRegsCmd( std::uint8_t unit_id, std::size_t addr, std::uint16_t andmask, std::uint16_t ormask );
      std::uint8_t GetCode () override { return kCode; }
      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

   // private:
      ~MaskWrRegsCmd() = default;

    private:
      std::size_t   _addr;
      std::uint16_t _ormask;
      std::uint16_t _andmask;
  };
  
  
  
  
  
  
  
  class RdWrMulRegsCmd: public Command
  {
    public:
      constexpr static std::uint8_t kCode = 0x10u;

    public:
      RdWrMulRegsCmd( std::uint8_t unit_id,
                                  std::size_t read_addr,  std::size_t read_count,
                                  std::uint8_t* write_ptr, std::size_t write_addr, std::size_t write_count );

      std::uint8_t GetCode () override { return kCode; }
      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

   // private:
      ~RdWrMulRegsCmd() = default;

    private:
      std::size_t   _read_addr;
      std::size_t   _read_count;
      std::uint8_t* _write_ptr;
      std::size_t   _write_addr;
      std::size_t   _write_count;
  };
  
  
} // namespace modbus
