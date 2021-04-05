cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)
project( modbus_pp CXX C ASM )


# Project targets {{{
  add_executable(${CMAKE_PROJECT_NAME}.elf)
# }}}



# Target language standart {{{
  set_target_properties(${CMAKE_PROJECT_NAME}.elf
                        PROPERTIES
                          C_STANDARD 11
                          CXX_STANDARD 17
                          CXX_STANDARD_REQUIRED YES)
# }}}



target_sources("${CMAKE_PROJECT_NAME}.elf"
                PRIVATE ${CMAKE_CURRENT_LIST_DIR}/test/main.cpp
                        ${CMAKE_CURRENT_LIST_DIR}/src/logic.cpp 
                        ${CMAKE_CURRENT_LIST_DIR}/src/node_base.cpp 
                        ${CMAKE_CURRENT_LIST_DIR}/src/node.cpp )
                        
                        
                        
target_include_directories ("${CMAKE_PROJECT_NAME}.elf"
                               PRIVATE "${CMAKE_CURRENT_LIST_DIR}/inc/")
