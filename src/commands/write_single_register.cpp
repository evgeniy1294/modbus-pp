#include "commands.hpp"

using namespace modbus;


WriteSingleRegister::WriteSingleRegister(void* context, std::uint16_t value, std::size_t addr)
{
  _context = context;
  _value   = value;
  _addr    = addr;
}






std::size_t WriteSingleRegister::Serialize( std::uint8_t *pdu, std::size_t sz )
{
  std::size_t ret = 0;
      
  if ( sz >= kRequestPduSize ) {
       
    *pdu++ = kCode;
    *pdu++ = (_addr >> 8) & 0xFFu;
    *pdu++ = _addr & 0xffu; 
    *pdu++ = (_value >> 8) & 0xFFu;
    *pdu++ = _value & 0xFFu;
        
    ret = kRequestPduSize;
  }
      
  return ret;
}
