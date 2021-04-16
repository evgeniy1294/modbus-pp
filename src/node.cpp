#include "node.hpp" 



using namespace modbus;



Node:Node ( ModbusId id, Logic* logic, Storage* storage, Observer* observer = nullptr ):
  _id ( id ) {
    
  _logic = logic;
  _storage = storage;
  _observer = observer;  
}






auto Node::Set( std::size_t reg, std::uint16_t value ) -> Error 
{
  return storage->Set( reg, value );
}






auto Node::Get( std::size_t reg ) -> std::optional< std::uint16_t >
{
  return storage->Get( reg ); 
}







auto Update( FunctionCode fc, ExceptionId ei, std::size_t reg, std::size_t count ) -> Error
{ 
  Error err = ERROR_NONE;
  
  // Exception handling
  
  if ( ei == ExceptionId::None ) {
    err = _storage->Update ( reg, count ); 
  }
  
  _observer->Update ( err, reg, count );
    
  return err;
}





auto Sync ( std::size_t reg, std::size_t count, Access access ) -> Error 
{
  Error err = OK;
  auto [ ptr, fc ] = storage->Data( reg, count, access );  
  
  if ( ( ptr != nullptr ) || ( fc == FunctionCode::None ) ){
    err = _logic->InitiateRequest( this, fc, ptr, reg, count ); 
  }
  else 
  {
    err = ERROR_FAILED; 
  }
 
  return err;
}











