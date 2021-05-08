#include "commands.hpp"

using namespace modbus;


MaskWriteRegister::MaskWriteRegister( void* context, std::size_t addr, std::uint16_t andmask, std::uint16_t ormask )
{
  _context = context;
  _addr    = addr;
  _ormask  = ormask;
  _andmask = andmask;
}






std::size_t MaskWriteRegister::Serialize( std::uint8_t *pdu, std::size_t sz )
{
  std::size_t ret = 0;
      
  if ( sz >= kRequestPduSize ) {
       
    *pdu++ = kCode;
    *pdu++ = (_addr >> 8) & 0xFFu;
    *pdu++ = _addr & 0xFFu; 
    *pdu++ = (_andmask >> 8) & 0xFFu;
    *pdu++ = _andmask & 0xFFu;
    *pdu++ = (_ormask >> 8) & 0xFFu;
    *pdu   = _ormask & 0xFFu;
        
    ret = kRequestPduSize;
  }
      
  return ret;    
}




