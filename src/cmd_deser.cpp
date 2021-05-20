#include "message.hpp"
#include "commands.hpp"

using namespace modbus;


Message* CmdBuilder::Build( std::uint8_t unit_id, std::uint8_t* pdu, std::size_t sz )
{
  Message* msg = nullptr;
  Error err = ERROR_FAILED;

  if ( ( sz != 0 ) && ( pdu != nullptr ) )
  {
    std::uint8_t code = *pdu;

    switch( code )
    {
      case RdCoilsCmd::kCode:
        msg = new RdCoilsCmd( unit_id );
        break;

      case RdDiscreteInputsCmd::kCode:
        msg = new RdDiscreteInputsCmd( unit_id );
        break;

      case RdHoldingRegsCmd::kCode:
        msg = new RdHoldingRegsCmd( unit_id );
        break;

      case RdInputRegsCmd::kCode:
        msg = new RdInputRegsCmd( unit_id );
        break;

      case WrCoilCmd::kCode:
        msg = new WrCoilCmd( unit_id );
        break;

      case WrRegsCmd::kCode:
        msg = new WrRegsCmd( unit_id );
        break;

      case RdExcepStatusCmd::kCode:
        msg = new RdExcepStatusCmd( unit_id );
        break;

      case WrMulCoilsCmd::kCode:
        msg = new WrMulCoilsCmd( unit_id );
        break;

      case WrMulRegsCmd::kCode:
        msg = new WrMulRegsCmd( unit_id );
        break;

      case MaskWrRegsCmd::kCode:
        msg = new MaskWrRegsCmd( unit_id );
        break;

      case RdWrMulRegsCmd::kCode:
        msg = new RdWrMulRegsCmd( unit_id );
        break;

      default:
        msg = new UnknownCmd( unit_id, code );
        break;
    }
  }

  if ( msg->Deserialize ( pdu, sz ) != ERROR_NONE )
  {
    delete msg;
    msg = nullptr;
  }

  return msg;
}
