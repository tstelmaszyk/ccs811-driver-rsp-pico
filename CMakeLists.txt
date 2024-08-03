cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(ccs811-driver-project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
pico_sdk_init()

# 1 Create an INTERFACE library aggregating all the common parts of the application
add_executable(ccs811-driver 
ccs811-driver.cpp gpio_rsp_pico.cpp i2c_rsp_pico.cpp)

# note cmake policy is to use absolute paths for interface libraries.
#target_sources(ccs811-driver INTERFACE
#        ${CMAKE_CURRENT_LIST_DIR}/ccs811-driver.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/gpio_rsp_pico.cpp
#        )

# enable usb output
pico_enable_stdio_usb(ccs811-driver 1)

 # create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(ccs811-driver) 

# can include library dependencies here
target_link_libraries(ccs811-driver
        pico_stdlib
        hardware_i2c
        )