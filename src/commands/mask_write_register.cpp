#include "commands.hpp"

using namespace modbus;


MaskWriteRegister::MaskWriteRegister( void* context, std::size_t addr, std::uint16_t andmask, std::uint16_t ormask )
{
  _context = context;
  _addr    = addr;
  _ormask  = ormask;
  _andmask = andmask
}






std::size_t MaskWriteRegister::CreateRequest( std::uint8_t* pdu, std::size_t sz ) 
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






Error MaskWriteRegister::HandleResponce( std::uint8_t* pdu, std::size_t sz ) 
{
  return ERROR_NOT_IMPLEMENTED;
}
      
      
      
      
      
      

Error MaskWriteRegister::CreateResponce( std::uint8_t* pdu, std::size_t maxsz )
{
  return ERROR_NOT_IMPLEMENTED;
}
      
      
      
      
      


Error MaskWriteRegister::HandleRequest( std::uint8_t* pdu, std::size_t sz )
{
  return ERROR_NOT_IMPLEMENTED;
}
     
