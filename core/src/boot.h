#ifndef THYSOS_CORE_BOOT_H
#define THYSOS_CORE_BOOT_H 1

// writes using the BIOS terminal. Provided by limine (bootloader). Avoid if possible.
void _preinit_write(const char* text);

#endif
