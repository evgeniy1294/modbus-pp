#include "commands.hpp"
#include "strategies.hpp"


int main () {
  modbus::Logic logic;
  modbus::Node Node ( 0x01, { 0x1000, 4, 0x2000, 4, 0x3000, 4, 0x4000, 4 }, &logic, nullptr );
  Node.CreateRequest( nullptr, modbus::FunctionCode::ReadCoils, nullptr, 100 );
  
  return 0;
}
