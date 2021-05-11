cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)
project( modbus_pp CXX C ASM )


# Project targets {{{
  add_executable(${CMAKE_PROJECT_NAME})
# }}}



# Target language standart {{{
  set_target_properties(${CMAKE_PROJECT_NAME}
                        PROPERTIES
                          C_STANDARD 11
                          CXX_STANDARD 17
                          CXX_STANDARD_REQUIRED YES)
# }}}


aux_source_directory("${CMAKE_CURRENT_LIST_DIR}/src/commands" COMMANDS)

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE
                   ${CMAKE_CURRENT_LIST_DIR}/test/main.cpp
                   ${COMMANDS}
                   ${CMAKE_CURRENT_LIST_DIR}/src/ascii_strategy.cpp
                   ${CMAKE_CURRENT_LIST_DIR}/src/rtu_strategy.cpp
                   ${CMAKE_CURRENT_LIST_DIR}/src/tcp_strategy.cpp )
                        
                        
                        
target_include_directories ("${CMAKE_PROJECT_NAME}"
                               PRIVATE "${CMAKE_CURRENT_LIST_DIR}/inc/")
