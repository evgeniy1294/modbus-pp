#pragma once

#include "message.hpp"


namespace modbus {

  using Result = Message;

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

    //private:
      ~ErrorResult() = default;

    private:
      std::uint8_t _code;
      ExceptionId  _ei;
  };



}

