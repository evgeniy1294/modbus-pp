#include "commands.hpp"

using namespace modbus;


ReportSlaveId::ReportSlaveId(void* context)
{
  _context = context;
}






std::size_t ReportSlaveId::CreateRequest( std::uint8_t* pdu, std::size_t sz ) 
{
  std::size_t ret = 0;
      
  if ( sz >= kRequestPduSize ) {     
    *pdu = kCode;
     ret = kRequestPduSize;
  }
      
  return ret;    
}






Error ReportSlaveId::HandleResponce( std::uint8_t* pdu, std::size_t sz ) 
{
  return ERROR_NOT_IMPLEMENTED;
}
      
      
      
      
      
      

Error ReportSlaveId::CreateResponce( std::uint8_t* pdu, std::size_t maxsz )
{
  return ERROR_NOT_IMPLEMENTED;
}
      
      
      
      
      


Error ReportSlaveId::HandleRequest( std::uint8_t* pdu, std::size_t sz )
{
  return ERROR_NOT_IMPLEMENTED;
}
     
