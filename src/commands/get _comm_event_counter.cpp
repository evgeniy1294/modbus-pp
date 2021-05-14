#include "commands.hpp"

namespace modbus::cmd {


  GetCommEventCounter::GetCommEventCounter(std::uint8_t unit_id)
  {
    _unit_id = unit_id;
  }






  std::size_t GetCommEventCounter::Serialize( std::uint8_t *pdu, std::size_t sz )
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

  GetCommEventCounter::GetCommEventCounter( std::uint8_t unit_id, std::uint16_t status, std::uint16_t count )
  {
    _unit_id = unit_id;
    _status  = status;
    _count   = count;
  }



  std::uint8_t GetCommEventCounter::GetCode()
  {
    return cmd::GetCommEventCounter::kCode;
  }



  std::size_t GetCommEventCounter::Serialize( std::uint8_t *pdu, std::size_t sz )
  {
    std::size_t ret = 0;

    if ( sz >= 5u ) {
      *pdu++ = cmd::GetCommEventCounter::kCode;
      *pdu++ = (_status >> 8) & 0xFFu;
      *pdu++ = _status & 0xFFu;
      *pdu++ = (_count >> 8) & 0xFFu;
      *pdu   = _count & 0xFFu;

      ret = 5u;
    }

    return ret;
  }

} // namespace modbus::result


