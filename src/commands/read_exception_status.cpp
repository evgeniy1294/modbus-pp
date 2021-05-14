#include "commands.hpp"


namespace modbus::cmd {


  ReadExceptionStatus::ReadExceptionStatus(std::uint8_t unit_id)
  {
    _unit_id = unit_id;
  }






  std::size_t ReadExceptionStatus::Serialize( std::uint8_t *pdu, std::size_t sz )
  {
    std::size_t ret = 0;

    if ( sz >= kRequestPduSize ) {
      *pdu = kCode;
       ret = kRequestPduSize;
    }

    return ret;
  }


} // namespace modbus::cmd





#include "result.hpp"

namespace modbus::result {

  ReadExceptionStatus::ReadExceptionStatus( std::uint8_t unit_id, std::uint8_t status )
  {
    _unit_id = unit_id;
    _status = status;
  }




  std::uint8_t ReadExceptionStatus::GetCode()
  {
    return cmd::ReadExceptionStatus::kCode;
  }



  std::size_t ReadExceptionStatus::Serialize( std::uint8_t *pdu, std::size_t sz )
  {
    std::size_t ret = 0;

    if ( sz >= 2u ) {
      *pdu++ = cmd::ReadExceptionStatus::kCode;
      *pdu   = _status;
       ret = 2;
    }

    return ret;
  }

} // namespace modbus::result



