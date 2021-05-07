#include "commands.hpp"

using namespace modbus;


GetCommEventLog::GetCommEventLog(void* context)
{
  _context = context;
}






std::size_t GetCommEventLog::CreateRequest( std::uint8_t* pdu, std::size_t sz ) 
{
  std::size_t ret = 0;
      
  if ( sz >= kRequestPduSize ) { 
    *pdu = kCode;
    ret = kRequestPduSize;
  }
      
  return ret;
}






Error GetCommEventLog::HandleResponce( std::uint8_t* pdu, std::size_t sz ) 
{
  return ERROR_NOT_IMPLEMENTED;
}
      
      
      
      
      
      

Error GetCommEventLog::CreateResponce( std::uint8_t* pdu, std::size_t maxsz )
{
  return ERROR_NOT_IMPLEMENTED;
}
      
      
      
      
      


Error GetCommEventLog::HandleRequest( std::uint8_t* pdu, std::size_t sz )
{
  return ERROR_NOT_IMPLEMENTED;
}
     
