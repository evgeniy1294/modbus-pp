#include "commands.hpp"

using namespace modbus;


ReadWriteMultipleRegisters::ReadWriteMultipleRegisters( void* context, 
                              std::uint8_t* read_ptr,  std::size_t read_addr,  std::size_t read_count,
                              std::uint8_t* write_ptr, std::size_t write_addr, std::size_t write_count )
{
  _context = context;
  _read_ptr    = read_ptr;          
  _read_addr   = read_addr;          
  _read_count  = read_count;         
  _write_ptr   = write_ptr;
  _write_addr  = write_addr;
  _write_count = write_count;
}






std::size_t ReadWriteMultipleRegisters::Serialize( std::uint8_t *pdu, std::size_t sz )
{
  std::size_t byte_count = _write_count * 2 ;
  std::size_t RequestPduSize = 10u + byte_count;
  std::size_t ret = 0;    
  
  if ( sz >= RequestPduSize ) {          
    *pdu++ = kCode;
    *pdu++ = (_read_addr >> 8) & 0xffu;
    *pdu++ = _read_addr & 0xffu; 
    *pdu++ = (_read_count >> 8) & 0xffu;
    *pdu++ = _read_count & 0xffu;
    *pdu++ = (_write_addr >> 8) & 0xffu;
    *pdu++ = _write_addr & 0xffu; 
    *pdu++ = (_write_count >> 8) & 0xffu;
    *pdu++ = _write_count & 0xffu;
    *pdu++ = byte_count;
     
    std::uint8_t* end  = _write_ptr + byte_count;
    std::uint8_t* ptr  = _write_ptr;
    while( ptr < end )
    {
      // TODO: Добавить поддержку big-endian
      *pdu++ = *(ptr + 1);  
      *pdu++ = *ptr;
       ptr   =  ptr + 2;
    }
    
    ret = RequestPduSize;
  }
      
  return ret;    
}




