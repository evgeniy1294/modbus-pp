#include "commands.hpp"

using namespace modbus;


GetCommEventCounter::GetCommEventCounter(void* context)
{
  _context = context;
}






std::size_t GetCommEventCounter::Serialize( std::uint8_t *pdu, std::size_t sz )
{
  std::size_t ret = 0;
      
  if ( sz >= kRequestPduSize ) {
    *pdu = kCode;      
    ret = kRequestPduSize;
  }
      
  return ret;    
}






