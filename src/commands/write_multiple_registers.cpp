#include "commands.hpp"

namespace modbus::cmd {


  WriteMultipleRegisters::WriteMultipleRegisters(std::uint8_t unit_id, std::uint8_t* ptr, std::size_t addr, std::size_t count)
  {
    _unit_id = unit_id;
    _ptr     = ptr;
    _addr    = addr;
    _count   = count;
  }






  std::size_t WriteMultipleRegisters::Serialize( std::uint8_t *pdu, std::size_t sz )
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


} // namespace modbus::cmd





#include "result.hpp"


namespace modbus::result {

  WriteMultipleRegisters::WriteMultipleRegisters( std::uint8_t unit_id, std::size_t addr, std::size_t count )
  {
    _unit_id = unit_id;
    _addr = addr;
    _count = count;
  }




  std::uint8_t WriteMultipleRegisters::GetCode()
  {
    return cmd::WriteMultipleRegisters::kCode;
  }





  std::size_t WriteMultipleRegisters::Serialize( std::uint8_t *pdu, std::size_t sz )
  {
    std::size_t ret = 0;

    if ( sz >= 5u ) {
      *pdu++ = cmd::WriteSingleRegister::kCode;
      *pdu++ = (_addr >> 8) & 0xFFu;
      *pdu++ = _addr & 0xFFu;
      *pdu++ = (_count >> 8) & 0xFFu;
      *pdu   = _count & 0xFFu;

      ret = 5u;
    }

    return ret;
  }

} // namespace modbus::result




