#include "commands.hpp"

namespace modbus::cmd {


  WriteSingleRegister::WriteSingleRegister(std::uint8_t unit_id, std::uint16_t value, std::size_t addr)
  {
    _unit_id = unit_id;
    _value   = value;
    _addr    = addr;
  }



  std::size_t WriteSingleRegister::Serialize( std::uint8_t *pdu, std::size_t sz )
  {
    std::size_t ret = 0;

    if ( sz >= kRequestPduSize ) {

      *pdu++ = kCode;
      *pdu++ = (_addr >> 8) & 0xFFu;
      *pdu++ = _addr & 0xffu;
      *pdu++ = (_value >> 8) & 0xFFu;
      *pdu++ = _value & 0xFFu;

      ret = kRequestPduSize;
    }

    return ret;
  }


} // namespace modbus::cmd





#include "result.hpp"


namespace modbus::result {

  WriteSingleRegister::WriteSingleRegister(std::uint8_t unit_id, std::uint16_t value, std::size_t addr )
  {
    _unit_id = unit_id;
    _value = value;
    _addr = addr;
  }



  std::uint8_t WriteSingleRegister::GetCode()
  {
    return cmd::WriteSingleRegister::kCode;
  }



  std::size_t WriteSingleRegister::Serialize( std::uint8_t *pdu, std::size_t sz )
  {
    std::size_t ret = 0;

    if ( sz >= 5u ) {
      *pdu++ = cmd::WriteSingleRegister::kCode;
      *pdu++ = (_addr >> 8) & 0xFFu;
      *pdu++ = _addr & 0xFFu;
      *pdu++ = (_value >> 8) & 0xFFu;
      *pdu   = _value & 0xFFu;

      ret = 5u;
    }

    return ret;
  }

} // namespace modbus::result










