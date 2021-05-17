#include "commands.hpp"
#include "result.hpp"


using namespace modbus;



RdHoldingRegsCmd::
RdHoldingRegsCmd(std::uint8_t unit_id, std::size_t addr, std::size_t count)
{
  _unit_id = unit_id;
  _addr    = addr;
  _count   = count;
}




std::size_t
RdHoldingRegsCmd::Serialize( std::uint8_t *pdu, std::size_t sz )
{
  std::size_t ret = 0;

  if ( sz >= kRequestPduSize ) {

    *pdu++ = kCode;
    *pdu++ = (_addr >> 8) & 0xFFu;
    *pdu++ = _addr & 0xFFu;
    *pdu++ = (_count >> 8) & 0xFFu;
    *pdu++ = _count & 0xFFu;

    ret = kRequestPduSize;
  }

  return ret;
}



Error
RdHoldingRegsCmd::Deserialize( std::uint8_t *pdu, std::size_t sz )
{
  Error err = ERROR_FAILED;

  if ( sz == kRequestPduSize )
  {
    std::uint8_t code = *pdu++;

    if ( code == kCode )
    {
      _addr = *pdu++ << 8;
      _addr = _addr | ( *pdu++ );

      _count = *pdu++ << 8;
      _count = _count | ( *pdu );

      err = ERROR_NONE;
    }
  }

  return err;
}






RdHoldingRegsRslt::
RdHoldingRegsRslt( std::uint8_t unit_id,
                   std::uint8_t* ptr, std::uint8_t* end,
                   std::size_t count )
{
  _unit_id = unit_id;
  _ptr = ptr;
  _end = end;
  _count = count;
}





std::uint8_t RdHoldingRegsRslt::GetCode()
{
  return RdHoldingRegsCmd::kCode;
}




std::size_t RdHoldingRegsRslt::Serialize( std::uint8_t* pdu, std::size_t sz )
{
  std::size_t byte_count     = _count * 2;
  std::size_t allowed_size   = _end - _ptr;
  std::size_t RequestPduSize = 2u + byte_count;
  std::size_t ret = 0;

  if ( ( sz >= RequestPduSize ) && ( byte_count <= allowed_size ) ) {

    *pdu++ = RdHoldingRegsCmd::kCode;
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
RdHoldingRegsRslt::Deserialize( std::uint8_t* pdu, std::size_t sz )
{
  Error err = ERROR_FAILED;

  if ( sz != 0 )
  {
    std::uint8_t code = *pdu++;

    if ( code == RdHoldingRegsCmd::kCode )
    {
      std::uint8_t byte_count = *pdu++;

      if ( byte_count == ( sz - 2 ) )
      {
        _count = byte_count >> 1;
        _ptr = pdu;
        _end = pdu + byte_count;

        err = ERROR_NONE;
      }
    }
  }

  return err;
}


