#include "strategies.hpp"


using namespace modbus;




  class RtuStrategy: public AduStrategy 
  {
    public:
      // addr(1) + cmd(1)/err(1) + exception(1)/data(min 1) + CRC16(2) = 5 
      constexpr static std::size_t MinAduSize     = 5u;
      constexpr static std::size_t MaxAduSize     = 256u;
      constexpr static std::size_t ServerAddrPos  = 0u;
      constexpr static std::size_t PduStartPos    = 1u;
    
    
    public:
      Error CheckAdu( AduContext&& ) override;
      std::size_t CreateAdu( std::uint8_t id, std::16_t tid, std::size_t pdu_sz ) override;  
      std::pair< std::uint8_t, std::uint16_t > GetAduInfo( AduContext&& ) override;
      std::pair< std::uint8_t*, std::size_t >  ExtractPdu( AduContext&& ) override;
      std::pair< std::uint8_t*, std::size_t >  GetPduSectionRange( AduContext&& ) override;
  };  
  
  
  
  
auto RtuStrategy::CheckAdu( AduContext&& context ) -> Error
{
  return ( CalculateCrc16( context.begin, context.adu_end ) == 0 ? ERROR_OK : ERROR_FAILED );
}









auto RtuStrategy::GetPduSectionRange( AduContext&& context ) -> std::pair< std::uint8_t*, std::size_t > 
{
  std::uint8_t* ptr = nullptr;
  std::size_t sz = 0;
      
  if ( ( context.begin != nullptr ) && ( (context.end - context.begin) >= MinimalAduSize )  )
  {
    ptr = context.begin + PduStartPos;
    sz  = (context.end - ptr) - 2;
  }
      
  return { ptr, sz };
}
    

    

    
    
     
auto ExtractPdu( AduContext&& context ) -> std::pair< std::uint8_t*, std::size_t >
{
  
}




