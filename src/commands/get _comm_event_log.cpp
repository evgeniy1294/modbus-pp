#include "commands.hpp"

using namespace modbus;


GetCommEventLog::GetCommEventLog(void* context)
{
  _context = context;
}






std::size_t GetCommEventLog::Serialize( std::uint8_t *pdu, std::size_t sz )
{
  std::size_t ret = 0;
      
  if ( sz >= kRequestPduSize ) { 
    *pdu = kCode;
    ret = kRequestPduSize;
  }
      
  return ret;
}
