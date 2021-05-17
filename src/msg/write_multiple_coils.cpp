#include "commands.hpp"
#include "result.hpp"

using namespace modbus;




WrMulCoilsCmd::
WrMulCoilsCmd(std::uint8_t unit_id, std::uint8_t* ptr,
              std::size_t addr, std::size_t count)
{
  _unit_id = unit_id;
  _ptr     = ptr;
  _addr    = addr;
  _count   = count;
}






std::size_t
WrMulCoilsCmd::Serialize( std::uint8_t *pdu, std::size_t sz )
{
  std::size_t byte_count = _count >> 3 ;
  std::size_t tail_bit   = _count & 0b111;
  std::size_t RequestPduSize = 6u + (byte_count + ((tail_bit != 0u) ? 1u : 0u));
  std::size_t ret = 0;

  if ( sz >= RequestPduSize ) {

    *pdu++ = kCode;
    *pdu++ = (_addr >> 8) & 0xFFu;
    *pdu++ = _addr & 0xFFu;
    *pdu++ = (_count >> 8) & 0xFFu;
    *pdu++ = _count & 0xFFu;
    *pdu++ = RequestPduSize - 6u;


    std::uint8_t* iter = _ptr;
    std::uint8_t* end = iter + byte_count;

    while( iter < end )
    {
      *pdu++ = *iter++;
    }

    if ( tail_bit != 0 )
    {
      *pdu++ = *iter & (0xFF >> ( 8u - tail_bit ));
    }

    ret = RequestPduSize;
  }

  return ret;
}






Error
WrMulCoilsCmd::Deserialize( std::uint8_t *pdu, std::size_t sz )
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






WrMulCoilsRslt::WrMulCoilsRslt( std::uint8_t unit_id, std::size_t addr, std::size_t count )
{
  _unit_id = unit_id;
  _addr = addr;
  _count = count;
}



std::uint8_t WrMulCoilsRslt::GetCode()
{
  return WrMulCoilsCmd::kCode;
}



std::size_t WrMulCoilsRslt::Serialize( std::uint8_t *pdu, std::size_t sz )
{
  std::size_t ret = 0;

  if ( sz >= 5u ) {
    *pdu++ = WrMulCoilsCmd::kCode;
    *pdu++ = (_addr >> 8) & 0xFFu;
    *pdu++ = _addr & 0xFFu;
    *pdu++ = (_count >> 8) & 0xFFu;
    *pdu   = _count & 0xFFu;

    ret = 5u;
  }

  return ret;
}






Error
WrMulCoilsRslt::Deserialize( std::uint8_t *pdu, std::size_t sz )
{
  Error err = ERROR_FAILED;

  if ( sz == 5u )
  {
    std::uint8_t code = *pdu++;

    if ( code == WrMulCoilsCmd::kCode )
    {
      _addr  = *pdu++ << 8;
      _addr  = _addr | ( *pdu++ );
      _count = *pdu++ << 8;
      _count = _count | ( *pdu++ );
    }
  }

  return err;
}

