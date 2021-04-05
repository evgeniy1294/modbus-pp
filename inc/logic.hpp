#pragma once
#include "node.hpp"
#include <iostream>
#include <cstring>


namespace modbus {
  
  class Logic {
    friend NodeBase;

    public:
      void Connect( NodeBase* node );
      void Disconnect( NodeBase* node );

    private:
      void CreateRequest( Request request );
  };
  
  
} // namespace modbus
