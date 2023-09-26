; bx = pointer to string
print:
	pusha

.loop:
	mov al, [bx]
	cmp al, 0x00
	je .end
	mov ah, 0x0e
	int 0x10
	inc bx
	jmp .loop
.end:
	popa
	ret

; dh = number of sectors
; bx = pointer
; dl = drive number
disk_load:
	push dx

	mov ah, 0x02
	mov al, dh    ; # of sectors
	mov ch, 0x00  ; cylinder 0
	mov dh, 0x00  ; head 0
	mov cl, 0x02  ; start from 2nd sector (cuz 1 after boot)
	int 0x13
	jc .disk_err

	pop dx
	cmp dh, al
	jne .sect_err
	ret
.disk_err:
	mov bx, DISK_ERR_STR
	call print
	jmp $
.sect_err:
	mov bx, SECT_ERR_STR
	call print
	jmp $
DISK_ERR_STR db "Failed to read from disk", 0
SECT_ERR_STR db "Incorrect amount of sectors read from disk", 0
