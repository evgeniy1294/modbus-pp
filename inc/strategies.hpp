#pragma once

#include <cstdint>
#include <utility>

#include "defs.hpp"
#include "commands.hpp"
#include "result.hpp"


namespace modbus
{
  
  class AduStrategy {
    public:
      virtual Error Check ( Buffer& ) = 0;
      virtual Error CreateAdu( Buffer&, Message* ) = 0;
      virtual std::pair< std::uint8_t , std::uint16_t > GetAduInfo( Buffer& ) = 0;
      
      // Maybe should be changed on ExtractMessage
      virtual std::pair< std::uint8_t*, std::size_t >   ExtractPdu( Buffer& ) = 0;

    protected:
      enum Type { TYPE_ASCII, TYPE_RTU, TYPE_TCP };
      virtual Type IsType() = 0;
  };
    
    
  

  
  class AsciiStrategy: public AduStrategy 
  {
    public:
      constexpr static std::size_t kAsciiWrapSize   = 7u;
      constexpr static std::size_t kMaxAduSize      = 513u;
      constexpr static std::size_t kMaxPduSize      = 253u;
      constexpr static std::size_t kMaxAsciiPduSize = kMaxPduSize * 2;
      constexpr static std::size_t kServerAddrPosHi = 1u;
      constexpr static std::size_t kServerAddrPosLo = 2u;
      constexpr static std::size_t kPduStartOffset  = 3u;
    
    public:
      Error Check ( Buffer& ) override;
      Error CreateAdu( Buffer&, Message* ) override;
      std::pair< std::uint8_t, std::uint16_t > GetAduInfo( Buffer& ) override;
      std::pair< std::uint8_t*, std::size_t >  ExtractPdu( Buffer& ) override;

    private:
      Type IsType() override { return Type::TYPE_ASCII; }
  };
  





  class RtuStrategy: public AduStrategy 
  {
    public:
      constexpr static std::size_t kRtuWrapSize    = 3u;
      constexpr static std::size_t kMaxAduSize     = 256u;
      constexpr static std::size_t kMaxPduSize     = kMaxAduSize - kRtuWrapSize;
      constexpr static std::size_t kServerAddrPos  = 0u;
      constexpr static std::size_t kPduStartOffset = 1u;
    
    
    public:
      Error Check ( Buffer& );
      Error CreateAdu( Buffer&, Message* ) override;
      std::pair< std::uint8_t, std::uint16_t > GetAduInfo( Buffer& ) override;
      std::pair< std::uint8_t*, std::size_t >  ExtractPdu( Buffer& ) override;

    private:
      Type IsType() override { return Type::TYPE_RTU; }
  };  






  class TcpStrategy: public AduStrategy
  {
    public:
      constexpr static std::size_t kMbapHeaderSize     = 7u;
      constexpr static std::size_t kMaxAduSize         = 260u;
      constexpr static std::size_t kMaxPduSize         = kMaxAduSize - kMbapHeaderSize;
      constexpr static std::size_t kTransactionIdHiPos = 0u;
      constexpr static std::size_t kTransactionIdLoPos = 1u;
      constexpr static std::size_t kServerAddrPos      = 6u;
      constexpr static std::size_t kPduStartOffset     = 7u; 
    
    
    public:
      Error Check ( Buffer& );
      Error CreateAdu( Buffer&, Message* ) override;
      std::pair< std::uint8_t, std::uint16_t > GetAduInfo( Buffer& ) override;
      std::pair< std::uint8_t*, std::size_t >  ExtractPdu( Buffer& ) override;


    private:
      Type IsType() override { return Type::TYPE_TCP; }
  };


    
} // namespace modbus

