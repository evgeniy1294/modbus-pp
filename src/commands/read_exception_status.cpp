#include "commands.hpp"

using namespace modbus;


ReadExceptionStatus::ReadExceptionStatus(void* context)
{
  _context = context;
}






std::size_t ReadExceptionStatus::CreateRequest( std::uint8_t* pdu, std::size_t sz ) 
{
  std::size_t ret = 0;
      
  if ( sz >= kRequestPduSize ) {     
    *pdu = kCode;
     ret = kRequestPduSize;
  }
      
  return ret;    
}






Error ReadExceptionStatus::HandleResponce( std::uint8_t* pdu, std::size_t sz ) 
{
  return ERROR_NOT_IMPLEMENTED;
}
      
      
      
      
      
      

Error ReadExceptionStatus::CreateResponce( std::uint8_t* pdu, std::size_t maxsz )
{
  return ERROR_NOT_IMPLEMENTED;
}
      
      
      
      
      


Error ReadExceptionStatus::HandleRequest( std::uint8_t* pdu, std::size_t sz )
{
  return ERROR_NOT_IMPLEMENTED;
}
     
