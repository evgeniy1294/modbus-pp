#include "commands.hpp"

using namespace modbus;


ReportSlaveIdCmd::ReportSlaveIdCmd(std::uint8_t unit_id)
{
  _unit_id = unit_id;
}






std::size_t ReportSlaveIdCmd::Serialize( std::uint8_t *pdu, std::size_t sz )
{
  std::size_t ret = 0;

  if ( sz >= kRequestPduSize ) {
    *pdu = kCode;
     ret = kRequestPduSize;
  }

  return ret;
}




Error
ReportSlaveIdCmd::Deserialize( std::uint8_t *pdu, std::size_t sz )
{
  Error err = ERROR_FAILED;

  if ( sz == kRequestPduSize )
  {
    err = ERROR_NONE;
  }

  return err;
}

