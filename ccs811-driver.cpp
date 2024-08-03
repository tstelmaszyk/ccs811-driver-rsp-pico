#include <stdio.h>
#include "pico/stdlib.h"

#include "gpio_rsp_pico.h"
#include "i2c_rsp_pico.h"

const uint8_t LED_PIN = 25;
const uint8_t NWAKE_PIN = 22;

static uint8_t ADDRESS = 0x5A; 
const uint8_t REG_STATUS = 0x00;
const uint8_t REG_HW_ID = 0x20;


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