#include "strategies.hpp"


using namespace modbus;




  
auto RtuStrategy::CheckAdu( AduContext& context ) -> Error
{
  return ( CalculateCrc16( context.begin, context.adu_end ) == 0 ? ERROR_NONE : ERROR_FAILED );
}












auto RtuStrategy::GetPduSectionRange( AduContext& context ) -> std::pair< std::uint8_t*, std::size_t > 
{
  std::uint8_t* pdu = nullptr;
  std::size_t    sz = 0;
      
  if ( ( context.begin != nullptr ) && ( context.end > context.begin ) )
  {
    if ( (context.end - context.begin ) >= MinAduSize ) 
    {
      pdu = context.begin + PduStartPos;
      sz  = (context.end - ptr) - 2u /*crc16*/;
      sz  = ( sz > MaxPduSize ) ? MaxPduSize : sz;
    }
  }
      
  return { pdu, sz };
}
    
 

    

    
    
     
auto RtuStrategy::ExtractPdu( AduContext& context ) -> std::pair< std::uint8_t*, std::size_t >
{
  std::uint8_t* pdu = nullptr;
  std::size_t    sz = 0;
  
  if ( ( context.begin != nullptr ) && ( context.adu_end > context.begin ) )
  {
    if ( (context.adu_end - context.begin) >= MinAduSize )
    {
      pdu = context.begin + PduStartPos;  
      sz  = (context.adu_end - ptr) - 2u /*crc16*/;
      sz  = ( sz > MaxPduSize ) ? MaxPduSize : sz;
    }
  }
  
  
  return { pdu, sz };
}








auto RtuStrategy::GetAduInfo( AduContext& context ) -> std::pair< std::uint8_t, std::uint16_t > 
{
  std::uint8_t ret = DummyServerAddr;
  
  if ( ( context.begin != nullptr ) && ( context.adu_end > context.begin ) )
  {
    if ( (context.adu_end - context.begin) >= MinAduSize )
    {
      ret = context.begin[ServerAddrPos];
    }
  }
      
  return { ret, DummyTransactionId };
}








auto RtuStrategy::CreateAdu( AduContext& context, std::uint8_t id, std::16_t tid, std::size_t pdu_sz ) -> Error
{
  Error err = ERROR_FAILED; 
  pdu_sz = (pdu_sz > MaxPduSize) ? MaxPduSize : pdu_sz;
 
  if ( ( context.begin != nullptr ) && ( context.end > context.begin ) )
  {
    std::size_t adu_sz = pdu_sz + 1u /*id*/ + 2u /*crc16*/;
    
    if ( ( context.end - context.begin ) >= adu_sz )
    {
      std::uint8_t* adu_ptr = context.begin;
          
     *adu_ptr++ = id; 
          
      // PDU уже во временном хранилище
      adu_ptr += pdu_sz;
          
      // Расчет сrc;
      std::uint16_t crc16 = CalculateCrc16( context.begin, adu_ptr );
     *adu_ptr++ = crc16 & 0xff;
     *adu_ptr++ = (crc16 >> 8) & 0xff;
     
      context.adu_end = adu_ptr;
      err = ERROR_NONE;
    }
  }
      
  return err;
}




