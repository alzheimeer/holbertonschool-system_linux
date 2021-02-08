BITS 64

section .data

    digits    db "0123456789",0

section .bss

    buf     resb 12             ; Charcter array with 11 bytes

extern asm_putc
global asm_puti

section .text

    ;; rax(rdi, rsi, rdx, r10, r8, r9)
    ;; size_t asm_puti(int n);
    ;; @edi: n
asm_puti:

    push rbp
    mov rbp, rsp
    push r8
    push r9
    push r10
    ;; push r11
    push rcx
    push rsi
    push rbx

    mov r8, buf                 ; @r8: is character buffer
    mov r9, digits              ; @r9: char array of characters
    xor rcx, rcx                ; Number of characters
    mov r10, 10                 ; Position in buffer mov BYTE [r8 + r10], 65
    mov BYTE [r8 + 11], 0       ; Put null byte at the end of array
    movsx rdi, edi              ; Fill rdi's 32 bits with zeros, good for handling overflows
    mov rbx, 10                 ; Base
    ;; mov r11, 11                 ; Length of @buf
    xor sil, sil                ; Sign flag

    cmp rdi, 0
    jl negative

continue:

    mov rax, rdi

do:

    xor rdx, rdx                ; to zero-extend RAX into RDX:RAX.
    div rbx                     ; @rdx will contain remainder, @rax will contain rdi/10
    mov dl, BYTE [r9 + rdx]     ; use base tabel to choose right symbol
    mov BYTE [r8 + r10], dl
    inc rcx

while:

    test rax, rax
    jz check_sign
    dec r10
    jmp do

negative:

    imul rdi, -1
    mov sil, -1
    jmp continue

check_sign:

    cmp sil, -1
    jne print
    dec r10
    mov BYTE [r8 + r10], '-'     ; Put '-' sign
    inc rcx

print:                          ; Better to call write function once, but requirements don't allow it

    lea r8, [r8 + r10]
    xor r9, r9                  ; Reuse for indexing @r8

print_loop:

    mov dl, BYTE [r8 + r9]
    test dl, dl
    jz end
    movzx rdi, dl
    call asm_putc
    inc r9
    jmp print_loop

end:

    mov rax, r9

    pop rbx
    pop rsi
    pop rcx
    ;; pop r11
    pop r10
    pop r9
    pop r8

    mov rsp, rbp
    pop rbp

    ret
