#include "strategies.hpp"


using namespace modbus;




  
auto TcpStrategy::Check( Buffer& context ) -> Error
{
  return ERROR_NONE;
}




  
  


auto TcpStrategy::ExtractPdu( Buffer& context ) -> std::pair< std::uint8_t*, std::size_t >
{
  std::uint8_t* pdu      = nullptr;
  std::size_t   pdu_size = 0;
  
  if ( ( context.begin != nullptr ) && ( context.adu_end > context.begin ) )
  {
    std::size_t adu_size = context.adu_end - context.begin;

    if ( adu_size > kMbapHeaderSize )
    {
      pdu      = context.begin + kPduStartOffset;
      pdu_size = adu_size - kMbapHeaderSize;
      pdu_size = ( pdu_size > kMaxPduSize ) ? kMaxPduSize : pdu_size;
    }
  }
  
  return { pdu, pdu_size };
}






auto TcpStrategy::GetAduInfo( Buffer& context ) -> std::pair< std::uint8_t, std::uint16_t >
{
  std::uint8_t  id  = kDummyUnitId;
  std::uint16_t tid = kDummyTransactionId;
      
  if ( ( context.begin != nullptr ) && ( context.adu_end > context.begin ) )
  {
    std::size_t adu_size = context.adu_end - context.begin;

    if ( adu_size > kMbapHeaderSize )
    {
      tid  = context.begin[kTransactionIdHiPos] << 8;
      tid |= context.begin[kTransactionIdLoPos];
    
      id   = context.begin[kServerAddrPos];
    }
  }
      
  return { id, tid };
}
    
    
    


    

auto  TcpStrategy::CreateAdu( Buffer& buffer, Command* cmd ) -> Error
{
  Error err = ERROR_FAILED;
      
  if ( ( buffer.begin != nullptr ) && ( buffer.end > buffer.begin ) )
  {
    std::size_t   adu_max_size = buffer.end - buffer.begin;
    std::size_t   pdu_max_size = (adu_max_size > kMbapHeaderSize) ? adu_max_size - kMbapHeaderSize : 0u;
    std::uint8_t* ptr = buffer.begin;
    
    if ( pdu_max_size != 0u )
    {          
      std::size_t pdu_size = cmd->CreateRequest(ptr+kPduStartOffset, pdu_max_size);
      
      if ( pdu_size != 0u )
      {
        std::uint16_t length = pdu_size + 1u; 
        std::uint16_t tid    = 0;    // TODO: сделать рандомным/счетчиком
        
        *ptr++ = (tid >> 8) & 0xff;
        *ptr++ = tid & 0xff;
        *ptr++ = 0;
        *ptr++ = 0;
        *ptr++ = (length >> 8) & 0xff;
        *ptr++ = length & 0xff;
        *ptr++ = cmd->GetUnitId();
          
        buffer.adu_end = ptr + pdu_size;
      
        err = ERROR_NONE;
      }
    }
  }
      
  
  return err;
}
    
    

    
    
Error TcpStrategy::CreateAdu( Buffer& buffer, Result* )
{
  return ERROR_NOT_IMPLEMENTED;  
} 

