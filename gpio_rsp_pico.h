#ifndef _gpio_rsp_pico_h
#define _gpio_rsp_pico_h

#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

class Gpio_rsp_pico
{
private:
    const uint8_t pin_number;
    const uint8_t direction;
    static const uint8_t high = 1 ;
    static const uint8_t low = 0 ;
    void init_gpio(uint8_t pin_number, uint8_t direction);
public:
    Gpio_rsp_pico(uint8_t pin_number, uint8_t direction);
    ~Gpio_rsp_pico();
    void set_high();
    void set_low();
};

#endif