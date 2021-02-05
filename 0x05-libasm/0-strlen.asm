BITS 64

    global asm_strlen; EXPORT our function 'asm_strlen'
    section .text; Code section

asm_strlen:
    mov rax, 0
while:
    cmp byte [rdi + rax], 0 ; *(s+c)!='/0' rdi use with firt parameter the stdin in C
    je end
    inc rax
    jmp while
end:
    ret