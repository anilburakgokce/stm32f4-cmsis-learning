#include "stm32f407xx.h"
#include "gpio.h"

extern void delay_cycles(int count);

int main(){
    // init GPIOs
    gpio_init_led();
    gpio_init_button();

    int period = 0x7000000;
    while(1){
        delay_cycles(period);
        gpio_led_toggle();
        period = gpio_button_read() ? 0x700000 : 0x7000000;
    }
}