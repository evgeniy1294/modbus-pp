#include "commands.hpp"
#include "result.hpp"

using namespace modbus;





WrCoilCmd::
WrCoilCmd(std::uint8_t unit_id, std::uint8_t value, std::size_t addr)
{
  _unit_id = unit_id;
  _value   = ( value == 0u ) ? 0x00u : 0xFFu;
  _addr    = addr;
}




std::size_t
WrCoilCmd::Serialize( std::uint8_t *pdu, std::size_t sz )
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




Error
WrCoilCmd::Deserialize( std::uint8_t *pdu, std::size_t sz )
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






WrCoilRslt::WrCoilRslt( std::uint8_t unit_id, std::uint8_t value, std::size_t addr )
{
  _unit_id = unit_id;
  _value = value;
  _addr = addr;
}



std::uint8_t WrCoilRslt::GetCode()
{
  return WrCoilCmd::kCode;
}




std::size_t WrCoilRslt::Serialize( std::uint8_t *pdu, std::size_t sz )
{
  std::size_t ret = 0;

  if ( sz >= 5u ) {
    *pdu++ = WrCoilCmd::kCode;
    *pdu++ = (_addr >> 8) & 0xFFu;
    *pdu++ = _addr & 0xFFu;
    *pdu++ = ( _value != 0 ) ? 0xFF : 0x00;
    *pdu   = 0x00;

    ret = 5u;
  }

  return ret;
}





Error
WrCoilRslt::Deserialize( std::uint8_t *pdu, std::size_t sz )
{
  Error err = ERROR_FAILED;

  if ( sz == WrCoilCmd::kRequestPduSize )
  {
    std::uint8_t code = *pdu++;

    if ( code == WrCoilCmd::kCode )
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



