section .megamimOS_handle
global megamimOS_multiboot_header
megamimOS_multiboot_header:
align 4
    ; magic
    dd 0x1BADB002

    ; flags
    dd 0x0

    ; checksum
    dd 0xE4524FFE


; -----------------------
section .text

global megamimOS_entrypoint

extern megamimOS_cpp

; This will be called by Grub.
megamimOS_entrypoint:
    ; cmp     eax,        0x1BADB002
    ; jne     .loop_inf
    ; call    megamimOS_cpp

.loop_inf:
;     hlt
;     jmp     .loop_inf