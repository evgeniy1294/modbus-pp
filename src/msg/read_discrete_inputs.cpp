#include "commands.hpp"
#include "result.hpp"


using namespace modbus;



RdDiscreteInputsCmd::
RdDiscreteInputsCmd(std::uint8_t unit_id, std::size_t addr, std::size_t count)
{
  _unit_id = unit_id;
  _addr    = addr;
  _count   = count;
}




std::size_t
RdDiscreteInputsCmd::Serialize( std::uint8_t *pdu, std::size_t sz )
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
RdDiscreteInputsCmd::Deserialize( std::uint8_t *pdu, std::size_t sz )
{
  Error err = ERROR_FAILED;

  if ( sz == kRequestPduSize )
  {
    std::uint8_t code = *pdu++;

    if ( code == kCode )
    {
      _addr  = *pdu++ << 8;
      _addr  = _addr | ( *pdu++ );

      _count = *pdu++ << 8;
      _count = _count | ( *pdu );

      err = ERROR_NONE;
    }
  }

  return err;
}







RdDiscreteInputsRslt::
RdDiscreteInputsRslt( std::uint8_t unit_id,
                      std::uint8_t* ptr, std::uint8_t* end,
                      std::size_t count )
{
  _unit_id = unit_id;
  _ptr = ptr;
  _end = end;
  _count = count;
}



std::uint8_t RdDiscreteInputsRslt::GetCode()
{
  return RdDiscreteInputsCmd::kCode;
}





std::size_t RdDiscreteInputsRslt::Serialize( std::uint8_t *pdu, std::size_t sz )
{
  std::size_t tail_bit   = _count & 0b111;
  std::size_t byte_count = (_count >> 3) + ((tail_bit != 0u) ? 1u : 0u);
  std::size_t allowed_size = _end - _ptr;
  std::size_t RequestPduSize = 2u + byte_count;
  std::size_t ret = 0;

  if ( ( sz >= RequestPduSize ) && (byte_count <= allowed_size) ){

    *pdu++ = RdDiscreteInputsCmd::kCode;
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




Error
RdDiscreteInputsRslt::Deserialize( std::uint8_t *pdu, std::size_t sz )
{
  Error err = ERROR_FAILED;

  if ( sz != 0 )
  {
    std::uint8_t code = *pdu++;

    if ( code == RdDiscreteInputsCmd::kCode )
    {
      std::size_t byte_count = *pdu++;

      if ( byte_count == ( sz - 2 ) )
      {
        _count = byte_count;
        _ptr = pdu;
        _end = pdu+_count;

        err = ERROR_NONE;
      }
    }
  }

  return err;
}
