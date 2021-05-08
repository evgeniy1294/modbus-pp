#include "commands.hpp"

using namespace modbus;


GetCommEventCounter::GetCommEventCounter(void* context)
{
  _context = context;
}






std::size_t GetCommEventCounter::CreateRequest( std::uint8_t* pdu, std::size_t sz ) 
{
  std::size_t ret = 0;
      
  if ( sz >= kRequestPduSize ) {
    *pdu = kCode;      
    ret = kRequestPduSize;
  }
      
  return ret;    
}






Error GetCommEventCounter::HandleResponce( std::uint8_t* pdu, std::size_t sz ) 
{
  return ERROR_NOT_IMPLEMENTED;
}
      
      
      
      
      
      

Error GetCommEventCounter::CreateResponce( std::uint8_t* pdu, std::size_t maxsz )
{
  return ERROR_NOT_IMPLEMENTED;
}
      
      
      
      
      


Error GetCommEventCounter::HandleRequest( std::uint8_t* pdu, std::size_t sz )
{
  return ERROR_NOT_IMPLEMENTED;
}
     
