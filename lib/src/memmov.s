global memMov
extern memCpy

section .data

section .bss

section .text
; Copies N bytes from a memory area to another.
; The memory areas may overlap.
;
; Parameters:
; [esp + 4]: the address of the destination memory area. (assumed to be a valid address)
; [esp + 8]: the address of the source memory area. (assumed to be a valid address)
; [esp + 12]: the number of bytes to copy.
;
; Return:
; eax: the address of the destination memory area.
memMov:
; put the arguments into registers
	mov eax, [esp + 4]; the address of the destination memory area
	mov edx, [esp + 8]; the address of the source memory area
; check if we need to compute the copy, and if so, check if we can use a regular copy (from the beginning to the end)
	cmp eax, edx
	je .return
	ja .reverse_copy
; copy the memory from the beginning to the end
	jmp memCpy
	ud2; unreachable code
.reverse_copy: ; copy the memory from the end to the beginning
; put the arguments into registers
	mov ecx, [esp + 12]; the number of bytes to copy
; check if the number of bytes to copy is 0
	test ecx, ecx
	jz .return
; advance the pointers to the end of the memory areas
	add eax, ecx
	add edx, ecx
; preserve the callee-saved registers
	push ebx
.copy_4_bytes:
; check if the remaining number of bytes to copy is less than 4
	cmp ecx, 4
	jb .copy_2_bytes
; step to the next chunck + update the remaining number of bytes to copy
	sub eax, 4
	sub edx, 4
	sub ecx, 4
; copy 4 bytes from the source memory area to the destination memory area
	mov ebx, [edx]
	mov [eax], ebx
; repeat until the remaining number of bytes to copy is less than 4
	jmp .copy_4_bytes
.copy_2_bytes:
; check if the remaining number of bytes to copy is less than 2
	cmp ecx, 2
	jb .copy_1_byte
; step to the next chunk + update the remaining number of bytes to copy
	sub eax, 2
	sub edx, 2
	sub ecx, 2
; copy 2 bytes from the source memory area to the destination memory area
	mov bx, [edx]
	mov [eax], bx
.copy_1_byte:
; check if the remaining number of bytes to copy is 0
	test ecx, ecx
	jz .restore_callee_saved_registers
; step to the next chunk + update the remaining number of bytes to copy
	dec eax
	dec edx
	dec ecx
; copy 1 byte from the source memory area to the destination memory area
	mov bl, [edx]
	mov [eax], bl
.restore_callee_saved_registers:
	pop ebx
.return:
	ret
