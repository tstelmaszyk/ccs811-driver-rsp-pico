#include "gpio_rsp_pico.h"

void Gpio_rsp_pico::init_gpio(uint8_t pin_number, uint8_t direction)
{
    gpio_init(pin_number);
    gpio_set_dir(pin_number, direction);
}

Gpio_rsp_pico::Gpio_rsp_pico(uint8_t pin_number, uint8_t direction):
pin_number(pin_number),
direction(direction)
{
    init_gpio(this->pin_number,this->direction);
}

Gpio_rsp_pico::~Gpio_rsp_pico()
{
}

void Gpio_rsp_pico::set_high()
{
    gpio_put(this->pin_number,high);
}

void Gpio_rsp_pico::set_low()
{
    gpio_put(this->pin_number,low);
}