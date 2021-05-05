#pragma once

#include <cstdint>


namespace modbus
{
  
  class AduStrategy {
    public:
      virtual Error CheckAdu( AduContext&& ) = 0;
      virtual Error CreateAdu( AduContext& context, std::uint8_t id, std::16_t tid, std::size_t pdusz ) = 0;
      virtual std::pair< std::uint8_t /*id*/, std::uint16_t /*tid*/ > GetAduInfo( AduContext& ) = 0;
      virtual std::pair< std::uint8_t*, std::size_t > ExtractPdu( AduContext& ) = 0;
      virtual std::pair< std::uint8_t*, std::size_t >  GetPduSectionRange( AduContext& ) = 0;
  };
    
    
  

  
  class AsciiStrategy: public AduStrategy 
  {
    public:
      // ':' + addr(2) + cmd(2)/err(2) + exp(2)/data(min 2) + LRC8(2) + 0x0D + 0x0A = 11 
      constexpr static std::size_t MinAduSize      = 11u; 
      constexpr static std::size_t MaxAduSize      = 513u;
      constexpr static std::size_t MaxPduSize      = 253u;
      constexpr static std::size_t MaxAsciiPduSize = MaxPduSize * 2;
      constexpr static std::size_t ServerAddrPosHi = 1u;
      constexpr static std::size_t ServerAddrPosLo = 2u;
      constexpr static std::size_t PduStartPos     = 3u;
    
    public:
      Error CheckAdu( AduContext& ) override;
      Error CreateAdu( AduContext& context, std::uint8_t id, std::16_t tid, std::size_t pdu_sz ) override;  
      std::pair< std::uint8_t, std::uint16_t > GetAduInfo( AduContext& ) override;
      std::pair< std::uint8_t*, std::size_t >  ExtractPdu( AduContext& ) override;
      std::pair< std::uint8_t*, std::size_t >  GetPduSectionRange( AduContext& ) override;
  };
  





  class RtuStrategy: public AduStrategy 
  {
    public:
      // addr(1) + cmd(1)/err(1) + exception(1)/data(min 1) + CRC16(2) = 5 
      constexpr static std::size_t MinAduSize     = 5u;
      constexpr static std::size_t MaxAduSize     = 256u;
      constexpr static std::size_t MaxPduSize     = 253u;
      constexpr static std::size_t ServerAddrPos  = 0u;
      constexpr static std::size_t PduStartPos    = 1u;
    
    
    public:
      Error CheckAdu( AduContext& ) override;
      Error CreateAdu( AduContext& context, std::uint8_t id, std::16_t tid, std::size_t pdu_sz ) override;  
      std::pair< std::uint8_t, std::uint16_t > GetAduInfo( AduContext& ) override;
      std::pair< std::uint8_t*, std::size_t >  ExtractPdu( AduContext& ) override;
      std::pair< std::uint8_t*, std::size_t >  GetPduSectionRange( AduContext& ) override;
  };  






  class TcpStrategy: public AduStrategy
  {
    public:
      constexpr static std::size_t MbapHeaderSize     = 7u;
      constexpr static std::size_t MaxAduSize         = 260u;
      constexpr static std::size_t MaxPduSize         = 253u;
      constexpr static std::size_t TransactionIdHiPos = 0u;
      constexpr static std::size_t TransactionIdLoPos = 1u;
      constexpr static std::size_t ServerAddrPos      = 6u;
      constexpr static std::size_t PduStartPos        = 7u; 
    
    
    public:
      Error CheckAdu( AduContext& ) override;
      Error CreateAdu( AduContext& context, std::uint8_t id, std::16_t tid, std::size_t pdu_sz ) override;  
      std::pair< std::uint8_t, std::uint16_t > GetAduInfo( AduContext& ) override;
      std::pair< std::uint8_t*, std::size_t >  ExtractPdu( AduContext& ) override;
      std::pair< std::uint8_t*, std::size_t >  GetPduSectionRange( AduContext& ) override;
  };


    
} // namespace modbus

