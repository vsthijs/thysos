/*
 * Communicates with the bootloader
 * Supported bootloaders:
 * - Limine (BOOT_LIMINE)
 * */

#include <stdbool.h>
#include "mem/raw.h"
#include "string.h"

// defined in main.c and called after initialization.
void main(void);

// Called on errors that can't be recovered from.
static void hlt(void) {
    asm("cli");
    for (;;) {
        asm("hlt");
    }
}

#ifdef BOOT_LIMINE

#include "limine/limine.h"

LIMINE_BASE_REVISION(1);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#pragma GCC diagnostic ignored "-Wunused-parameter"
void _term_callback_(struct limine_terminal *_terminal, uint64_t _type, uint64_t _a, uint64_t _b, uint64_t _c) { return; }

struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 1,
    .callback = _term_callback_,
};
#pragma GCC diagnostic pop

struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0,
};

void _preinit_write(const char* text) {
    terminal_request.response->write(terminal_request.response->terminals[0], text, strlen(text));
}

void _start(void) {
    // check if everything is given
    if (LIMINE_BASE_REVISION_SUPPORTED == false) hlt();
    // if (terminal_request.response == false) hlt();

    _preinit_write("initialized BIOS debugging succesfully\n");

    // initialize memory
    mem_raw_init(memmap_request.response);

    return main();
}

#else
#error "No supported bootloader selected"
#endif

