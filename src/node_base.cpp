#include "node.hpp"
#include "logic.hpp"

using namespace modbus;



NodeBase::NodeBase( ModbusId id, Logic* logic, 
                    Subscriber* subscriber): id ( id ) {
  if ( logic != nullptr ) {
    logic->Connect( this );
  }

  if ( subscriber != nullptr ) {
    this->subscriber = subscriber;
  }
  
}



void NodeBase::Subscribe( Subscriber* s ) {
  if ( s != nullptr ) {
    this->subscriber = s;
  }
  
  return;
}




void NodeBase::Unsubscribe( Subscriber* s ) {
  if ( this->subscriber == s )
  {
    this->subscriber = nullptr; 
    // оповестить подписчика
  }
  
  return;
}




void NodeBase::CreateRequest( void* context, FunctionCode fc, std::uint8_t* ptr, std::size_t sz ) {
  if ( logic != nullptr )
  {
    Request request = { /* .context */ this,
                        /* .fc */ fc,
                        /* .ptr */ ptr,
                        /* .sz */ sz,
                        /* .user */ context,
                        /* .status */ 0, };
          
    logic->CreateRequest( request );
  }
        
  return;
}




void NodeBase::Connect ( Logic* logic ) {
  if ( logic != nullptr ) {
    if ( this->logic != nullptr )
    {
      this->logic->Disconnect( this );
    }
    logic->Connect( this );
  }

  return;
}
  
  
void NodeBase::Disconnect ( ) {
  if ( this->logic != nullptr )
  {
     this->logic->Disconnect ( this );
  }
        
  return;
}



