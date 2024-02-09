section .megamimOS_handle
align 4
    ; magic
    dd 0x1BADB002

    ; flags
    dd 0x0

    ; checksum
    dd 0xE4524FFE

align 8
.gdt_start:
    ; Null Segment. Don't ask.
    dq 0x0

    ; Kernel Code Segment
    dq 0x00cf9a000000ffff
    ; Kernel Data Segment
    dq 0x00cf92000000ffff
    ; Kernel Stack Segment
    dq 0x00cf92000000ffff

    ; User Code Segment
    dq 0x00cffa000000ffff
    ; User Data Segment
    dq 0x00cff2000000ffff
    ; User Stack Segment
    dq 0x00cff2000000ffff
.gdt_end:

.gdt_descriptor:
    dw .gdt_end - .gdt_start - 1 ; Size of the GDT.
    dd .gdt_start                ; Start address of the GDT.

; -----------------------
; Stack
section .bss
align 16 ; 16-byte alignment for the stack. Corresponds to the SSE alignment.
    resb 32768 ; 32KB stack.
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

    ; Load the GDT.
    lgdt    [.gdt_descriptor]

    mov     ax,         0x10    ; Moves 0x10 to the data segment register.
    mov     ds,         ax      ; Indicates the data segment offset.
    mov     es,         ax
    mov     fs,         ax
    mov     gs,         ax
    mov     ss,         ax

    ; Jump to the code segment.
    ; Necessary to reload the code segment register.
    jmp     0x08:.reload_CS
.reload_CS:

    ; Call the C++ entry point.
    ; We need to save ebx because it is passed down by Grub and
    ; contains the info structure.
    push    ebx
    call    megamimOS_cpp

.loop_inf:
    hlt
    jmp     .loop_inf