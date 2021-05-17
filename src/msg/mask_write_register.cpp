#include "commands.hpp"
#include "result.hpp"


using namespace modbus;


MaskWrRegsCmd::MaskWrRegsCmd( std::uint8_t unit_id, std::size_t addr, std::uint16_t andmask, std::uint16_t ormask )
{
  _unit_id = unit_id;
  _addr    = addr;
  _ormask  = ormask;
  _andmask = andmask;
}




MaskWrRegsCmd::MaskWrRegsCmd( std::uint8_t unit_id )
{
  _unit_id = unit_id;
}





std::size_t MaskWrRegsCmd::Serialize( std::uint8_t *pdu, std::size_t sz )
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





Error MaskWrRegsCmd::Deserialize(std::uint8_t *pdu, std::size_t sz)
{
  Error err = ERROR_FAILED;

  if ( sz == kRequestPduSize )
  {
    std::uint8_t code = *pdu++;

    if ( code == kCode )
    {
      _addr = *pdu++ << 8;
      _addr = _addr | ( *pdu++ );

      _andmask = *pdu++ << 8;
      _andmask = _andmask | ( *pdu++ );

      _ormask = *pdu++ << 8;
      _ormask = _ormask | ( *pdu++ );

      err = ERROR_NONE;
    }
  }

  return err;
}







MaskWrRegsRslt::MaskWrRegsRslt( std::uint8_t unit_id, std::size_t addr, std::uint16_t andmask, std::uint16_t ormask )
{
  _unit_id = unit_id;
  _addr    = addr;
  _ormask  = ormask;
  _andmask = andmask;
}



std::uint8_t MaskWrRegsRslt::GetCode()
{
  return MaskWrRegsCmd::kCode;
}


std::size_t MaskWrRegsRslt::Serialize( std::uint8_t *pdu, std::size_t sz )
{
  std::size_t ret = 0;

  if ( sz >= 7u ) {

    *pdu++ = MaskWrRegsCmd::kCode;
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




Error MaskWrRegsRslt::Deserialize(std::uint8_t *pdu, std::size_t sz)
{
  Error err = ERROR_FAILED;

  if ( sz == MaskWrRegsCmd::kRequestPduSize )
  {
    std::uint8_t code = *pdu++;

    if ( code == MaskWrRegsCmd::kCode )
    {
      _addr = *pdu++ << 8;
      _addr = _addr | ( *pdu++ );

      _andmask = *pdu++ << 8;
      _andmask = _andmask | ( *pdu++ );

      _ormask = *pdu++ << 8;
      _ormask = _ormask | ( *pdu );

      err = ERROR_NONE;
    }
  }

  return err;
}


