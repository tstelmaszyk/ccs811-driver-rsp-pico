#ifndef _i2c_rsp_pico_h
#define _i2c_rsp_pico_h

#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"

class I2c_rsp_pico
{
private:
    const unsigned baudrate;
    const uint8_t sda_pin;
    const uint8_t scl_pin;
    void init_i2c();
public:
    I2c_rsp_pico();
    ~I2c_rsp_pico();
};

#endif