#include "commands.hpp"
#include "result.hpp"

using namespace modbus;


RdWrMulRegsCmd::
RdWrMulRegsCmd( std::uint8_t unit_id,
                std::size_t read_addr,  std::size_t read_count,
                std::uint8_t* write_ptr, std::size_t write_addr, std::size_t write_count )
{
  _unit_id     = unit_id;
  _read_addr   = read_addr;
  _read_count  = read_count;
  _write_ptr   = write_ptr;
  _write_addr  = write_addr;
  _write_count = write_count;
}






std::size_t RdWrMulRegsCmd::Serialize( std::uint8_t *pdu, std::size_t sz )
{
  std::size_t byte_count = _write_count * 2 ;
  std::size_t RequestPduSize = 10u + byte_count;
  std::size_t ret = 0;

  if ( sz >= RequestPduSize ) {
    *pdu++ = kCode;
    *pdu++ = (_read_addr >> 8) & 0xffu;
    *pdu++ = _read_addr & 0xffu;
    *pdu++ = (_read_count >> 8) & 0xffu;
    *pdu++ = _read_count & 0xffu;
    *pdu++ = (_write_addr >> 8) & 0xffu;
    *pdu++ = _write_addr & 0xffu;
    *pdu++ = (_write_count >> 8) & 0xffu;
    *pdu++ = _write_count & 0xffu;
    *pdu++ = byte_count;

    std::uint8_t* end  = _write_ptr + byte_count;
    std::uint8_t* ptr  = _write_ptr;
    while( ptr < end )
    {
      // TODO: Добавить поддержку big-endian
      *pdu++ = *(ptr + 1);
      *pdu++ = *ptr;
       ptr   =  ptr + 2;
    }

    ret = RequestPduSize;
  }

  return ret;
}





Error
RdWrMulRegsCmd::Deserialize( std::uint8_t *pdu, std::size_t sz )
{
  Error err = ERROR_FAILED;

  if ( sz != 0 )
  {
    std::uint8_t code = *pdu++;

    if ( code == kCode )
    {
      _read_addr = *pdu++ << 8;
      _read_addr = _read_addr | ( *pdu++ );

      _read_count = *pdu++ << 8;
      _read_count = _read_count | (*pdu++ );

      _write_addr = *pdu++ << 8;
      _write_addr = _write_addr | ( *pdu++ );

      _write_count = *pdu++ << 8;
      _write_count = _write_count | ( *pdu++ );

      std::uint8_t byte_count = *pdu++;

      if ( ( byte_count == ( sz - 10 ) ) && ( ( byte_count << 1 ) == _write_count ) )
      {
        _write_ptr = pdu;

        err = ERROR_NONE;
      }
    }
  }

  return err;
}






RdWrMulRegsRslt::
RdWrMulRegsRslt( std::uint8_t unit_id,
                            std::uint8_t* ptr, std::uint8_t* end,
                            std::size_t count )
{
  _unit_id = _unit_id;
  _ptr = ptr;
  _end = end;
  _count = count;
}





std::uint8_t RdWrMulRegsRslt::GetCode()
{
  return RdWrMulRegsCmd::kCode;
}





std::size_t RdWrMulRegsRslt::Serialize( std::uint8_t *pdu, std::size_t sz )
{
  std::size_t byte_count     = _count * 2;
  std::size_t allowed_size   = _end - _ptr;
  std::size_t RequestPduSize = 2u + byte_count;
  std::size_t ret = 0;

  if ( ( sz >= RequestPduSize ) && ( byte_count <= allowed_size ) ) {

    *pdu++ = RdWrMulRegsCmd::kCode;
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
RdWrMulRegsRslt::Deserialize( std::uint8_t *pdu, std::size_t sz )
{
  Error err = ERROR_FAILED;

  if ( sz != 0 )
  {
    std::uint8_t code = *pdu++;

    if ( code == RdWrMulRegsCmd::kCode )
    {
      std::uint8_t byte_count = *pdu++;

      if ( byte_count - ( sz - 2 ) )
      {
        _count = byte_count >> 1;
        _ptr   = pdu;
        _end   = pdu+byte_count;

        err = ERROR_NONE;
      }
    }
  }

  return err;
}




