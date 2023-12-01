# ThysOS
ThysOS is a hobby operating system.

# Bootloader
It uses Limine as the bootloader, but different boot protocols can easily be
implemented in the code. Macros tell the code what bootloader is used. For
Limine, it is `BOOT_LIMINE`.

# Terminal
There is no framebuffer terminal implemented yet. For debugging purposes, the
limine terminal is used. As soon as the framebuffer terminal is implemented,
this will be removed.

# Building
GNU Make is used to build the os. the top-level makefile calls the makefiles
of sub-projects such as `core`. It also automatically creates the `.iso` image
and downloads limine.

