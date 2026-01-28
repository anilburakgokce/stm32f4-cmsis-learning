#ifdef GPIO_H
#else
#define GPIO_H
#include "stm32f4xx.h"


void gpio_init_led();

void gpio_init_button();

void gpio_led_on();

void gpio_led_off();

void gpio_led_toggle();

int gpio_button_read();

#endif