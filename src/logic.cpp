#include "logic.hpp"


using namespace modbus;


void Logic::Connect( NodeBase* node ) {
  node->logic = this;
  std::cout << "Node connected" << std::endl;
}



void Logic::Disconnect( NodeBase* node ) {
  node->logic = nullptr;
  std::cout << "Node disconnected" << std::endl; 
}



void Logic::CreateRequest( Request request ) {
  std::cout << "Request accepted" << std::endl;
  request.context->Notify ( request.user, request.fc, ExceptionId::None, request.ptr, request.sz );
}

