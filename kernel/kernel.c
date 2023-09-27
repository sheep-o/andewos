#include "vga.h"

void main() {
	char *vmem = (char *)0xb8000;

	kv_clear();
	kv_puts("Welcome to andewOS!");

	for (;;) {}
}
