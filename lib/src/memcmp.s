global memCmp

section .data

section .bss

section .text
; Compares N bytes of two memory areas.
;
; Parameters:
; [esp + 4]: the address of the first memory area to compare. (assumed to be a valid address)
; [esp + 8]: the address of the second memory area to compare. (assumed to be a valid address)
; [esp + 12]: the number of bytes to compare.
;
; Return:
; eax:
; - zero if the first N bytes of the two memory areas are equal.
; - a positive value if the first memory area is greater than the second one.
; - a negative value if the first memory area is less than the second one.
memCmp:
	mov ecx, [esp + 12] ; the number of bytes to compare
; check if the number of bytes to compare is 0
	test ecx, ecx
	jz .return_zero
; preserve the callee-saved registers
	push edi
	push esi
; put the arguments into registers
	mov edi, [esp + 12] ; the address of the first memory area to compare
	mov esi, [esp + 16] ; the address of the second memory area to compare
.compare_4_bytes:
; check if the remaining number of bytes to compare is less than 4
	cmp ecx, 4
	jb .compare_2_bytes
; compare the 4 next bytes of the two memory areas
	mov eax, dword [edi]
	mov edx, dword [esi]
	cmp eax, edx
	jne .compare_2_bytes
; step to the next chunck + update the remaining number of bytes to compare
	add edi, 4
	add esi, 4
	sub ecx, 4
; repeat until either the remaining number of bytes to compare is less than 4
; or the 4 next bytes of the two memory areas differ
	jmp .compare_4_bytes
.compare_2_bytes:
; check if the remaining number of bytes to compare is less than 2
	cmp ecx, 2
	jb .compare_1_byte
; compare the 2 next bytes of the two memory areas
	movzx eax, word [edi]
	movzx edx, word [esi]
	cmp eax, edx
	jne .compare_1_byte
; step to the next chunck + update the remaining number of bytes to compare
	add edi, 2
	add esi, 2
	sub ecx, 2
.compare_1_byte:
; check if the remaining number of bytes to compare is 0
	test ecx, ecx
	jz .return
; compare the next byte of the two memory areas
	movzx eax, byte [edi]
	movzx edx, byte [esi]
	cmp eax, edx
	jne .return
; get the next byte of each memory area
	movzx eax, byte [edi + 1]
	movzx edx, byte [esi + 1]
.return:
	sub eax, edx
; restore the callee-saved registers
	pop esi
	pop edi
	ret
.return_zero:
	xor eax, eax
	ret
