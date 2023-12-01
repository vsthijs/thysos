CC ?= clang -target x86_64-elf
LD ?= ld.lld
AS ?= nasm

EMULATOR ?= qemu

ARGS := CC=$(CC) LD=$(LD) AS=$(AS)

CORE := core
CORE_OUT := $(CORE)/core.elf

LIMINE := limine

OS := thysos
OS_OUT := $(OS).iso

ROOT := iso_root

$(OS_OUT): $(LIMINE) limine.cfg $(CORE_OUT)
	@mkdir -p $(ROOT)
	@cp $(CORE_OUT) limine.cfg $(LIMINE)/limine-bios.sys $(LIMINE)/limine-bios-cd.bin $(LIMINE)/limine-uefi-cd.bin $(ROOT)/
	@mkdir -p $(ROOT)/EFI/BOOT
	@cp limine/BOOTX64.EFI $(ROOT)/EFI/BOOT/
	@cp limine/BOOTIA32.EFI $(ROOT)/EFI/BOOT/
	@xorriso -as mkisofs -b limine-bios-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table \
		--efi-boot limine-uefi-cd.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		$(ROOT) -o $@
	@$(LIMINE)/limine bios-install $@

$(CORE_OUT): $(LIMINE) $(CORE)/makefile
	@make -C $(CORE) $(ARGS)

$(LIMINE):
	@git clone https://github.com/limine-bootloader/limine.git --branch v5.x-branch-binary --depth=1 $(LIMINE)
	@make -C $(LIMINE)

.PHONY: test_qemu
test_qemu: $(OS_OUT)
	@qemu-system-x86_64 -cdrom $(OS_OUT)

.PHONY: test
test: test_$(EMULATOR)

.PHONY: clean
clean:
	@make -C $(CORE) clean
	@rm -rf $(ROOT) $(OS_OUT)

