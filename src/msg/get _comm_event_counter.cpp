#include "commands.hpp"
#include "result.hpp"



using namespace modbus;


GetCommEventCounterCmd::GetCommEventCounterCmd(std::uint8_t unit_id)
{
  _unit_id = unit_id;
}






std::size_t GetCommEventCounterCmd::Serialize( std::uint8_t *pdu, std::size_t sz )
{
  std::size_t ret = 0;

  if ( sz >= kRequestPduSize ) {
    *pdu = kCode;
    ret = kRequestPduSize;
  }

  return ret;
}










GetCommEventCounterRslt::GetCommEventCounterRslt( std::uint8_t unit_id, std::uint16_t status, std::uint16_t count )
{
  _unit_id = unit_id;
  _status  = status;
  _count   = count;
}



std::uint8_t GetCommEventCounterRslt::GetCode()
{
  return GetCommEventCounterCmd::kCode;
}



std::size_t GetCommEventCounterRslt::Serialize( std::uint8_t *pdu, std::size_t sz )
{
  std::size_t ret = 0;

  if ( sz >= 5u ) {
    *pdu++ = GetCommEventCounterCmd::kCode;
    *pdu++ = (_status >> 8) & 0xFFu;
    *pdu++ = _status & 0xFFu;
    *pdu++ = (_count >> 8) & 0xFFu;
    *pdu   = _count & 0xFFu;

    ret = 5u;
  }

  return ret;
}



