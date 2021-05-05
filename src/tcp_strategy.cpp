#include "strategies.hpp"


using namespace modbus;




  
auto TcpStrategy::CheckAdu( AduContext& context ) -> Error
{
  return ERROR_NONE;
}





auto TcpStrategy::GetPduSectionRange( AduContext& context ) -> std::pair< std::uint8_t*, std::size_t > 
{
  std::uint8_t* pdu = nullptr;
  std::size_t    sz = 0;
      
  if ( ( context.begin != nullptr ) && ( context.end > context.begin ) )
  {
    if ( (context.end - context.begin ) >= MinimalAduSize ) 
    {
      pdu = context.begin + PduStartPos;
      sz  = context.end - ptr;
      sz  = ( sz > MaxPduSize ) ? MaxPduSize : sz;
    }
  }
      
  return { pdu, sz };
}
  
  
  
  


auto TcpStrategy::ExtractPdu( AduContext& context ) -> std::pair< std::uint8_t*, std::size_t >
{
  std::uint8_t* pdu = nullptr;
  std::size_t    sz = 0;
  
  if ( ( context.begin != nullptr ) && ( context.adu_end > context.begin ) )
  {
    if ( (context.adu_end - context.begin) >= MinimalAduSize )
    {
      pdu = context.begin + PduStartPos;  
      sz  = context.adu_end - ptr;
      sz  = ( sz > MaxPduSize ) ? MaxPduSize : sz;
    }
  }
  
  
  return { pdu, sz };
}






auto TcpStrategy::GetAduInfo( AduContext& context ) -> std::pair< std::uint8_t, std::uint16_t > 
{
  std::uint8_t  id  = DummyServerAddr;
  std::uint16_t tid = DummyTransactionId;
      
  if ( ( context.begin != nullptr ) && ( context.adu_end > context.begin ) )
  {
    if ( (context.adu_end - context.begin) >= MinAduSize )
    {
      tid  = context.begin[TransactionIdHiPos] << 8;
      tid |= context.begin[TransactionIdLoPos]; 
    
      id   = context.begin[ServerAddrPos];
    }
  }
      
  return { id, tid };
}
    
    
    


    

auto  TcpStrategy::CreateAdu( AduContext& context, std::uint8_t id, std::16_t tid, std::size_t pdu_sz ) -> Error
{
  Error err = ERROR_FAILED;
  pdu_sz = (pdu_sz > MaxPduSize) ? MaxPduSize : pdu_sz;
      
  if ( ( context.begin != nullptr ) && ( context.end > context.begin ) )
  {
    std::size_t adu_sz = pdu_sz + MbapHeaderSize;
    
    if ( ( context.end - context.begin ) >= adu_sz )
    {
      std::uint8_t* adu_ptr = context.begin;
          
      // MBAP
      std::uint16_t tmp = pdu_sz + 1u /* ID */; 
         
      *adu_ptr++ = (tid >> 8) & 0xff;
      *adu_ptr++ = tid & 0xff;
      *adu_ptr++ = 0;
      *adu_ptr++ = 0;
      *adu_ptr++ = (tmp >> 8) & 0xff;
      *adu_ptr++ = tmp & 0xff;
      *adu_ptr++ = id; 
          
      // PDU уже во временном хранилище
      adu_ptr += pdu_sz;
      context.adu_end = adu_ptr;
      
      err = ERROR_NONE;
    }
  }
      
  
  return err;
}
    
    
    
