#pragma once


#include "unit.hpp"



namespace modbus
{

  class UniversalUnit: public Unit
  {
    public:
      struct InitStruct
      {
        std::uint8_t unit_id;
        std::size_t  coils_count;
        std::size_t  coils_start_addr;
        std::size_t  indis_count;
        std::size_t  indis_start_addr;
        std::size_t  inreg_count;
        std::size_t  inreg_start_addr;
        std::size_t  holreg_count;
        std::size_t  holreg_start_addr;
      };

      UniversalUnit( InitStruct& init );

    public:
      Result* Execute(Command* cmd) override;
      void Accept (Result* result)  override;
      MsgBuilder* GetCmdBuilder()   override;
      MsgBuilder* GetRsltBuilder()  override;

    private:
      std::uint8_t*  _coils;
      std::uint8_t*  _indis;
      std::uint16_t* _inreg;
      std::uint16_t* _holreg;

      std::size_t _coils_count;
      std::size_t _indis_count;
      std::size_t _inreg_count;
      std::size_t _holreg_count;


    private:
      Result* Execute( RdCoilsCmd* cmd );
      Result* Execute( RdDiscreteInputsCmd cmd );
  };



} // namespace modbus
