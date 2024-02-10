global strLen

section .data

section .bss

section .text
; Calculates the length of a null-terminated string.
;
; Parameters:
;  [esp + 4] - the string to calculate the length of.
;
; Return:
;  eax - length of the string
strLen:
	mov ecx, dword [esp + 4]
	lea eax, [ecx - 1]
.loop:
; step to the next character
	inc eax
; check if the end of the string is reached
	test byte [eax], 0xff
	jnz .loop
; end of loop
	sub eax, ecx
	ret
