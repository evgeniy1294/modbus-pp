#include "universal_unit.hpp"

using namespace modbus;






UniversalUnit::UniversalUnit( InitStruct& init )
{
  std::size_t _coils_count  = init.coils_count;
  std::size_t _indis_count  = init.indis_count;
  std::size_t _inreg_count  = init.inreg_count;
  std::size_t _holreg_count = init.holreg_count;

  std::uint8_t*  _coils  = new uint8_t [ _coils_count  ];
  std::uint8_t*  _indis  = new uint8_t [ _indis_count  ];
  std::uint16_t* _inreg  = new uint16_t[ _inreg_count  ];
  std::uint16_t* _holreg = new uint16_t[ _holreg_count ];
}





Result* Execute(Command* cmd)
{
  Result* res = nullptr;

  switch (cmd->GetCode()) {
    case RdCoilsCmd::kCode:
      res = Execute( static_cast<RdCoilsCmd*>(cmd) );
      break;

    case RdDiscreteInputsCmd::kCode:
      res = Execute( static_cast<RdDiscreteInputsCmd*>(cmd) );
      break;

    case RdHoldingRegsCmd::kCode:
      break;

    case RdInputRegsCmd::kCode:
      break;

    case WrCoilCmd::kCode:
      break;

    case WrRegsCmd::kCode:
      break;

    case RdExcepStatusCmd::kCode:
      break;

    case WrMulCoilsCmd::kCode:
      break;

    case WrMulRegsCmd::kCode:
      break;

    case MaskWrRegsCmd::kCode:
      break;

    case RdWrMulRegsCmd::kCode:
      break;

    default:
      break;

  }

  return res;
}




void Accept (Result* result)
{
  return;
}



MsgBuilder* GetCmdBuilder()
{
  static CmdBuilder builder;
  return &builder;
}



MsgBuilder* GetRsltBuilder()
{
  static RsltBuilder builder;
  return &builder;
}



