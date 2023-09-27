void clear() {
	char *vmem = (char *)0xb8000;

	int i = 0;
	while (i < 80*25*2) {
		vmem[i] = ' ';
		vmem[i + 1] = 0x00;
		i += 2;
	}
}


void print(int cursor, char *str) {
	char *vmem = (char *)(0xb8000 + cursor * 2);

	for (int i = 0; i < 80*25 - cursor; i++) {
		if (str[i] == 0)
			return;
		else {
			vmem[0] = str[i];
			vmem[1] = 0x0f;
			vmem += 2;
		}
	}
}

void main() {
	clear();
	int cursor = 0;
	print(cursor, "Welcome to andewOS!");

	for (;;) {}
}
