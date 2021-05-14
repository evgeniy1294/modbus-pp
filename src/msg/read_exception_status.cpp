#include "commands.hpp"
#include "result.hpp"

using namespace modbus;


RdExcepStatusCmd::
RdExcepStatusCmd(std::uint8_t unit_id)
{
  _unit_id = unit_id;
}






std::size_t
RdExcepStatusCmd::Serialize( std::uint8_t *pdu, std::size_t sz )
{
  std::size_t ret = 0;

  if ( sz >= kRequestPduSize ) {
    *pdu = kCode;
     ret = kRequestPduSize;
  }

  return ret;
}








RdExcepStatusRslt::RdExcepStatusRslt( std::uint8_t unit_id, std::uint8_t status )
{
  _unit_id = unit_id;
  _status = status;
}




std::uint8_t RdExcepStatusRslt::GetCode()
{
  return RdExcepStatusCmd::kCode;
}



std::size_t RdExcepStatusRslt::Serialize( std::uint8_t *pdu, std::size_t sz )
{
  std::size_t ret = 0;

  if ( sz >= 2u ) {
    *pdu++ = RdExcepStatusCmd::kCode;
    *pdu   = _status;
     ret = 2;
  }

  return ret;
}



