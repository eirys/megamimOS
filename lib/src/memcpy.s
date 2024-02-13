global memCpy

section .data

section .bss

section .text
; Copies N bytes from a memory area to another.
; The memory areas must not overlap.
;
; Parameters:
; [esp + 4]: the address of the destination memory area. (assumed to be a valid address)
; [esp + 8]: the address of the source memory area. (assumed to be a valid address)
; [esp + 12]: the number of bytes to copy.
;
; Return:
; eax: the address of the destination memory area.
memCpy:
; put the arguments into registers
	mov eax, [esp + 4] ; the address of the destination memory area
	mov ecx, [esp + 12] ; the number of bytes to copy
; check if the number of bytes to copy is zero
	test ecx, ecx
	jz .return
; preserve the callee-saved registers
	push esi
	push edi
; put the arguments into registers
	mov edi, eax ; the address of the destination memory area
	mov esi, [esp + 16] ; the address of the source memory area
.copy_4_bytes:
; check if the remaining number of bytes to copy is less than 4
	cmp ecx, 4
	jb .copy_2_bytes
; copy 4 bytes from the source memory area to the destination memory area
	mov edx, [esi]
	mov [edi], edx
; step to the next chunk + update the remaining number of bytes to copy
	add edi, 4
	add esi, 4
	sub ecx, 4
	jmp .copy_4_bytes
.copy_2_bytes:
; check if the remaining number of bytes to copy is less than 2
	cmp ecx, 2
	jb .copy_1_byte
; copy 2 bytes from the source memory area to the destination memory area
	mov dx, [esi]
	mov [edi], dx
; step to the next chunk + update the remaining number of bytes to copy
	add edi, 2
	add esi, 2
	sub ecx, 2
.copy_1_byte:
; check if the remaining number of bytes to copy is 0
	test ecx, ecx
	jz .restore_callee_saved_registers
; copy 1 byte from the source memory area to the destination memory area
	mov dl, [esi]
	mov [edi], dl
.restore_callee_saved_registers:
	pop edi
	pop esi
.return:
	ret
