global strCmp

section .data

section .bss

section .text
; Compares two null-terminated strings.
;
; Parameters
; [esp + 4]: the address of the first string to compare. (assumed to be a valid address)
; [esp + 8]: the address of the second string to compare. (assumed to be a valid address)
;
; Return
; eax:
; - zero if the strings are equal.
; - a positive value if the first string is greater than the second one.
; - a negative value if the first string is less than the second one.
strCmp:
; put the arguments into registers
	mov ecx, [esp + 4]; the address of the first string
	mov edx, [esp + 8]; the address of the second string
; clear the first buffer register
	xor eax, eax
; check if we need to compute the comparison
	cmp ecx, edx
	je .return
; preserve the callee-saved registers
	push ebx
; clear the second buffer register
	xor ebx, ebx
.loop:
; compare the 2 current characters
	mov al, [ecx]
	mov bl, [edx]
	sub eax, ebx
	jnz .restore_callee_saved_registers
; check if the end of the second string is reached
	test bl, bl
	jz .restore_callee_saved_registers
; step to the next character of each string
	inc ecx
	inc edx
; repeat until either the current characters differ or the end of one of the strings is reached
	jmp .loop
.restore_callee_saved_registers:
	pop ebx
.return:
	ret
