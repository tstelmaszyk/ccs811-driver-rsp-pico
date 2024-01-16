#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"

const uint8_t LED_PIN = 25;
const uint8_t NWAKE_PIN = 0;

static uint8_t ADDRESS = 0x5A; 
const uint8_t REG_STATUS = 0x00;
const uint8_t REG_HW_ID = 0x20;

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


int main() {

    stdio_init_all();

    Gpio_rsp_pico led(LED_PIN,GPIO_OUT);
    Gpio_rsp_pico nwake(NWAKE_PIN,GPIO_OUT);
    I2c_rsp_pico i2c_communication;
    

    uint8_t buf[32];


 while (1) {
    led.set_low();
    sleep_ms(250);
    led.set_high();
    puts("Hello World\n");
    sleep_ms(1000);

    nwake.set_low();
    printf("Valeur envoyeee: %02x\n", &REG_HW_ID);
    i2c_write_blocking(i2c_default, ADDRESS, &REG_HW_ID, 1, true);
    i2c_read_blocking(i2c_default, ADDRESS, buf, 1, false);
    printf("Valeur lue: %02x\n", buf[0]);
    nwake.set_high();

    }
}