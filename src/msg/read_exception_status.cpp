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






Error
RdExcepStatusCmd::Deserialize( std::uint8_t *pdu, std::size_t sz )
{
  Error err = ERROR_FAILED;

  if ( sz == kRequestPduSize )
  {
    std::uint8_t code = *pdu;

    if ( code == kCode )
    {
      err = ERROR_NONE;
    }
  }

  return err;
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




Error
RdExcepStatusRslt::Deserialize( std::uint8_t *pdu, std::size_t sz )
{
  Error err = ERROR_FAILED;

  if ( sz == 2u )
  {
    std::uint8_t code = *pdu++;

    if ( code == RdExcepStatusCmd::kCode )
    {
      _status = *pdu;
      err = ERROR_NONE;
    }
  }

  return err;
}

