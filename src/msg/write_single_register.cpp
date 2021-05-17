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





Error
WrRegsCmd::Deserialize( std::uint8_t *pdu, std::size_t sz )
{
  Error err = ERROR_FAILED;

  if ( sz == kRequestPduSize )
  {
    std::uint8_t code = *pdu++;

    if ( code == kCode )
    {
      _addr = *pdu++ << 8;
      _addr = *pdu++;

      _value = *pdu++ << 8;
      _value = *pdu++;

      err = ERROR_NONE;
    }
  }

  return err;
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







Error
WrRegsRslt::Deserialize( std::uint8_t *pdu, std::size_t sz )
{
  Error err = ERROR_FAILED;

  if ( sz == WrRegsCmd::kRequestPduSize )
  {
    std::uint8_t code = *pdu++;

    if ( code == WrRegsCmd::kCode )
    {
      _addr = *pdu++ << 8;
      _addr = *pdu++;

      _value = *pdu++ << 8;
      _value = *pdu++;

      err = ERROR_NONE;
    }
  }

  return err;

}




