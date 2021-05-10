#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include "commands.hpp"
#include "strategies.hpp"



void toString(modbus::Buffer& buf)
{
  for ( std::uint8_t* p = buf.begin; p < buf.adu_end; p++) {
    std::cout << "0x" << std::hex << (std::uint32_t)*p << ' ';
  }

  std::cout << std::endl;
}





bool CheckAdu(std::string&& name, modbus::AduStrategy& s, modbus::Message* m,
              modbus::Buffer& buf,
              std::uint8_t* currect_begin, std::uint8_t* currect_end )
{
  bool ret = false;


  if ( s.CreateAdu(buf, m) == modbus::ERROR_NONE )
  {
    std::size_t res_adu_size = buf.adu_end - buf.begin;
    std::size_t cur_adu_size = currect_end - currect_begin;

    if ( res_adu_size != cur_adu_size )
    {
      std::cout << name << " is bad: wrong size!" << std::endl;
    }
    else
    {
      if  (! std::equal(buf.begin, buf.adu_end, currect_begin ) )
      {
        std::cout << name << " is bad: wrong data!" << std::endl;
      }
      else
      {
        ret = true;
      }
    }
  }

  if (!ret) {
    std::cout << "Get : "; toString(buf);
    std::cout << "Must: ";
    for (auto p = currect_begin; p < currect_end; p++) {
      std::cout << "0x" << std::hex << (std::uint32_t)*p << ' ';
    }
    std::cout << std::endl;
  }

  return ret;
}






void AsciiTest()
{
  modbus::AsciiStrategy ascii;


  return;
}







void TcpTest()
{
  modbus::TcpStrategy tcp;

}











void RtuTest()
{
  modbus::RtuStrategy rtu;
  std::uint8_t  mesg [256];
  modbus::Buffer buf = { .begin = mesg, .adu_end = mesg, .end = mesg + sizeof (mesg) };

  std::uint8_t  coils[4] = { 0x11, 0x22, 0x33, 0xAA };
  std::uint8_t  disc [4] = { 0x00, 0xAB, 0xCD, 0xFF };
  std::uint16_t input[4] = { 0x1122, 0x5566, 0xAABB , 0x1234 };
  std::uint16_t hold [4] = {0, 0, 0, 0};


  std::cout << "Starting RTU-test: " << std::endl;

  /*  Read Coils Request Test: */
  {
    std::array< std::uint8_t, 8> currect = { 0x01, 0x01, 0x10, 0x20, 0x00, 0x05, 0xBB, 0xAA };
    modbus::Command* cmd = new modbus::ReadCoils( nullptr, nullptr, 0x1020, 5 );
    CheckAdu( "ReadCoil command test", rtu, cmd, buf, currect.data(), currect.end() );

    delete cmd;
  }



  /*  Read Discrete Inputs Request Test: */
  {
    std::array< std::uint8_t, 8> currect = { 0x01, 0x02, 0x11, 0x21, 0x00, 0xC, 0xBB, 0xAA };
    modbus::Command* cmd = new modbus::ReadDiscreteInputs( nullptr, nullptr, 0x1121, 12 );
    CheckAdu( "ReadDiscreteInputs command test", rtu, cmd, buf, currect.data(), currect.end() );

    delete cmd;
  }




  /*  Read Holding Registers Request Test: */
  {
    std::array< std::uint8_t, 8> currect = { 0x01, 0x03, 0x20, 0x00, 0x00, 0x13, 0xBB, 0xAA };
    modbus::Command* cmd = new modbus::ReadHoldingRegisters( nullptr, nullptr, 0x2000, 0x13 );
    CheckAdu( "ReadHoldingRegisters command test", rtu, cmd, buf, currect.data(), currect.end() );

    delete cmd;
  }




  /*  Read Input Registers  Request Test: */
  {
    std::array< std::uint8_t, 8> currect = { 0x01, 0x04, 0x30, 0x00, 0x00, 0x4, 0xBB, 0xAA };
    modbus::Command* cmd = new modbus::ReadInputRegisters( nullptr, nullptr, 0x3000, 0x4 );
    CheckAdu( "ReadInputRegisters command test", rtu, cmd, buf, currect.data(), currect.end() );

    delete cmd;
  }



  /*  Write Single Coil Request Test: */
  {
    std::array< std::uint8_t, 8> currect = { 0x01, 0x05, 0x10, 0x00, 0xFF, 0x00, 0xBB, 0xAA };
    modbus::Command* cmd = new modbus::WriteSingleCoil( nullptr, 0x1, 0x1000 );
    CheckAdu( "WriteSingleCoil command test", rtu, cmd, buf, currect.data(), currect.end() );

    delete cmd;
  }

  /*  Write Single Register Request Test: */
  {
    std::array< std::uint8_t, 8> currect = { 0x01, 0x06, 0x10, 0x00, 0xDE, 0xAD, 0xBB, 0xAA };
    modbus::Command* cmd = new modbus::WriteSingleRegister( nullptr, 0xDEAD, 0x1000 );
    CheckAdu( "WriteSingleRegister command test", rtu, cmd, buf, currect.data(), currect.end() );

    delete cmd;
  }



  /*  Write Multiple Coils Request Test: */
  {
    std::array< std::uint8_t, 11> currect = { 0x01, 0x0F, 0x00, 0x13, 0x00, 0x0A, 0x02, 0x11, 0x02, 0xBB, 0xAA };
    modbus::Command* cmd = new modbus::WriteMultipleCoils( nullptr, coils, 0x0013, 10 );
    CheckAdu( "WriteMultipleCoils command test", rtu, cmd, buf, currect.data(), currect.end() );

    delete cmd;
  }


  /*  Write Multiple Registers Request Test: */
  {
    std::array< std::uint8_t, 13> currect = { 0x01, 0x10, 0x00, 0x01, 0x00, 0x02, 0x04, 0x11, 0x22, 0x55, 0x66, 0xBB, 0xAA };
    modbus::Command* cmd = new modbus::WriteMultipleRegisters( nullptr, (uint8_t*)input, 0x0001, 2 );
    CheckAdu( "WriteMultipleRegisters command test", rtu, cmd, buf, currect.data(), currect.end() );

    delete cmd;
  }


  return;
}










int main () {
  RtuTest();


  return 0;
}
