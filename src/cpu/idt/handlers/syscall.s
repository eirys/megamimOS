global _syscall

.section .text
_syscall:
    push eax
    push ebx
    push ecx
    push edx
    push esi
    push edi
    push ebp

    push gs
    push fs
    push es
    push ds

    push esp



    iretd