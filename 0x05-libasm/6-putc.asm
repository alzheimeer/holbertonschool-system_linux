  
BITS 64

    global asm_putc

    section .text

asm_putc:
    mov rax, 1                  ; write syscall
    mov rsi, rsp                ; Character
    mov rdi, 1                  ; stdout
    mov rdx, 1                  ; one byte
    syscall
    ret
