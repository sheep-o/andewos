[org 0x7c00]
[bits 16]

mov [BOOT_DRIVE], dl

mov bp, 0x8000
mov sp, bp

mov dh, 0x01
mov bx, 0x9000
mov dl, [BOOT_DRIVE]
call disk_load

jmp $

BOOT_DRIVE: db 0

%include "util.asm"

times 510 - ($ - $$) db 0
dw 0xaa55
