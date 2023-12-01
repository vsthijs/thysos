CC ?= clang -target x86_64-elf
LD ?= ld.lld
AS ?= nasm

SOURCE_C := $(shell find -L src -type f -name '*.c')
SOURCE_AS := $(shell find -L src -type f -name ' *.s')

OBJECTS := $(SOURCE_C:.c=.o) $(SOURCE_AS:.s=.o)
HEADER_DEPS := $(SOURCE_C:.c=.d)

CFLAGS := \
	-Wall \
    -Wextra \
    -std=gnu11 \
    -ffreestanding \
    -fno-stack-protector \
    -fno-stack-check \
    -fno-lto \
    -fPIE \
    -m64 \
    -march=x86-64 \
    -mno-80387 \
    -mno-mmx \
    -mno-sse \
    -mno-sse2 \
    -mno-red-zone

CPPFLAGS := \
	-I.. \
	-Isrc \
	-DBOOT_LIMINE \
	-MMD \
	-MP

ASFLAGS :=\
	-Wall \
	-felf64

LDFLAGS := \
	-m elf_x86_64 \
	-nostdlib \
	-static \
	-pie \
	--no-dynamic-linker \
	-z text \
	-z max-page-size=0x1000 \
	-Tlinker.ld

OUT ?= core.elf

$(OUT): linker.ld $(OBJECTS)
	@$(LD) $(OBJECTS) $(LDFLAGS) -o $@

%.o: %.c
	@$(CC) -c $< $(CFLAGS) $(CPPFLAGS) -o $@

%.o: %.s
	@$(AS) $< $(ASFLAGS) -o $@

.PHONY: clean
clean:
	@rm -rf $(OUT) $(OBJECTS) $(HEADER_DEPS)
