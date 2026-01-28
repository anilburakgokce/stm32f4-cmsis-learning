## Startup and Linker Example Project
The default CMSIS startup provided by PlatformIO is disabled by replacing the `framework = cmsis` line with `framework = ` in order to fully control the Cortex-M4 boot sequence.

### Owned Files
- `src/startup.S`
- `src/system_init.c`
- `linker.ld`

### Notes
In `src/startup.S`:
- All exception handlers are weakly aliased to a default infinite loop, allowing seamless override from both C and assembly.
- The vector table symbol is intentionally separated from the section name to avoid GNU assembler symbol redefinition issues.