#include "logic.hpp"

using namespace modbus;




void Logic::SetStrategy( AduStrategy* strategy )
{
  /* TODO: сохранять во временную переменную/сбрасывать текущий запрос.
     Может привести к проблемам в многопоточном приложении.
     Замена стратегии - очень редкая операция, можно использовать спинлок */
  _strategy = strategy;
}



