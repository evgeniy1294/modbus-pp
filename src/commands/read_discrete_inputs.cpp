#include "commands.hpp"

using namespace modbus;


ReadDiscreteInputs::ReadDiscreteInputs(void* context, std::uint8_t* ptr, std::size_t addr, std::size_t count)
{
  _context = context;
  _ptr     = ptr;
  _addr    = addr;
  _count   = count;
}



      
std::size_t ReadDiscreteInputs::Serialize( std::uint8_t *pdu, std::size_t sz )
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
