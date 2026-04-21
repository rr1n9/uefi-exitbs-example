## ExitBootServices example
## Tested on IdeaPad 82C7 (Tested also in QEMU)

Disclaimer: The precompiled `compiled.efi` is provided for convenience.
Review the source code before running.

A minimal x86_64 EFI application that demonstrates how to correctly terminate UEFI Boot Services and transition to a "bare-metal" state.

## Implementation Details

The application performs the following steps:
1. Memory Map Acquisition: Calls GetMemoryMap to determine the required buffer size.
2. Memory Allocation: Uses AllocatePool to reserve space for the memory descriptors.
3. Synchronization: Retrieves the actual memory map and the current `mapKey`.
4. Termination: Invokes ExitBootServices. This is the point of no return where UEFI-specific functions (like `ConOut`) are no longer available.
5. Final State: Enters an infinite loop with hlt instruction to halt the CPU execution.

## Technical Environment
- Architecture: `x86_64`
- Toolchain: `x86_64`-w64-mingw32-gcc
- Subsystem: EFI Application (Type 10)

## Build
The project is built using a custom Makefile without EDK II dependencies, interacting directly with UEFI System Tables.

## Dependencies
- `x86_64-w64-mingw32-gcc` (cross-compiler)
- `gnu-efi` (header files)
- `qemu & ovmf` (for emulation and testing)