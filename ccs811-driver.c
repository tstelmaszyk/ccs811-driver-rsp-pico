#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"

const uint LED_PIN = 25;
const uint NWAKE_PIN = 0;

static uint8_t ADDRESS = 0x5A; //When ADDR is low the 7 bit I2C address is 0x5A (if high --> 0x5B)
const uint8_t REG_STATUS = 0x00;
const uint8_t REG_HW_ID = 0x20;

int main() {

    bi_decl(bi_program_description("This is a test binary."));
    bi_decl(bi_1pin_with_name(LED_PIN, "On-board LED"));
    bi_decl(bi_1pin_with_name(NWAKE_PIN, "On-board for nwake"));

    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_init(NWAKE_PIN);
    gpio_set_dir(NWAKE_PIN, GPIO_OUT);

    //uint8_t buf[32];
    unsigned char buf[32];

    // This example will use I2C0 on the default SDA and SCL pins (4, 5 on a Pico)
    i2c_init(i2c_default, 400 * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
    bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN,GPIO_FUNC_I2C));

 while (1) {
    gpio_put(LED_PIN, 0);
    sleep_ms(250);
    gpio_put(LED_PIN, 1);
    puts("Hello World\n");
    sleep_ms(1000);

    //gpio_put(NWAKE_PIN, 1);
    sleep_ms(1);
    buf[0]=0x20;
    printf("Valeur envoyeee: %02x\n", buf[0]);
    //i2c_write_blocking(i2c_default, ADDRESS, &REG_HW_ID, 1, true);
    i2c_write_blocking(i2c_default, ADDRESS, buf, 1, true);
    i2c_read_blocking(i2c_default, ADDRESS, buf, 1, false);
    printf("Valeur lue: %02x\n", buf[0]);
    //gpio_put(NWAKE_PIN, 0);

    }
}
