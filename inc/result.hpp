#pragma once

#include <utility>
#include "message.hpp"



namespace modbus {

  using Result = Message;


  namespace result {


    class NullResult: public Result
    {
      public:
        static constexpr std::uint8_t kCode = 0x00;

      public:
        NullResult() = default;
        std::uint8_t GetCode() override { return kCode; }
        std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override { return 0; }
    };







    class ErrorResult: public Result
    {
      public:
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


      public:
        ErrorResult( std::uint8_t function_code, ExceptionId ei );
        std::uint8_t GetCode() override { return _code; }
        std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

        ExceptionId GetExceptionId() { return _ei; }

      //private:
        ~ErrorResult() = default;

      private:
        std::uint8_t _code;
        ExceptionId  _ei;
    };




    class ReadCoils: public Result
    {
      public:
        ReadCoils( std::uint8_t unit_id, std::uint8_t* ptr, std::size_t addr, std::size_t count );
        std::uint8_t GetCode() override;
        std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

        std::pair< std::size_t , std::size_t > GetCoilsRange() { return {_addr, _count}; }
        std::uint8_t* GetValueStorage() { return _ptr; }

      //private:
        ~ReadCoils() = default;

      private:
        std::uint8_t* _ptr;
        std::size_t   _addr;
        std::size_t   _count;
    };





    class ReadDiscreteInputs: public Result
    {
      public:
        static constexpr std::uint8_t kCode = cmd::ReadDiscreteInputs::kCode;

      public:
        ReadDiscreteInputs( std::uint8_t unit_id, std::uint8_t* ptr, std::size_t addr, std::size_t count );
        std::uint8_t GetCode() override { return kCode; }
        std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

      //private:
        ~ReadDiscreteInputs() = default;

      private:
        std::uint8_t* _ptr;
        std::size_t   _addr;
        std::size_t   _count;
    };





    class ReadHoldingRegisters: public Result
    {
      public:
        static constexpr std::uint8_t kCode = cmd::ReadHoldingRegisters::kCode;

      public:
        ReadHoldingRegisters( std::uint8_t unit_id, std::uint8_t* ptr, std::size_t addr, std::size_t count );
        std::uint8_t GetCode() override { return kCode; }
        std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

      //private:
        ~ReadHoldingRegisters() = default;

      private:
        std::uint8_t* _ptr;
        std::size_t   _addr;
        std::size_t   _count;
    };





    class ReadInputRegisters: public Result
    {
      public:
        static constexpr std::uint8_t kCode = cmd::ReadInputRegisters::kCode;

      public:
        ReadInputRegisters( std::uint8_t unit_id, std::uint8_t* ptr, std::size_t addr, std::size_t count );
        std::uint8_t GetCode() override { return kCode; }
        std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

      //private:
        ~ReadInputRegisters() = default;

      private:
        std::uint8_t* _ptr;
        std::size_t   _addr;
        std::size_t   _count;
    };




    class WriteSingleCoil: public Result
    {
      public:
        static constexpr std::uint8_t kCode = cmd::WriteSingleCoil::kCode;

      public:
        WriteSingleCoil(std::uint8_t unit_id, std::uint16_t value, std::size_t addr);
        std::uint8_t GetCode () override { return kCode; }
        std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

      // private:
        ~WriteSingleCoil() = default;

      private:
        std::uint16_t  _value;
        std::size_t   _addr;
    };





    class WriteSingleRegister: public Result
    {
      public:
        constexpr static std::uint8_t kCode = cmd::WriteSingleRegister::kCode;

      public:
        WriteSingleRegister(std::uint8_t unit_id, std::uint16_t value, std::size_t addr);
        std::uint8_t GetCode () override { return kCode; }
        std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

     // private:
        ~WriteSingleRegister() = default;

      private:
        std::uint16_t  _value;
        std::size_t   _addr;

    };





    class ReadExceptionStatus: public Result
    {
      public:
        static constexpr std::uint8_t kCode = cmd::ReadExceptionStatus::kCode;

      public:
        ReadExceptionStatus( std::uint8_t unit_id, std::uint8_t status );
        std::uint8_t GetCode () override { return kCode; }
        std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

      //private:
        ~ReadExceptionStatus() = default;

      private:
        std::uint8_t status;
    };






    class WriteMultipleCoils: public Result
    {
      public:
        static constexpr std::uint8_t kCode = cmd::WriteMultipleCoils::kCode;

      public:
        WriteMultipleCoils( std::uint8_t unit_id, std::size_t addr, std::size_t count );
        std::uint8_t GetCode () override { return kCode; }
        std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

      //private:
        ~WriteMultipleCoils() = default;

      private:
        std::size_t _addr;
        std::size_t _count;
    };




    class WriteMultipleRegisters: public Result
    {
      public:
        static constexpr std::uint8_t kCode = cmd::WriteMultipleRegisters::kCode;

      public:
        WriteMultipleRegisters( std::uint8_t unit_id, std::size_t addr, std::size_t count );
        std::uint8_t GetCode () override { return kCode; }
        std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

      //private:
        ~WriteMultipleRegisters() = default;

      private:
        std::size_t _addr;
        std::size_t _count;
    };






    class MaskWriteRegister: public Result
    {
      public:
        static constexpr std::uint8_t kCode = cmd::MaskWriteRegister::kCode;

      public:
        MaskWriteRegister( std::uint8_t unit_id, std::size_t addr, std::uint16_t andmask, std::uint16_t ormask );
        std::uint8_t GetCode () override { return kCode; }
        std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

      // private:
        ~MaskWriteRegister() = default;

      private:
        std::size_t   _addr;
        std::uint16_t _ormask;
        std::uint16_t _andmask;
    };




    class ReadWriteMultipleRegisters: public Result
    {
      public:
        static constexpr std::uint8_t kCode = cmd::ReadWriteMultipleRegisters::kCode;

      public:
        ReadWriteMultipleRegisters( std::uint8_t unit_id, std::uint8_t* ptr, std::size_t count );
        std::uint8_t GetCode () override { return kCode; }
        std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

      // private:
        ~ReadWriteMultipleRegisters() = default;

      private:
        std::uint8_t* _ptr;
        std::size_t   _count;
    };


  } // namespace result
} // namespace modbus

