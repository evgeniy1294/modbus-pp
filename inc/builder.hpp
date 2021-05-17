#pragma once

#include "message.hpp"




namespace modbus {

  class MessageBuilder
  {
    public:
      virtual Message* Build( std::uint8_t* pdu, std::size_t sz );
  };



  // TODO: класс должен быть шаблонным с возможностью установки аллокатора
  class ResultBuilder: public MessageBuilder
  {
    public:
      Message* Build( std::uint8_t* pdu, std::size_t sz ) override;
  };



  // TODO: класс должен быть шаблонным с возможностью установки аллокатора
  class CommandBuilder: public MessageBuilder
  {
    public:
      Message* Build( std::uint8_t* pdu, std::size_t sz ) override;
  };

} // namespace modbus
