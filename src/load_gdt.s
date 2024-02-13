global load_gdt

section .text
load_gdt:
    ; Load the GDT.
    mov     eax,       [esp + 4]  ; Moves the address of the GDT to the eax register.
    lgdt    [eax]

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