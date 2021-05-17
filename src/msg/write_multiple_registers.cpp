#include "commands.hpp"
#include "result.hpp"

using namespace modbus;



WrMulRegsCmd::
WrMulRegsCmd(std::uint8_t unit_id, std::uint8_t* ptr,
             std::size_t addr, std::size_t count)
{
  _unit_id = unit_id;
  _ptr     = ptr;
  _addr    = addr;
  _count   = count;
}






std::size_t
WrMulRegsCmd::Serialize( std::uint8_t *pdu, std::size_t sz )
{
  std::size_t byte_count = _count * 2 ;
  std::size_t RequestPduSize = 6u + byte_count;
  std::size_t ret = 0;

  if ( sz >= RequestPduSize ) {

    *pdu++ = kCode;
    *pdu++ = (_addr >> 8) & 0xffu;
    *pdu++ = _addr & 0xffu;
    *pdu++ = (_count >> 8) & 0xffu;
    *pdu++ = _count & 0xffu;
    *pdu++ = byte_count;

    std::uint8_t* iter = _ptr;
    std::uint8_t* end  = _ptr + byte_count;
    while( iter < end )
    {
      // TODO: Добавить поддержку big-endian
      *pdu++ = *(iter + 1);
      *pdu++ = *iter;
      iter   = iter + 2;
    }

    ret = RequestPduSize;
  }

  return ret;
}




Error
WrMulRegsCmd::Deserialize( std::uint8_t *pdu, std::size_t sz )
{
  Error err = ERROR_FAILED;

  if ( sz > 6u )
  {
    std::uint8_t code = *pdu++;

    if ( code == kCode )
    {
      _addr = *pdu++ << 8;
      _addr = _addr | ( *pdu++ );

      _count = *pdu++ << 8;
      _count = _count | ( *pdu++ );

      std::uint8_t byte_count = *pdu++;

      if ( byte_count == ( sz - 6u ) )
      {
        _ptr = pdu;

        err = ERROR_NONE;
      }
    }
  }


  return err;
}







WrMulRegsRslt::WrMulRegsRslt( std::uint8_t unit_id, std::size_t addr, std::size_t count )
{
  _unit_id = unit_id;
  _addr = addr;
  _count = count;
}




std::uint8_t WrMulRegsRslt::GetCode()
{
  return WrMulRegsCmd::kCode;
}





std::size_t WrMulRegsRslt::Serialize( std::uint8_t *pdu, std::size_t sz )
{
  std::size_t ret = 0;

  if ( sz >= 5u ) {
    *pdu++ = WrMulRegsCmd::kCode;
    *pdu++ = (_addr >> 8) & 0xFFu;
    *pdu++ = _addr & 0xFFu;
    *pdu++ = (_count >> 8) & 0xFFu;
    *pdu   = _count & 0xFFu;

    ret = 5u;
  }

  return ret;
}




Error
WrMulRegsRslt::Deserialize( std::uint8_t *pdu, std::size_t sz )
{
  Error err = ERROR_FAILED;

  if ( sz == 5u )
  {
    std::uint8_t code = *pdu++;

    if ( code == WrMulRegsCmd::kCode )
    {
      _addr  = *pdu++ << 8;
      _addr  = _addr | ( *pdu++ );
      _count = *pdu++ << 8;
      _count = _count | ( *pdu++ );

      err = ERROR_NONE;
    }
  }

  return err;
}


