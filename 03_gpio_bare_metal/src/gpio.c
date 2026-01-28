#include "gpio.h"

void gpio_init_led(){
    // Enable Clock for GPIOD (Bit 3 of AHB1ENR)
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

    // configure GPIO port depending on the input for data output according to Table 36 in RM0090
    GPIOD->MODER &= ~GPIO_MODER_MODER12;
    GPIOD->MODER |= GPIO_MODER_MODER12_0;
    GPIOD->OTYPER &= ~GPIO_OTYPER_OT12; 
    GPIOD->PUPDR &= ~GPIO_PUPDR_PUPDR12_0;
    GPIOD->PUPDR |= GPIO_PUPDR_PUPDR12_1;
}

void gpio_init_button(){
    // Enable Clock for GPIOA (Bit 0 of AHB1ENR)
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // configure PA0 for data input
    GPIOA->MODER &= ~GPIO_MODER_MODER10;
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD0;
}

void gpio_led_on(){
    GPIOD->BSRR = GPIO_BSRR_BS12;
}

void gpio_led_off(){
    GPIOD->BSRR = GPIO_BSRR_BR12;
}

void gpio_led_toggle(){
    if(GPIOD->ODR & GPIO_ODR_OD12_Msk){
        gpio_led_off();
    }
    else {
        gpio_led_on();
    }
}

int gpio_button_read(){
    return GPIOA->IDR & GPIO_IDR_ID0_Msk;
}