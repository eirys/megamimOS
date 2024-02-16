global strCpy

section .data

section .bss

section .text
; Copy a null-terminated string to another string.
; The destination string is assumed to be large enough
; to hold the source string, including its null terminator.
;
; Parameters:
; [esp + 4]: the address of the destination string to copy to. (assumed to be a valid address)
; [esp + 8]: the address of the source string to copy from. (assumed to be a valid address)
;
; Return:
; eax: the address of the destination string.
strCpy:
; put the arguments into registers
	mov eax, [esp + 4]; the address of the source string
	mov edx, [esp + 8]; the address of the destination string
; check if we need to compute the copy
	cmp eax, edx
	jz .return
; preserve the callee-saved registers
	push ebx
; set a second pointer to the destination string that will iterate over it
	mov ecx, eax
.loop:
; copy the current character from the source string to the destination string
	mov bl, [edx]
	mov [ecx], bl
; check if the end of the source string has been reached
	test bl, bl
	jz .restore_callee_saved_registers
; step to the next character
	inc edx
	inc ecx
; repeat until the end of the source string is reached
	jmp .loop
.restore_callee_saved_registers:
	pop ebx
.return:
	ret
