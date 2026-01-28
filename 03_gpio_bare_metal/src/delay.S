.syntax unified
.cpu cortex-m4
.thumb

.section .text
.global delay_cycles

# busy wait for r0 cycles
delay_cycles:
    subs r0, r0, #1
    bne delay_cycles
    bx  lr