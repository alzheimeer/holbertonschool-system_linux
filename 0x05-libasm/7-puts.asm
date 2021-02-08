BITS 64

    global asm_puts

    extern asm_strlen

    section .text

    ;rax(rdi, rsi, rdx, r10, r8, r9)

asm_puts:

    call asm_strlen

    push rsi                    ; Store values of $rsi and $rdx
    push rdx

    mov rdx, rax                ; Pass length
    mov rax, 1                  ; Write syscall
    mov rsi, rdi                ; Adress of buf
    mov rdi, 1                  ; File descriptor, STDOUT
    syscall

end:

    pop rdx                      ; Restore rdx
    pop rsi                      ; Restore rsi

    ret
