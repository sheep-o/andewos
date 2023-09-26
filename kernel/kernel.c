void print() {
	char *vmem = (char *)0xb8000;
	vmem[0] = 'Z';
}

void main() {
	char *vmem = (char *)0xb8000;
	vmem[0] = 'M';

	print();
}
