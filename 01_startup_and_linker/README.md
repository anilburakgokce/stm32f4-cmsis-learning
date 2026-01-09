The default CMSIS startup provided by PlatformIO is explicitly disabled using -nostartfiles in order to fully control the Cortex-M4 boot sequence.s

All exception handlers are weakly aliased to a default infinite loop, allowing seamless override from both C and assembly.

The vector table symbol is intentionally separated from the section name to avoid GNU assembler symbol redefinition issues.