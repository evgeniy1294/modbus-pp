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










static std::uint8_t ByteArrayToAscii( std::uint8_t* first, std::uint8_t* last, std::uint8_t* end )
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
  Error err = ( ( (end - begin) & 0x1u ) == 0 ) ERROR_NONE ? ERROR_FAILED;
  
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







auto AsciiStrategy::CheckAdu( AduContext& context ) -> Error
{
  bool ret = ERROR_FAILED;
  
  if ( ( context.begin != nullptr ) && ( context.adu_end > context.begin ) )
  {
    std::size_t sz = context.adu_end - context.begin;
      
    if ( ( sz >= MinAduSize) && ( sz < MaxAduSize )
    {
      std::uint8_t prefix  = *context.begin;
      std::uint8_t suffix1 = *( context.adu_end - 2u );
      std::uint8_t suffix2 = *( context.adu_end - 1u );
        
      if ( ( prefix == ':' ) && ( suffix1 == 0x0D ) && ( suffix2 == 0x0A ) )
      {
        std::uint8_t lrc8lo = *( context.adu_end - 4u );
        std::uint9_t lrc8hi = *( context.adu_end - 3u );
        std::uint8_t lrc8 = AsciiToByte  ( lrc8hi, lrc8lo );
          
        ret = (lrc8 == CalculateLrc8( context.begin+1, context.adu_end-4 )) ? ERROR_NONE : ERROR_FAILED;
      }
    }
  }
      
  return ret;
}                                         
                                          
                                          
                                          
                                          
                                          




auto AsciiStrategy::GetPduSectionRange( AduContext& context ) -> std::pair< std::uint8_t*, std::size_t > 
{
  std::uint8_t* pdu = nullptr;
  std::size_t    sz = 0;
      
  if ( ( context.begin != nullptr ) && ( context.end > context.begin ) )
  {
    if ( ( context.end - context.begin ) >= MinAduSize ) 
    {
      pdu = context.begin + PduStartPos;
      sz  = ( (context.end - ptr) - 2u /*lrc8*/ - 2u /* 0x0D + 0x0A */ ) >> 1;
      sz  = ( sz > MaxPduSize ) ? MaxPduSize : sz;
    }
  }
      
  return { pdu, sz };
}
    
 


 

 
 
auto AsciiStrategy::ExtractPdu( AduContext& context ) -> std::pair< std::uint8_t*, std::size_t >
{
  std::uint8_t* pdu = nullptr;
  std::size_t    sz = 0;
  
  if ( ( context.begin != nullptr ) && ( context.adu_end > context.begin ) )
  {
    if ( (context.adu_end - context.begin) >= MinAduSize )
    {
      std::uint8_t* pdu_end = context.adu_end - 2u /*lrc8*/ - 2u /* 0x0D + 0x0A */;
      pdu = context.begin + PduStartPos;  
      
      if ( AsciiToByteArray( pdu, pdu_end ) == ERROR_NONE )
      {
        sz  = ( pdu_end - pdu ) >> 1;
        sz  = ( sz > MaxPduSize ) ? MaxPduSize : sz;
      }
      else
      {
        sz = 0;
        pdu = nullptr;
      }
    }
  }
  
  
  return { pdu, sz };
}











auto AsciiStrategy::GetAduInfo( AduContext& context ) -> std::pair< std::uint8_t, std::uint16_t > 
{
  std::uint8_t ret = DummyServerAddr;
  
  if ( ( context.begin != nullptr ) && ( context.adu_end > context.begin ) )
  {
    if ( (context.adu_end - context.begin) >= MinAduSize )
    {
      ret = ( (context.begin[ServerAddrPosHi] & 0x0f) << 4 ) | ( context.begin[ServerAddrPosLo] & 0x0f );
    }
  }
      
  return { ret, DummyTransactionId };
}











auto CreateAdu( AduContext& context, std::uint8_t id, std::16_t tid, std::size_t pdu_sz ) -> Error
{
  Error err = ERROR_FAILED;
      
  if ( ( context.begin != nullptr ) && ( context.end > context.begin ) )
  {
    std::size_t   adu_sz  = ( pdu_sz << 1 ) + 7u;
    
    if ( ( context.end - context.begin ) >= adu_sz )
    {
      std::uint8_t* adu_ptr = context.begin;
         
     *adu_ptr++ = ':'; 
      adu_ptr = ByteToAscii( adu_ptr, id );
      adu_ptr = ByteArrayToAscii( adu_ptr, adu_ptr + pdu_sz, context.end );
      
      if ( adu_ptr != nullptr )
      {    
        std::uint8_t lrc = CalculateLrc8(_begin, adu_ptr);
        adu_ptr = ByteToAscii( adu_ptr, lrc );   
       *adu_ptr++ = 0x0D; 
       *adu_ptr++ = 0x0A; 
        context.adu_end = adu_ptr;
       
        err = ERROR_NONE;
      }
    }
  }
      
  return err;
}





