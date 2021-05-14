#include "commands.hpp"

namespace modbus::cmd {


  WriteSingleCoil::WriteSingleCoil(std::uint8_t unit_id, std::uint8_t value, std::size_t addr)
  {
    _unit_id = unit_id;
    _value   = ( value == 0u ) ? 0x00u : 0xFFu;
    _addr    = addr;
  }



  std::size_t WriteSingleCoil::Serialize( std::uint8_t *pdu, std::size_t sz )
  {
    std::size_t ret = 0;

    if ( sz >= kRequestPduSize ) {

      *pdu++ = kCode;
      *pdu++ = (_addr >> 8) & 0xFFu;
      *pdu++ = _addr & 0xFFu;
      *pdu++ = _value;
      *pdu   = 0x00;

      ret = kRequestPduSize;
    }

    return ret;
  }


} // namespace modbus::cmd





#include "result.hpp"


namespace modbus::result {

  WriteSingleCoil::WriteSingleCoil( std::uint8_t unit_id, std::uint8_t value, std::size_t addr )
  {
    _unit_id = unit_id;
    _value = value;
    _addr = addr;
  }



  std::uint8_t WriteSingleCoil::GetCode()
  {
    return cmd::WriteSingleCoil::kCode;
  }




  std::size_t WriteSingleCoil::Serialize( std::uint8_t *pdu, std::size_t sz )
  {
    std::size_t ret = 0;

    if ( sz >= 5u ) {
      *pdu++ = cmd::WriteSingleCoil::kCode;
      *pdu++ = (_addr >> 8) & 0xFFu;
      *pdu++ = _addr & 0xFFu;
      *pdu++ = ( _value != 0 ) ? 0xFF : 0x00;
      *pdu   = 0x00;

      ret = 5u;
    }

    return ret;
  }


} // namespace modbus::result






