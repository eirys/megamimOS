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
; preserve the callee-saved registers
	push ebx
; load the parameters into registers
	mov eax, [esp + 8]
	mov ebx, [esp + 12]
	mov ecx, eax
.loop:
; copy the current character from the source string to the destination string
	mov dl, [ebx]
	mov [ecx], dl
; check if the end of the source string has been reached
	test dl, dl
	jz .end_of_loop
; step to the next character
	inc ebx
	inc ecx
; repeat until the end of the source string is reached
	jmp .loop
.end_of_loop:
; restore the callee-saved registers
	pop ebx
	ret
