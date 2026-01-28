## PLL and System Clock Example Project
Bare-metal STM32F407 system clock configuration using CMSIS only. Includes a custom startup, linker script, and a manual PLL setup to reach 168 MHz.

### Owned Files
- `src/startup.S`
- `src/system_init.c`
- `linker.ld`

### Notes
In `platformio.ini`:
- The default CMSIS startup provided by PlatformIO is disabled by replacing the `framework = cmsis` line with `framework = ` in order to fully control the Cortex-M4 boot sequence.

In `src/startup.S`:
- All exception handlers are weakly aliased to a default infinite loop, allowing seamless override from both C and assembly.
- The vector table symbol is intentionally separated from the section name to avoid GNU assembler symbol redefinition issues.