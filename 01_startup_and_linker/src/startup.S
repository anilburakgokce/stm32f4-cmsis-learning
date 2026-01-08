.syntax unified
.cpu cortex-m4
.thumb

.global _estack
.global Reset_Handler

.section .isr_vector, "a", %progbits
.isr_vector:
    .word _estack
    .word Reset_Handler
    .word Default_Handler   /* NMI */
    .word Default_Handler   /* HardFault */