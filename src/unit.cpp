#include "unit.hpp"
#include "logic.hpp"
#include "storage.hpp"
#include "observer.hpp"


using namespace modbus;



Unit::Unit( std::uint8_t id, Logic* logic, Storage* storage, Observer* observer )
{
  _id = id;
  _logic = logic;
  _storage = storage;
  _observer = observer;
}



/*
std::uint16_t& Unit::operator[]( const std::size_t addr )
{
  return _storage[addr];
}
*/




Result* Unit::Execute(Command *cmd)
{
  Result* res = new ErrorResult( cmd->GetCode(), ErrorResult::ExceptionId::IllegalFunction );
  delete cmd;

  return res;
}





void Unit::Accept(Result *result)
{
  return;
}





Error Sync( std::size_t reg, std::size_t count, Access op )
{
  return ERROR_NOT_IMPLEMENTED;
}
