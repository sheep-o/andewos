ASM := nasm
LD := x86_64-elf-ld
CC := x86_64-elf-gcc

all: test 

build/boot.bin: boot/boot.asm
	$(ASM) -f bin $^ -o $@

build/kernel.o: kernel/kernel.c kernel/port.h kernel/vga.h
	$(CC) -m32 -ffreestanding -Ikernel/ -c $< -o $@

build/entry.o: kernel/entry.asm
	$(ASM) -f elf $^ -o $@

build/kernel.bin: build/entry.o build/kernel.o 
	$(LD) -melf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

build/andewos.bin: build/boot.bin build/kernel.bin
	cat $^ > $@

.PHONY: test
test: build/andewos.bin
	qemu-system-x86_64 $^

.PHONY: clean
clean:
	rm -rf build/*
