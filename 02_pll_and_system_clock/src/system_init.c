#include "stm32f4xx.h"

/*
 * SystemInit
 * - Called from Reset_Handler before main()
 * - Sets up clock tree and low-level MCU state
 */
void SystemInit(void)
{
    // Enable HSI
    RCC->CR |= RCC_CR_HSION;
    while ((RCC->CR & RCC_CR_HSIRDY) == 0); // wait until the change takes place

    // Configure reset clock
    RCC->CFGR = 0x00000000;

    //  Disable PLL
    RCC->CR &= ~RCC_CR_PLLON;
    while (RCC->CR & RCC_CR_PLLRDY);

    //Configure Flash latency for 16 MHz
    FLASH->ACR = FLASH_ACR_LATENCY_0WS
               | FLASH_ACR_PRFTEN
               | FLASH_ACR_ICEN
               | FLASH_ACR_DCEN;

    //Select HSI as system clock
    RCC->CFGR &= ~RCC_CFGR_SW;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI); // wait until the change takes place

    // Vector Table Offset
    SCB->VTOR = FLASH_BASE;
}