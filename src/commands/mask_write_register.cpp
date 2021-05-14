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




#include "result.hpp"



namespace modbus::result {

  MaskWriteRegister::MaskWriteRegister( std::uint8_t unit_id, std::size_t addr, std::uint16_t andmask, std::uint16_t ormask )
  {
    _unit_id = unit_id;
    _addr    = addr;
    _ormask  = ormask;
    _andmask = andmask;
  }



  std::uint8_t MaskWriteRegister::GetCode()
  {
    return cmd::MaskWriteRegister::kCode;
  }


  std::size_t MaskWriteRegister::Serialize( std::uint8_t *pdu, std::size_t sz )
  {
    std::size_t ret = 0;

    if ( sz >= 7u ) {

      *pdu++ = cmd::MaskWriteRegister::kCode;
      *pdu++ = (_addr >> 8) & 0xFFu;
      *pdu++ = _addr & 0xFFu;
      *pdu++ = (_andmask >> 8) & 0xFFu;
      *pdu++ = _andmask & 0xFFu;
      *pdu++ = (_ormask >> 8) & 0xFFu;
      *pdu   = _ormask & 0xFFu;

      ret = 7u;
    }

    return ret;
  }



} // namespace modbus::result


