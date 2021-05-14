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
        ReadCoils( std::uint8_t unit_id, std::uint8_t* ptr, std::uint8_t* end, std::size_t addr, std::size_t count );
        std::uint8_t GetCode() override;
        std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

        std::pair< std::size_t , std::size_t > GetRange() { return {_addr, _count}; }
        std::pair< std::uint8_t*, std::uint8_t* > GetValueStorage() { return {_ptr, _end}; }

      //private:
        ~ReadCoils() = default;

      private:
        std::uint8_t* _ptr;
        std::uint8_t* _end;
        std::size_t   _addr;
        std::size_t   _count;
    };





    class ReadDiscreteInputs: public Result
    {
      public:
        ReadDiscreteInputs( std::uint8_t unit_id, std::uint8_t* ptr, std::uint8_t* end, std::size_t addr, std::size_t count );
        std::uint8_t GetCode() override;
        std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

        std::pair< std::size_t , std::size_t > GetRange() { return {_addr, _count}; }
        std::pair< std::uint8_t*, std::uint8_t* > GetValueStorage() { return {_ptr, _end}; }
        
      //private:
        ~ReadDiscreteInputs() = default;

      private:
        std::uint8_t* _ptr;
        std::uint8_t* _end;
        std::size_t   _addr;
        std::size_t   _count;
    };





    class ReadHoldingRegisters: public Result
    {
      public:
        ReadHoldingRegisters( std::uint8_t unit_id, std::uint8_t* ptr, std::uint8_t* end, std::size_t addr, std::size_t count );
        std::uint8_t GetCode() override;
        std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

        std::pair< std::size_t , std::size_t > GetRange() { return {_addr, _count}; }
        std::pair< std::uint8_t*, std::uint8_t* > GetValueStorage() { return {_ptr, _end}; }
      //private:
        ~ReadHoldingRegisters() = default;

      private:
        std::uint8_t* _ptr;
        std::uint8_t* _end;
        std::size_t   _addr;
        std::size_t   _count;
    };





    class ReadInputRegisters: public Result
    {
      public:
        ReadInputRegisters( std::uint8_t unit_id, std::uint8_t* ptr, std::uint8_t* end, std::size_t addr, std::size_t count );
        std::uint8_t GetCode() override;
        std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

        std::pair< std::size_t , std::size_t > GetRange() { return {_addr, _count}; }
        std::pair< std::uint8_t*, std::uint8_t* > GetValueStorage() { return {_ptr, _end}; }
      //private:
        ~ReadInputRegisters() = default;

      private:
        std::uint8_t* _ptr;
        std::uint8_t* _end;
        std::size_t   _addr;
        std::size_t   _count;
    };




    class WriteSingleCoil: public Result
    {
      public:
        WriteSingleCoil( std::uint8_t unit_id, std::uint8_t value, std::size_t addr );
        std::uint8_t GetCode () override;
        std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

        std::pair< std::uint16_t, std::size_t> GetValue() { return {_value, _addr}; }
      // private:
        ~WriteSingleCoil() = default;

      private:
        std::uint8_t _value;
        std::size_t _addr;
    };





    class WriteSingleRegister: public Result
    {
      public:
        WriteSingleRegister(std::uint8_t unit_id, std::uint16_t value, std::size_t addr);
        std::uint8_t GetCode () override;
        std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

        std::pair< std::uint16_t, std::size_t> GetValue() { return {_value, _addr}; }
     // private:
        ~WriteSingleRegister() = default;

      private:
        std::uint16_t  _value;
        std::size_t   _addr;

    };





    class ReadExceptionStatus: public Result
    {
      public:
        ReadExceptionStatus( std::uint8_t unit_id, std::uint8_t status );
        std::uint8_t GetCode () override;
        std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

        std::uint8_t GetStatus() { return status; }
      //private:
        ~ReadExceptionStatus() = default;

      private:
        std::uint8_t _status;
    };






    class GetCommEventCounter: public Result
    {
      public:
        GetCommEventCounter( std::uint8_t unit_id, std::uint16_t status, std::uint16_t count );
        std::uint8_t GetCode () override;
        std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;
        
        std::pair< std::uint16_t, std::uint16_t > GetResult() { return { _status, _count}; }
        
      private:
        std::uint16_t _status;
        std::uint16_t _count;
    };
    
    
    
    
    class WriteMultipleCoils: public Result
    {
      public:
        WriteMultipleCoils( std::uint8_t unit_id, std::size_t addr, std::size_t count );
        std::uint8_t GetCode () override;
        std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

        std::pair< std::uint16_t, std::uint16_t > GetResult() { return { _addr, _count}; }
        
      //private:
        ~WriteMultipleCoils() = default;

      private:
        std::size_t _addr;
        std::size_t _count;
    };




    class WriteMultipleRegisters: public Result
    {
      public:
        WriteMultipleRegisters( std::uint8_t unit_id, std::size_t addr, std::size_t count );
        std::uint8_t GetCode () override;
        std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

        std::pair< std::uint16_t, std::uint16_t > GetResult() { return { _addr, _count}; }
        
      //private:
        ~WriteMultipleRegisters() = default;

      private:
        std::size_t _addr;
        std::size_t _count;
    };






    class MaskWriteRegister: public Result
    {
      public:
        MaskWriteRegister( std::uint8_t unit_id, std::size_t addr, std::uint16_t andmask, std::uint16_t ormask );
        std::uint8_t GetCode () override;
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
        ReadWriteMultipleRegisters( std::uint8_t unit_id, std::uint8_t* ptr, std::uint8_t* end, std::size_t count );
        std::uint8_t GetCode () override;
        std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

      // private:
        ~ReadWriteMultipleRegisters() = default;

      private:
        std::uint8_t* _ptr;
        std::uint8_t* _end;
        std::size_t   _count;
    };


  } // namespace result
} // namespace modbus

