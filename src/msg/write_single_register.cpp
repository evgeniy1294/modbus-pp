#include "commands.hpp"
#include "result.hpp"

using namespace modbus;





WrRegsCmd::WrRegsCmd(std::uint8_t unit_id, std::uint16_t value, std::size_t addr)
{
  _unit_id = unit_id;
  _value   = value;
  _addr    = addr;
}



std::size_t WrRegsCmd::Serialize( std::uint8_t *pdu, std::size_t sz )
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












WrRegsRslt::WrRegsRslt(std::uint8_t unit_id, std::uint16_t value, std::size_t addr )
{
  _unit_id = unit_id;
  _value = value;
  _addr = addr;
}



std::uint8_t WrRegsRslt::GetCode()
{
  return WrRegsCmd::kCode;
}



std::size_t WrRegsRslt::Serialize( std::uint8_t *pdu, std::size_t sz )
{
  std::size_t ret = 0;

  if ( sz >= 5u ) {
    *pdu++ = WrRegsCmd::kCode;
    *pdu++ = (_addr >> 8) & 0xFFu;
    *pdu++ = _addr & 0xFFu;
    *pdu++ = (_value >> 8) & 0xFFu;
    *pdu   = _value & 0xFFu;

    ret = 5u;
  }

  return ret;
}










