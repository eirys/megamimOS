section .megamimOS_handle
align 4
    ; magic
    dd 0x1BADB002

    ; flags
    dd 0x0

    ; checksum
    dd 0xE4524FFE

; -----------------------
; Stack
section .bss
align 16 ; 16-byte alignment for the stack. Corresponds to the SSE alignment.
    resb 1638
stack_top:

; -----------------------
section .text
global megamimOS_entrypoint
extern megamimOS_cpp

; This will be called by Grub.
megamimOS_entrypoint:
    ; Check if the multiboot magic number is valid.
    cmp     eax,        0x2BADB002
    jne     .loop_inf

    ; Setup the stack.
    mov     esp,        stack_top

    ; TODO: copy GDT at `0x0800`

    ; Call the C++ entry point.
    ; We need to save ebx because it is passed down by Grub and
    ; contains the info structure.
    push    ebx
    call    megamimOS_cpp

.loop_inf:
    hlt
    jmp     .loop_inf