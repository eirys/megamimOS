global enable_paging

section .text
enable_paging:
    mov     eax,    [esp + 4]
    mov     cr3,    eax

    mov     eax,    cr4
    or      eax,    0x00000010
    mov     cr4,    eax

    mov     eax,    cr0
    ; Enable paging and Write-Protect for kernel
    or      eax,    0x80010000
    mov     cr0,    eax

    ret