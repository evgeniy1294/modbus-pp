#include "commands.hpp"

using namespace modbus;


WriteMultipleRegisters::WriteMultipleRegisters(void* context, std::uint8_t* ptr, std::size_t addr, std::size_t count)
{
  _context = context;
  _ptr     = ptr;
  _addr    = addr;
  _count   = count;
}






std::size_t WriteMultipleRegisters::CreateRequest( std::uint8_t* pdu, std::size_t sz ) 
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






Error WriteMultipleRegisters::HandleResponce( std::uint8_t* pdu, std::size_t sz ) 
{
  return ERROR_NOT_IMPLEMENTED;
}
      
      
      
      
      
      

Error WriteMultipleRegisters::CreateResponce( std::uint8_t* pdu, std::size_t maxsz )
{
  return ERROR_NOT_IMPLEMENTED;
}
      
      
      
      
      


Error WriteMultipleRegisters::HandleRequest( std::uint8_t* pdu, std::size_t sz )
{
  return ERROR_NOT_IMPLEMENTED;
}
     
