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
	mov eax, [esp + 4]; the address of the destination memory area
	mov edx, [esp + 8]; the address of the source memory area
; check if we need to compute the copy
	cmp eax, edx
	je .return
; put the arguments into registers
	mov ecx, [esp + 12]; the number of bytes to copy
; check if the number of bytes to copy is 0
	test ecx, ecx
	jz .return
; preserve the callee-saved registers
	push ebx
.copy_4_bytes:
; check if the remaining number of bytes to copy is less than 4
	cmp ecx, 4
	jb .copy_2_bytes
; copy 4 bytes from the source memory area to the destination memory area
	mov ebx, [edx]
	mov [eax], ebx
; step to the next chunk + update the remaining number of bytes to copy
	add eax, 4
	add edx, 4
	sub ecx, 4
; repeat until the remaining number of bytes to copy is less than 4
	jmp .copy_4_bytes
.copy_2_bytes:
; check if the remaining number of bytes to copy is less than 2
	cmp ecx, 2
	jb .copy_1_byte
; copy 2 bytes from the source memory area to the destination memory area
	mov bx, [edx]
	mov [eax], bx
; step to the next chunk + update the remaining number of bytes to copy
	add eax, 2
	add edx, 2
	sub ecx, 2
.copy_1_byte:
; check if the remaining number of bytes to copy is 0
	test ecx, ecx
	jz .restore_callee_saved_registers
; copy 1 byte from the source memory area to the destination memory area
	mov bl, [edx]
	mov [eax], bl
.restore_callee_saved_registers:
	pop ebx
; set the return value
	mov eax, [esp + 4]
.return:
	ret
