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

    //Configure Flash latency for 168 MHz
    FLASH->ACR = FLASH_ACR_LATENCY_5WS
               | FLASH_ACR_PRFTEN // enable prefetch
               | FLASH_ACR_ICEN // enable instruction cache
               | FLASH_ACR_DCEN; // enable data cache
    while(FLASH->ACR & FLASH_ACR_LATENCY != FLASH_ACR_LATENCY_5WS); // wait for the configuration to take place

    // Configure PLL for 168 MHz system clock
    // VCO_IN  = HSI / PLLM     = 16 / 16 = 1
    // VCO_OUT = VCO_IN * PLLN  = 1 / 336 = 336
    // SYS_CLK = VCO_OUT / PLLP = 336 / 2 = 168
    RCC->PLLCFGR =
        (16 << RCC_PLLCFGR_PLLM_Pos) |
        (336 << RCC_PLLCFGR_PLLN_Pos) |
        (0 << RCC_PLLCFGR_PLLP_Pos) |   // PLLP = 2
        RCC_PLLCFGR_PLLSRC_HSI; // set PLL_in as HSI

    // Enable PLL
    RCC->CR |= RCC_CR_PLLON;
    while ((RCC->CR & RCC_CR_PLLRDY) == 0); // wait until the PLL is enabled

    // Set prescalers
    RCC->CFGR |=
        RCC_CFGR_HPRE_DIV1 |   /* AHB = 168 MHz */
        RCC_CFGR_PPRE1_DIV4 |  /* APB1 = 42 MHz */
        RCC_CFGR_PPRE2_DIV2;   /* APB2 = 84 MHz */

    // Switch system clock to PLL
    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

    // Vector Table Offset
    SCB->VTOR = FLASH_BASE;
}