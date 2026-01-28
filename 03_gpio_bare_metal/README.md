## GPIO Bare Metal Example Project
Bare-metal GPIO input/output example for the STM32F407 Discovery board. The project demonstrates configuring GPIO registers directly using CMSIS and interacting with the on-board user button in Renode, without HAL or vendor startup code.

### Notes
In `platformio.ini`:
- The default CMSIS startup provided by PlatformIO is disabled by replacing the `framework = cmsis` line with `framework = ` in order to fully control the Cortex-M4 boot sequence.

In `src/startup.S`:
- All exception handlers are weakly aliased to a default infinite loop, allowing seamless override from both C and assembly.
- The vector table symbol is intentionally separated from the section name to avoid GNU assembler symbol redefinition issues.

In `src/system_init.c`:
- Default HSI is disabled and PLL of 168MHz is enabled

The following commands are to be run in Renode window in order to press and release the button configured in the code, respectively:
- `gpioA.UserButton Press`
- `gpioA.UserButton Release`