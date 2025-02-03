# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_BOARD pico_w CACHE STRING "Board type")


include(pico_sdk_import.cmake)
project(Atividade_2 C CXX ASM)
pico_sdk_init()
add_executable(Atividade_2 Atividade_2.c )
pico_set_program_name(Atividade_2 "Atividade_2")
pico_enable_stdio_uart(Atividade_2 1)
pico_enable_stdio_usb(Atividade_2 1)
target_link_libraries(Atividade_2
        pico_stdlib)
pico_add_extra_outputs(Atividade_1)
