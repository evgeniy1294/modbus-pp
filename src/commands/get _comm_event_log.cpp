#include "commands.hpp"

using namespace modbus;


GetCommEventLog::GetCommEventLog(std::uint8_t unit_id)
{
  _unit_id = unit_id;
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
