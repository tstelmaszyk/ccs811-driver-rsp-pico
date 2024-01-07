cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(ccs811-driver-project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()
add_executable(ccs811-driver
    ccs811-driver.c
)
pico_enable_stdio_usb(ccs811-driver 1)
pico_add_extra_outputs(ccs811-driver) 
target_link_libraries(ccs811-driver pico_stdlib hardware_i2c)