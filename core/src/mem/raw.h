#ifndef THYSOS_CORE_MEM_RAW_H
#define THYSOS_CORE_MEM_RAW_H 1


#ifdef BOOT_LIMINE

#include "limine/limine.h"

void mem_raw_init(struct limine_memmap_response*);

#else
#error "No supported bootloader selected"
#endif // BOOT_LIMINE
#endif // THYSOS_CORE_MEM_RAW_H

