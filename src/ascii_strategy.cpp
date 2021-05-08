#include "strategies.hpp"


using namespace modbus;





static inline std::uint8_t DecToAscii ( std::uint8_t c )
{
  c &= 0x0f;
  return ( c < 0x0Au ) ? c + 0x30 : c + 0x40;    
}






static inline std::uint8_t* ByteToAscii( std::uint8_t* ptr, std::uint8_t byte ) {
  *ptr++ = DecToAscii( byte >> 4 );
  *ptr++ = DecToAscii( byte );
  
  return ptr;
}






static inline std::uint8_t AsciiToDec ( std::uint8_t c )
{ 
  if ( ( c > 0x29 ) && ( c < 0x3A ) ) {
    c = c - 0x30;   // 0-9
  }
  else if ( ( c > 0x40 ) && ( c < 0x47 ) ) {
    c = c - 0x37;   // A-F
  }
  else if ( ( c > 0x60 ) && ( c < 0x67 ) ){
    c = c - 0x57;  // a-f 
  }
  else
  {
    c = 0; /* NUL */   
  }
    
  return c;  
}








static inline std::uint8_t AsciiToDecFast ( std::uint8_t c )
{
  return c & 0x0f;
}








static inline std::uint8_t AsciiToByte( std::uint8_t hi, std::uint8_t lo ) 
{
  return ( AsciiToDec(hi) << 4 ) | AsciiToDec(lo); 
}









static inline std::uint8_t AsciiToByteFast ( std::uint8_t hi, std::uint8_t lo ) 
{
  return ( AsciiToDecFast(hi) << 4 ) | AsciiToDecFast(lo); 
}










static std::uint8_t* ByteArrayToAscii( std::uint8_t* first, std::uint8_t* last, std::uint8_t* end )
{
  std::uint8_t* iptr = last - 1;
  std::uint8_t* optr = first + ( ( (last - first) << 1 ) - 1u );
  std::uint8_t* ret  = nullptr;
  
  if ( optr <= end ) 
  {
    ret  = optr + 1;
    
    do
    {
      std::uint8_t byte = *iptr--;
      std::uint8_t hi = byte >> 4;
      std::uint8_t lo = byte & 0x0f;
    
      *optr-- = ( lo < 0x0Au ) ? lo + 0x30 : lo + 0x40; 
      *optr-- = ( hi < 0x0Au ) ? hi + 0x30 : hi + 0x40; 
    } while ( optr > first );
  }
  
  return ret;  
}







static Error AsciiToByteArray( std::uint8_t* begin, std::uint8_t* end )
{
  std::uint8_t* iptr = begin;
  std::uint8_t* optr = begin;
  Error err = ( ( (end - begin) & 0x1u ) == 0 ) ? ERROR_NONE : ERROR_FAILED;
  
  if ( err == ERROR_NONE )
  {
    while( iptr < end )
    {
      std::uint8_t hi = *iptr & 0x0f;
      iptr++;
      std::uint8_t lo = *iptr & 0x0f; 
      iptr++;
      
      *optr++ =  (hi << 4) | lo;
    }
  }
  
  return err;
}








static std::uint8_t CalculateLrc8( const std::uint8_t* data, const std::uint8_t* end )
{
  std::uint8_t lrc = 0u;  

  while(data < end) {
    lrc += *data++;
  }

  return ((lrc ^ 0xFF) + 1u);    
}







auto AsciiStrategy::Check( Buffer& buffer ) -> Error
{
  Error ret = ERROR_FAILED;
  
  if ( ( buffer.begin != nullptr ) && ( buffer.adu_end > buffer.begin ) )
  {
    std::size_t sz = buffer.adu_end - buffer.begin;
      
    if ( sz >= kAsciiWrapSize )
    {
      std::uint8_t prefix  = *buffer.begin;
      std::uint8_t suffix1 = *( buffer.adu_end - 2u );
      std::uint8_t suffix2 = *( buffer.adu_end - 1u );
        
      if ( ( prefix == ':' ) && ( suffix1 == 0x0D ) && ( suffix2 == 0x0A ) )
      {
        std::uint8_t lrc8lo = *( buffer.adu_end - 4u );
        std::uint8_t lrc8hi = *( buffer.adu_end - 3u );
        std::uint8_t lrc8 = AsciiToByte  ( lrc8hi, lrc8lo );
          
        ret = (lrc8 == CalculateLrc8( buffer.begin+1, buffer.adu_end-4 )) ? ERROR_NONE : ERROR_FAILED;
      }
    }
  }
      
  return ret;
}                                         
                                          
                                          
                                          
                                          
                                          

 

 
// TODO: Change to "ExtractCommand"
auto AsciiStrategy::ExtractPdu( Buffer& buffer ) -> std::pair< std::uint8_t*, std::size_t >
{
  std::uint8_t* pdu = nullptr;
  std::size_t   adu_size = buffer.adu_end - buffer.begin;
  std::size_t   pdu_size = 0;
  
  if ( ( buffer.begin != nullptr ) && ( buffer.adu_end > buffer.begin ) )
  {
    if ( adu_size >= kAsciiWrapSize )
    {
      std::uint8_t* pdu_end = buffer.adu_end - 2u /*lrc8*/ - 2u /* 0x0D + 0x0A */;
      pdu = buffer.begin + kPduStartOffset;
      
      if ( AsciiToByteArray( pdu, pdu_end ) == ERROR_NONE )
      {
        pdu_size  = ( pdu_end - pdu ) >> 1;
        pdu_size  = ( pdu_size > kMaxPduSize ) ? kMaxPduSize : pdu_size;
      }
      else
      {
        pdu = nullptr;
      }
    }
  }
  
  
  return { pdu, pdu_size };
}











auto AsciiStrategy::GetAduInfo( Buffer& buffer ) -> std::pair< std::uint8_t, std::uint16_t >
{
  std::uint8_t ret = kDummyUnitId;
  std::size_t   adu_size = buffer.adu_end - buffer.begin;

  if ( ( buffer.begin != nullptr ) && ( buffer.adu_end > buffer.begin ) )
  {
    if ( adu_size >= kAsciiWrapSize )
    {
      ret = ( (buffer.begin[kServerAddrPosHi] & 0x0f) << 4 ) | ( buffer.begin[kServerAddrPosLo] & 0x0f );
    }
  }
      
  return { ret, kDummyTransactionId };
}











auto AsciiStrategy::CreateAdu( Buffer& buffer, Command* cmd ) -> Error
{
  Error err = ERROR_FAILED;
      
  if ( ( buffer.begin != nullptr ) && ( buffer.end > buffer.begin ) )
  {
    std::size_t   adu_max_size = buffer.end - buffer.begin;
    std::size_t   pdu_max_size = (adu_max_size > kAsciiWrapSize) ? 
                                   (adu_max_size - kAsciiWrapSize)/2u : 0u;
    std::uint8_t* ptr = buffer.begin;
    
    if ( pdu_max_size != 0 )
    {
      std::size_t pdu_size = cmd->Serialize(ptr+kPduStartOffset, pdu_max_size);
      
      if ( pdu_size != 0u )
      {
        *ptr++ = ':'; 
         ptr = ByteToAscii( ptr, cmd->GetUnitId() );
         ptr = ByteArrayToAscii( ptr, ptr + pdu_size, buffer.end );
      
        if ( ptr != nullptr )
        {    
          std::uint8_t lrc = CalculateLrc8( buffer.begin, ptr);
          ptr = ByteToAscii( ptr, lrc );   
         *ptr++ = 0x0D; 
         *ptr++ = 0x0A; 
          buffer.adu_end = ptr;
       
          err = ERROR_NONE;
        }
      }
    }
  }
      
  return err;
}




Error AsciiStrategy::CreateAdu( Buffer&, Result* )
{
  return ERROR_NOT_IMPLEMENTED;  
} 


