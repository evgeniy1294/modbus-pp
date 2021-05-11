#include "commands.hpp"


using namespace modbus;


WriteMultipleCoils::WriteMultipleCoils(std::uint8_t unit_id, std::uint8_t* ptr, std::size_t addr, std::size_t count)
{
  _unit_id = unit_id;
  _ptr     = ptr;
  _addr    = addr;
  _count   = count;
}






std::size_t WriteMultipleCoils::Serialize( std::uint8_t *pdu, std::size_t sz )
{
  std::size_t byte_count = _count >> 3 ;
  std::size_t tail_bit   = _count & 0b111;
  std::size_t RequestPduSize = 6u + (byte_count + ((tail_bit != 0u) ? 1u : 0u));
  std::size_t ret = 0;
  
  if ( sz >= RequestPduSize ) {  
    
    *pdu++ = kCode;
    *pdu++ = (_addr >> 8) & 0xFFu;
    *pdu++ = _addr & 0xFFu; 
    *pdu++ = (_count >> 8) & 0xFFu;
    *pdu++ = _count & 0xFFu;
    *pdu++ = RequestPduSize - 6u;
        
    
    std::uint8_t* iter = _ptr;
    std::uint8_t* end = iter + byte_count;
    
    while( iter < end )
    {
      *pdu++ = *iter++; 
    }
          
    if ( tail_bit != 0 )
    { 
      *pdu++ = *iter & (0xFF >> ( 8u - tail_bit ));
    }
    
    ret = RequestPduSize;
  }
      
  return ret;
}



