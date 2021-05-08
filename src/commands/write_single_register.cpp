#include "commands.hpp"

using namespace modbus;


WriteSingleRegister::WriteSingleRegister(void* context, std::uint8_t value, std::size_t addr)
{
  _context = context;
  _value   = value;
  _addr    = addr;
}






std::size_t WriteSingleRegister::CreateRequest( std::uint8_t* pdu, std::size_t sz ) 
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






Error WriteSingleRegister::HandleResponce( std::uint8_t* pdu, std::size_t sz ) 
{
  return ERROR_NOT_IMPLEMENTED;
}
      
      
      
      
      
      

Error WriteSingleRegister::CreateResponce( std::uint8_t* pdu, std::size_t maxsz )
{
  return ERROR_NOT_IMPLEMENTED;
}
      
      
      
      
      


Error WriteSingleRegister::HandleRequest( std::uint8_t* pdu, std::size_t sz )
{
  return ERROR_NOT_IMPLEMENTED;
}
     
