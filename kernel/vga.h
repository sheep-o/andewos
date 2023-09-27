#ifndef VGA_H
#define VGA_H

#include "port.h"

#define VGA_MAX_ROWS 25
#define VGA_MAX_COLS 80
#define VGA_VMEM_ADDR 0xb8000

#define VGA_CTRL_REGISTER 0x3d4
#define VGA_DATA_REGISTER 0x3d5
#define VGA_CURSOR_LOW 0x0f
#define VGA_CURSOR_HIGH 0x0e

#define WHITE_ON_BLACK 0x0f

// returns the memory offset of cursor
int kv_get_cursor() {
	outb(VGA_CTRL_REGISTER, VGA_CURSOR_HIGH);
	int pos = inb(VGA_DATA_REGISTER) << 8;
	outb(VGA_CTRL_REGISTER, VGA_CURSOR_LOW);
	pos += inb(VGA_DATA_REGISTER);
	return pos * 2;
}

// sets cursor pos to memory offset
void kv_set_cursor(int offset) {
	offset /= 2;
	outb(VGA_CTRL_REGISTER, VGA_CURSOR_HIGH);
	outb(VGA_DATA_REGISTER, (unsigned char) (offset >> 8));
	outb(VGA_CTRL_REGISTER, VGA_CURSOR_LOW);
	outb(VGA_DATA_REGISTER, (unsigned char) (offset & 0xff));
}

void kv_clear() {
	char *vmem = (char *)VGA_VMEM_ADDR;

	for (int i = 0; i < VGA_MAX_COLS * VGA_MAX_ROWS * 2; i += 2) {
		vmem[i] = 0x00;
		vmem[i+1] = WHITE_ON_BLACK;
	}

	kv_set_cursor(0);
}

inline int kv_get_row() {
	return (kv_get_cursor() - VGA_VMEM_ADDR) / 2 / VGA_MAX_ROWS;
}

inline int kv_get_col() {
	return (kv_get_cursor() - VGA_VMEM_ADDR) / 2 / VGA_MAX_COLS;
}

void kv_puts(const char *str) {
	int cursor = kv_get_cursor();

	char *vmem = (char *) (VGA_VMEM_ADDR + cursor);
	while (str[0]) {
		vmem[0] = str[0];
		vmem[1] = WHITE_ON_BLACK;
		vmem+=2;
		cursor+=2;
		str++;
	}

	kv_set_cursor(cursor);
}

#endif
