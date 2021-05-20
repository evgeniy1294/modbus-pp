#include "message.hpp"
#include "commands.hpp"
#include "result.hpp"

using namespace modbus;


Message* RsltBuilder::
Build( std::uint8_t unit_id, std::uint8_t* pdu, std::size_t sz )
{
  Error err = ERROR_FAILED;
  Message* msg = nullptr;

  if ( ( sz != 0 ) && ( pdu != nullptr ) )
  {
    std::uint8_t code = *pdu;

    switch( code )
    {
      case RdCoilsCmd::kCode:
        msg = new RdCoilsRslt( unit_id );
        break;

      case RdDiscreteInputsCmd::kCode:
        msg = new RdDiscreteInputsRslt( unit_id );
        break;

      case RdHoldingRegsCmd::kCode:
        msg = new RdHoldingRegsRslt( unit_id );
        break;

      case RdInputRegsCmd::kCode:
        msg = new RdInputRegsRslt( unit_id );
        break;

      case WrCoilCmd::kCode:
        msg = new WrCoilRslt( unit_id );
        break;

      case WrRegsCmd::kCode:
        msg = new WrRegsRslt( unit_id );
        break;

      case RdExcepStatusCmd::kCode:
        msg = new RdExcepStatusRslt( unit_id );
        break;

      case GetCommEventCounterCmd::kCode:
        msg = new GetCommEventCounterRslt( unit_id );
        break;

      case WrMulCoilsCmd::kCode:
        msg = new WrMulCoilsRslt( unit_id );
        break;

      case WrMulRegsCmd::kCode:
        msg = new WrMulRegsRslt( unit_id );
        break;

      case MaskWrRegsCmd::kCode:
        msg = new MaskWrRegsRslt( unit_id );
        break;

      case RdWrMulRegsCmd::kCode:
        msg = new RdWrMulRegsRslt( unit_id );
        break;

      default:
        if ( code & 0x80 )
        {
          msg = new ErrorRslt( unit_id );
        }
    }
  }

  if ( msg->Deserialize ( pdu, sz ) != ERROR_NONE )
  {
    delete msg;
    msg = nullptr;
  }

  return msg;
}
