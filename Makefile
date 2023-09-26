ASM := nasm
LD := ld
CC := gcc

all: boot.bin

boot.bin: boot/boot.asm
	$(ASM) -f bin $^ -o build/$@

.PHONY: test
all: test
test: build/boot.bin
	qemu-system-x86_64 build/boot.bin

.PHONY: clean
clean:
	rm -rf build/*
