global memSet

section .data

section .bss

section .text
; Sets N bytes of a memory area to a specific value.
;
; Parameters:
; [esp + 4]: the address of the memory area to set. (assumed to be a valid address)
; [esp + 8]: the value to set the memory area to.
; [esp + 12]: the number of bytes to set.
;
; Return:
; eax: the address of the set memory area.
memSet:
; put the arguments into registers
	mov ecx, [esp + 12] ; the number of bytes to set
	test ecx, ecx
	jz .return
	movzx eax, byte [esp + 8]
	mov edx, 0x01010101
	mul edx
	mov edx, eax ; the value to set the memory area to
	mov eax, [esp + 4] ; the address of the memory area to set
.set_4_bytes:
; check if the remaining number of bytes to set is less 4
	cmp ecx, 4
	jb .set_2_bytes
; set 4 bytes of the memory area to the value
	mov [eax], edx
; step to the next chunck + update the remaining number of bytes to set
	add eax, 4
	sub ecx, 4
	jmp .set_4_bytes
.set_2_bytes:
; check if the remaining number of bytes to set is less 2
	cmp ecx, 2
	jb .set_1_byte
; set 2 bytes of the memory area to the value
	mov [eax], dx
; step to the next chunck + update the remaining number of bytes to set
	add eax, 2
	sub ecx, 2
	jmp .set_2_bytes
.set_1_byte:
; check if the remaining number of bytes to set is 0
	test ecx, ecx
	jz .return
; set 1 byte of the memory area to the value
	mov [eax], dl
.return:
; return the address of the set memory area
	mov eax, [esp + 4]
	ret
