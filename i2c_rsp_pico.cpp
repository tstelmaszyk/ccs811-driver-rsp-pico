# include "i2c_rsp_pico.h"

void I2c_rsp_pico::init_i2c()
{
    // This example will use I2C0 on the default SDA and SCL pins (4, 5 on a Pico)
    i2c_init(i2c_default, baudrate);
    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);
    gpio_pull_up(sda_pin);
    gpio_pull_up(scl_pin);
    bi_decl(bi_2pins_with_func(sda_pin, scl_pin,GPIO_FUNC_I2C));
}

I2c_rsp_pico::I2c_rsp_pico():
baudrate(400*1000),
sda_pin(PICO_DEFAULT_I2C_SDA_PIN),
scl_pin(PICO_DEFAULT_I2C_SCL_PIN)
{
    this->init_i2c();
}

I2c_rsp_pico::~I2c_rsp_pico()
{
}