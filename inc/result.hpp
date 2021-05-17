#pragma once

#include <utility>
#include "message.hpp"



namespace modbus {

  using Result = Message;


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
      ErrorResult( std::uint8_t unit_id, std::uint8_t function_code, ExceptionId ei );
      ErrorResult( std::uint8_t unit_id );

      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;
      Error Deserialize( std::uint8_t* pdu, std::size_t sz );

      std::uint8_t GetCode() override { return _code; }
      ExceptionId GetExceptionId() { return _ei; }

    //private:
      ~ErrorResult() = default;

    private:
      std::uint8_t _code;
      ExceptionId  _ei;
  };




  class RdCoilsRslt: public Result
  {
    public:
      RdCoilsRslt( std::uint8_t unit_id );
      RdCoilsRslt( std::uint8_t unit_id, std::uint8_t* ptr, std::uint8_t* end, std::size_t count );

      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;
      Error Deserialize( std::uint8_t* pdu, std::size_t sz );

      std::uint8_t GetCode() override;
      std::size_t GetCount() { return _count; }
      std::pair< std::uint8_t*, std::uint8_t* > GetValueStorage() { return {_ptr, _end}; }

    //private:
      ~RdCoilsRslt() = default;

    private:
      std::uint8_t* _ptr;
      std::uint8_t* _end;
      std::size_t   _count;
  };





  class RdDiscreteInputsRslt: public Result
  {
    public:
      RdDiscreteInputsRslt( std::uint8_t unit_id );
      RdDiscreteInputsRslt( std::uint8_t unit_id, std::uint8_t* ptr, std::uint8_t* end, std::size_t count );

      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;
      Error Deserialize( std::uint8_t* pdu, std::size_t sz );

      std::uint8_t GetCode() override;
      std::size_t GetCount() { return _count; }
      std::pair< std::uint8_t*, std::uint8_t* > GetValueStorage() { return {_ptr, _end}; }

    //private:
      ~RdDiscreteInputsRslt() = default;

    private:
      std::uint8_t* _ptr;
      std::uint8_t* _end;
      std::size_t   _count;
  };





  class RdHoldingRegsRslt: public Result
  {
    public:
      RdHoldingRegsRslt( std::uint8_t unit_id );
      RdHoldingRegsRslt( std::uint8_t unit_id, std::uint8_t* ptr, std::uint8_t* end, std::size_t count );

      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;
      Error Deserialize( std::uint8_t* pdu, std::size_t sz );

      std::uint8_t GetCode() override;
      std::size_t GetCount() { return _count; }
      std::pair< std::uint8_t*, std::uint8_t* > GetValueStorage() { return {_ptr, _end}; }
    //private:
      ~RdHoldingRegsRslt() = default;

    private:
      std::uint8_t* _ptr;
      std::uint8_t* _end;
      std::size_t   _count;
  };





  class RdInputRegsRslt: public Result
  {
    public:
      RdInputRegsRslt( std::uint8_t unit_id );
      RdInputRegsRslt( std::uint8_t unit_id, std::uint8_t* ptr, std::uint8_t* end, std::size_t count );

      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;
      Error Deserialize( std::uint8_t* pdu, std::size_t sz );

      std::uint8_t GetCode() override;
      std::size_t GetCount() { return _count; }
      std::pair< std::uint8_t*, std::uint8_t* > GetValueStorage() { return {_ptr, _end}; }
    //private:
      ~RdInputRegsRslt() = default;

    private:
      std::uint8_t* _ptr;
      std::uint8_t* _end;
      std::size_t   _count;
  };




  class WrCoilRslt: public Result
  {
    public:
      WrCoilRslt( std::uint8_t unit_id );
      WrCoilRslt( std::uint8_t unit_id, std::uint8_t value, std::size_t addr );

      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;
      Error Deserialize( std::uint8_t* pdu, std::size_t sz );

      std::uint8_t GetCode () override;
      std::pair< std::uint16_t, std::size_t> GetValue() { return {_value, _addr}; }
    // private:
      ~WrCoilRslt() = default;

    private:
      std::uint8_t _value;
      std::size_t _addr;
  };





  class WrRegsRslt: public Result
  {
    public:
      WrRegsRslt( std::uint8_t unit_id );
      WrRegsRslt(std::uint8_t unit_id, std::uint16_t value, std::size_t addr);

      Error Deserialize( std::uint8_t* pdu, std::size_t sz );
      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;

      std::uint8_t GetCode () override;
      std::pair< std::uint16_t, std::size_t> GetValue() { return {_value, _addr}; }
   // private:
      ~WrRegsRslt() = default;

    private:
      std::uint16_t  _value;
      std::size_t   _addr;

  };





  class RdExcepStatusRslt: public Result
  {
    public:
      RdExcepStatusRslt( std::uint8_t unit_id );
      RdExcepStatusRslt( std::uint8_t unit_id, std::uint8_t status );

      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;
      Error Deserialize( std::uint8_t* pdu, std::size_t sz );

      std::uint8_t GetCode () override;
      std::uint8_t GetStatus() { return _status; }
    //private:
      ~RdExcepStatusRslt() = default;

    private:
      std::uint8_t _status;
  };






  class GetCommEventCounterRslt: public Result
  {
    public:
      GetCommEventCounterRslt( std::uint8_t unit_id );
      GetCommEventCounterRslt( std::uint8_t unit_id, std::uint16_t status, std::uint16_t count );

      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;
      Error Deserialize( std::uint8_t* pdu, std::size_t sz );

      std::uint8_t GetCode () override;
      std::pair< std::uint16_t, std::uint16_t > GetResult() { return { _status, _count}; }

    private:
      std::uint16_t _status;
      std::uint16_t _count;
  };
    
    
    
    
  class WrMulCoilsRslt: public Result
  {
    public:
      WrMulCoilsRslt( std::uint8_t unit_id );
      WrMulCoilsRslt( std::uint8_t unit_id, std::size_t addr, std::size_t count );

      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;
      Error Deserialize( std::uint8_t* pdu, std::size_t sz );

      std::uint8_t GetCode () override;
      std::pair< std::uint16_t, std::uint16_t > GetResult() { return { _addr, _count}; }

    //private:
      ~WrMulCoilsRslt() = default;

    private:
      std::size_t _addr;
      std::size_t _count;
  };




  class WrMulRegsRslt: public Result
  {
    public:
      WrMulRegsRslt( std::uint8_t unit_id );
      WrMulRegsRslt( std::uint8_t unit_id, std::size_t addr, std::size_t count );

      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;
      Error Deserialize( std::uint8_t* pdu, std::size_t sz );

      std::uint8_t GetCode () override;
      std::pair< std::uint16_t, std::uint16_t > GetResult() { return { _addr, _count}; }

    //private:
      ~WrMulRegsRslt() = default;

    private:
      std::size_t _addr;
      std::size_t _count;
  };






  class MaskWrRegsRslt: public Result
  {
    public:
      MaskWrRegsRslt( std::uint8_t unit_id );
      MaskWrRegsRslt( std::uint8_t unit_id, std::size_t addr, std::uint16_t andmask, std::uint16_t ormask );

      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;
      Error Deserialize( std::uint8_t* pdu, std::size_t sz );

      std::uint8_t GetCode () override;
    // private:
      ~MaskWrRegsRslt() = default;

    private:
      std::size_t   _addr;
      std::uint16_t _ormask;
      std::uint16_t _andmask;
  };




  class RdWrMulRegsRslt: public Result
  {
    public:
      RdWrMulRegsRslt( std::uint8_t unit_id );
      RdWrMulRegsRslt( std::uint8_t unit_id, std::uint8_t* ptr, std::uint8_t* end, std::size_t count );

      std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) override;
      Error Deserialize( std::uint8_t* pdu, std::size_t sz );

      std::uint8_t GetCode () override;
    // private:
      ~RdWrMulRegsRslt() = default;

    private:
      std::uint8_t* _ptr;
      std::uint8_t* _end;
      std::size_t   _count;
  };


} // namespace modbus

