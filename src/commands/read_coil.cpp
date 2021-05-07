#include "commands.hpp"

using namespace modbus;



ReadCoils::ReadCoils(void* context, std::uint8_t* ptr, std::size_t addr, std::size_t count)
{
  _context = context;
  _ptr     = ptr;
  _addr    = addr;
  _count   = count;
}






std::size_t ReadCoils::CreateRequest( std::uint8_t* pdu, std::size_t sz ) 
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






Error ReadCoils::HandleResponce( std::uint8_t* pdu, std::size_t sz ) 
{
  return ERROR_NOT_IMPLEMENTED;
}
      
      
      
      
      
      
      
      
Error ReadCoils::CreateResponce( std::uint8_t* pdu, std::size_t maxsz )
{
  return ERROR_NOT_IMPLEMENTED;
}
      
      
      
      
      
      
      


Error ReadCoils::HandleRequest( std::uint8_t* pdu, std::size_t sz )
{
  return ERROR_NOT_IMPLEMENTED;
}


