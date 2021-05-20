#include "result.hpp"


using namespace modbus;


ErrorRslt::ErrorRslt( std::uint8_t unit_id, std::uint8_t function_code, ExceptionId ei )
{
  _unit_id = unit_id;
  _code = function_code;
  _ei = ei;
}




ErrorRslt::ErrorRslt( std::uint8_t unit_id )
{
  _unit_id = unit_id;
}




std::size_t
ErrorRslt::Serialize ( std::uint8_t* pdu, std::size_t sz )
{
  std::size_t ret = 0;

  if ( sz >= 2u ) {
    *pdu++ = _code | 0x80;
    *pdu   = static_cast<std::uint8_t>(_ei);

    ret = 2u;
  }

  return ret;
}




Error
ErrorRslt::Deserialize( std::uint8_t* pdu, std::size_t sz )
{
  Error err = ERROR_FAILED;

  if ( sz == 2u )
  {
    _code = *pdu++;
    _ei   = static_cast<ExceptionId>( *pdu );

    err = ERROR_NONE;
  }

  return err;
}



