#include "commands.hpp"



namespace modbus::cmd {

  ReadCoils::ReadCoils(std::uint8_t unit_id, std::size_t addr, std::size_t count)
  {
    _unit_id = unit_id;
    _addr    = addr;
    _count   = count;
  }



  std::size_t ReadCoils::Serialize( std::uint8_t *pdu, std::size_t sz )
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

}  // namespace modbus::cmd





#include "result.hpp"

namespace modbus::result {


  ReadCoils::ReadCoils( std::uint8_t unit_id, std::uint8_t* ptr, std::size_t addr, std::size_t count )
  {
    _unit_id = unit_id;
    _ptr = ptr;
    _addr = addr;
    _count = count;
  }





  std::uint8_t ReadCoils::GetCode()
  {
    return modbus::cmd::ReadCoils::kCode;
  }



  std::size_t ReadCoils::Serialize( std::uint8_t* pdu, std::size_t maxsz )
  {

    return ret;
  }


} // namepsace modbus::result
