[org 0x7c00]

mov [BOOT_DRIVE], dl

mov bp, 0x8000
mov sp, bp

mov dh, 0x01
mov bx, 0x1000
mov dl, [BOOT_DRIVE]
call disk_load

cli
lgdt [gdt_descriptor]
mov eax, cr0
or eax, 0x1
mov cr0, eax
jmp CODE_SEG:pm_start

jmp $

BOOT_DRIVE: db 0

%include "boot/util.asm"
%include "boot/gdt.asm"

[bits 32]
pm_start:
	mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ebp, 0x90000
	mov esp, ebp

	call 0x1000
	jmp $

times 510 - ($ - $$) db 0
dw 0xaa55
