#include "commands.hpp"
#include "result.hpp"

using namespace modbus;





RdCoilsCmd::
RdCoilsCmd(std::uint8_t unit_id, std::size_t addr, std::size_t count)
{
  _unit_id = unit_id;
  _addr    = addr;
  _count   = count;
}



std::size_t
RdCoilsCmd::Serialize( std::uint8_t *pdu, std::size_t sz )
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









RdCoilsRslt::
RdCoilsRslt( std::uint8_t unit_id,
             std::uint8_t* ptr, std::uint8_t* end,
             std::size_t addr, std::size_t count )
{
  _unit_id = unit_id;
  _ptr = ptr;
  _end = end;
  _addr = addr;
  _count = count;
}





std::uint8_t RdCoilsRslt::GetCode()
{
  return RdCoilsCmd::kCode;
}



std::size_t
RdCoilsRslt::Serialize( std::uint8_t* pdu, std::size_t sz )
{
  std::size_t tail_bit     = _count & 0b111;
  std::size_t byte_count   = ( _count >> 3 ) + ((tail_bit != 0u) ? 1u : 0u);
  std::size_t allowed_size = _end - _ptr;
  std::size_t RequestPduSize = 2u + byte_count;
  std::size_t ret = 0;

  if ( ( sz >= RequestPduSize ) && ( byte_count <= allowed_size ) ) {

    *pdu++ = RdCoilsCmd::kCode;
    *pdu++ = byte_count;


    std::uint8_t* iter = _ptr;
    std::uint8_t* end = iter + byte_count - ((tail_bit != 0u) ? 1u : 0u);

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

