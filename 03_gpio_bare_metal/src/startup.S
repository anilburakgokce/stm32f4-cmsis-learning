/* =========================================================
 * Custom startup file written by the programmer.
 * Name must match the name of the framework's (CMSIS) startup file: startup_stm32f407xx.S
 * ========================================================= */

.syntax unified
.cpu cortex-m4
.fpu fpv4-sp-d16
.thumb

/* Symbols from linker script */
.extern _sidata, _sdata, _edata, _sbss, _ebss, _estack
.extern SystemInit
.extern main

/* =========================================================
 * Vector Table
 * ========================================================= */
.section .isr_vector, "a", %progbits
.__isr_vector:
    .word   _estack            /* 0: Initial Stack Pointer */
    .word   Reset_Handler      /* 1: Reset Handler */
    .word   NMI_Handler        /* 2: NMI */
    .word   HardFault_Handler  /* 3: Hard Fault */
    .word   MemManage_Handler  /* 4: MPU Fault */
    .word   BusFault_Handler   /* 5: Bus Fault */
    .word   UsageFault_Handler /* 6: Usage Fault */
    .word   0, 0, 0, 0         /* 7-10: Reserved */
    .word   SVC_Handler        /* 11: SVCall */
    .word   DebugMon_Handler   /* 12: Debug Monitor */
    .word   0                  /* 13: Reserved */
    .word   PendSV_Handler     /* 14: PendSV */
    .word   SysTick_Handler    /* 15: SysTick */

    .type .__isr_vector, %object
    .size .__isr_vector, .-.isr_vector

/* =========================================================
 * Default Handler & Macro for Exception Handlers
 * ========================================================= */
.weak Default_Handler
.section .text.Default_Handler, "ax", %progbits
Default_Handler:
    b       Default_Handler
    .size   Default_Handler, .-Default_Handler

.macro IRQ handler
    .weak   \handler
    .set    \handler, Default_Handler
.endm

IRQ NMI_Handler
IRQ HardFault_Handler
IRQ MemManage_Handler
IRQ BusFault_Handler
IRQ UsageFault_Handler
IRQ SVC_Handler
IRQ DebugMon_Handler
IRQ PendSV_Handler
IRQ SysTick_Handler

/* =========================================================
 * Reset Handler (The "Fallback" Implementation)
 * ========================================================= */
.weak Reset_Handler
.section .text.Reset_Handler, "ax", %progbits
.type Reset_Handler, %function
Reset_Handler:
    /* Copy .data from Flash to SRAM */
    ldr   r0, =_sidata
    ldr   r1, =_sdata
    ldr   r2, =_edata
.Lcopy_data:
    cmp   r1, r2
    ittt  lt
    ldrlt r3, [r0], #4
    strlt r3, [r1], #4
    blt   .Lcopy_data

    /* Zero .bss section */
    ldr   r0, =_sbss
    ldr   r1, =_ebss
    movs  r2, #0
.Lzero_bss:
    cmp   r0, r1
    it    lt
    strlt r2, [r0], #4
    blt   .Lzero_bss

    bl    SystemInit
    bl    main

.Lhang:
    b     .Lhang
    .size Reset_Handler, .-Reset_Handler