#include "commands.hpp"

namespace modbus::cmd {


  MaskWriteRegister::MaskWriteRegister( std::uint8_t unit_id, std::size_t addr, std::uint16_t andmask, std::uint16_t ormask )
  {
    _unit_id = unit_id;
    _addr    = addr;
    _ormask  = ormask;
    _andmask = andmask;
  }






  std::size_t MaskWriteRegister::Serialize( std::uint8_t *pdu, std::size_t sz )
  {
    std::size_t ret = 0;

    if ( sz >= kRequestPduSize ) {

      *pdu++ = kCode;
      *pdu++ = (_addr >> 8) & 0xFFu;
      *pdu++ = _addr & 0xFFu;
      *pdu++ = (_andmask >> 8) & 0xFFu;
      *pdu++ = _andmask & 0xFFu;
      *pdu++ = (_ormask >> 8) & 0xFFu;
      *pdu   = _ormask & 0xFFu;

      ret = kRequestPduSize;
    }

    return ret;
  }


} // namespace modbus::cmd

