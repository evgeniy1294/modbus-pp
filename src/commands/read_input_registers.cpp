#include "commands.hpp"

namespace modbus::cmd {


  ReadInputRegisters::ReadInputRegisters(std::uint8_t unit_id, std::size_t addr, std::size_t count)
  {
    _unit_id = unit_id;
    _addr    = addr;
    _count   = count;
  }




  std::size_t ReadInputRegisters::Serialize( std::uint8_t *pdu, std::size_t sz )
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


} // namespace modbus::cmd







#include "result.hpp"

namespace modbus::result {

  ReadInputRegisters::ReadInputRegisters( std::uint8_t unit_id,
                                          std::uint8_t* ptr, std::uint8_t* end,
                                          std::size_t addr, std::size_t count )
  {
    _unit_id = unit_id;
    _ptr = ptr;
    _end = end;
    _addr = addr;
    _count = count;
  }





  std::uint8_t ReadInputRegisters::GetCode()
  {
    return modbus::cmd::ReadInputRegisters::kCode;
  }




  std::size_t ReadInputRegisters::Serialize( std::uint8_t* pdu, std::size_t sz )
  {
    std::size_t byte_count     = _count * 2;
    std::size_t allowed_size   = _end - _ptr;
    std::size_t RequestPduSize = 2u + byte_count;
    std::size_t ret = 0;

    if ( ( sz >= RequestPduSize ) && ( byte_count <= allowed_size ) ) {

      *pdu++ = modbus::cmd::ReadHoldingRegisters::kCode;
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


} // namespace modbus::result







