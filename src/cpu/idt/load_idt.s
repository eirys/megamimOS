global load_idt

section .text
load_idt:
    ; Load the IDT.
    mov     eax,       [esp + 4]  ; Moves the address of the IDT to the eax register.
    lidt    [eax]

    ret