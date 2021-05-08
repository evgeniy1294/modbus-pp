#include "strategies.hpp"


using namespace modbus;


// TODO: Fix it after test
std::uint16_t CalculateCrc16( std::uint8_t* data, std::uint8_t* end )
{
  return 0xAABB;
}





  
auto RtuStrategy::Check( Buffer& buffer ) -> Error
{
  return ( CalculateCrc16( buffer.begin, buffer.adu_end ) == 0 ? ERROR_NONE : ERROR_FAILED );
}






auto RtuStrategy::ExtractPdu( Buffer& buffer ) -> std::pair< std::uint8_t*, std::size_t >
{
  std::uint8_t* pdu = nullptr;
  std::size_t   pdu_size = 0;
  
  if ( ( buffer.begin != nullptr ) && ( buffer.adu_end > buffer.begin ) )
  {
    std::size_t adu_size = buffer.adu_end - buffer.begin;

    if ( adu_size > kRtuWrapSize )
    {
      pdu = buffer.begin + kPduStartOffset;
      pdu_size  = adu_size - kRtuWrapSize;
      pdu_size  = ( pdu_size > kMaxPduSize ) ? kMaxPduSize : pdu_size;
    }
  }
  
  return { pdu, pdu_size };
}








auto RtuStrategy::GetAduInfo( Buffer& buffer ) -> std::pair< std::uint8_t, std::uint16_t >
{
  std::uint8_t ret = kDummyUnitId;
  
  if ( ( buffer.begin != nullptr ) && ( buffer.adu_end > buffer.begin ) )
  {
    std::size_t adu_size = buffer.adu_end - buffer.begin;

    if ( adu_size >= kRtuWrapSize )
    {
      ret = buffer.begin[kServerAddrPos];
    }
  }
      
  return { ret, kDummyTransactionId };
}








auto RtuStrategy::CreateAdu( Buffer& buffer, Command* cmd ) -> Error
{
  Error err = ERROR_FAILED;
  
  if ( ( buffer.begin != nullptr ) && ( buffer.end > buffer.begin ) )
  {
    std::size_t   adu_max_size = buffer.end - buffer.begin;
    std::size_t   pdu_max_size = (adu_max_size > kRtuWrapSize) ? adu_max_size - kRtuWrapSize : 0u;
    std::uint8_t* ptr = buffer.begin;
    
    if ( pdu_max_size != 0u )
    {
      std::size_t pdu_size = cmd->Serialize(ptr+kPduStartOffset, pdu_max_size);
      
      if ( pdu_size != 0u )
      {
        *ptr = cmd->GetUnitId();
        ptr  = ptr + pdu_size + kPduStartOffset;
        
        std::uint16_t crc16 = CalculateCrc16( buffer.begin, ptr );
       *ptr++ =   crc16 & 0xff;
       *ptr++ = ( crc16 >> 8 ) & 0xff;
     
        buffer.adu_end = ptr;
        err = ERROR_NONE;
      }
    }
  }
      
  return err;
}



Error RtuStrategy::CreateAdu( Buffer&, Result* )
{
  return ERROR_NOT_IMPLEMENTED;  
} 



 
      
      
