#include "commands.hpp"



namespace modbus::cmd {


  ReadHoldingRegisters::ReadHoldingRegisters(std::uint8_t unit_id, std::size_t addr, std::size_t count)
  {
    _unit_id = unit_id;
    _addr    = addr;
    _count   = count;
  }




  std::size_t ReadHoldingRegisters::Serialize( std::uint8_t *pdu, std::size_t sz )
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



