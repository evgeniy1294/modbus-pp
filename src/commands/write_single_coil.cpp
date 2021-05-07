#include "commands.hpp"

using namespace modbus;


WriteSingleCoil::WriteSingleCoil(void* context, std::uint8_t value, std::size_t addr)
{
  _context = context;
  _value   = ( value == 0u ) ? 0x00u : 0xFFu;
  _addr    = addr;
}






std::size_t WriteSingleCoil::CreateRequest( std::uint8_t* pdu, std::size_t sz ) 
{
  std::size_t ret = 0;
      
  if ( sz >= kRequestPduSize ) {
       
    *pdu++ = kCode;
    *pdu++ = (_addr >> 8) & 0xFFu;
    *pdu++ = _addr & 0xFFu; 
    *pdu++ = _value;
    *pdu   = 0x00;
        
    ret = kRequestPduSize;
  }
      
  return ret;    
}






Error WriteSingleCoil::HandleResponce( std::uint8_t* pdu, std::size_t sz ) 
{
  return ERROR_NOT_IMPLEMENTED;
}
      
      
      
      
      
      

Error WriteSingleCoil::CreateResponce( std::uint8_t* pdu, std::size_t maxsz )
{
  return ERROR_NOT_IMPLEMENTED;
}
      
      
      
      
      


Error WriteSingleCoil::HandleRequest( std::uint8_t* pdu, std::size_t sz )
{
  return ERROR_NOT_IMPLEMENTED;
}
     
