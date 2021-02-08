BITS 64

    global asm_strncasecmp

    section .text

asm_strncasecmp:
    push rbp
    mov rbp, rsp
    push r8
    push r9
    push rcx
    xor rcx, rcx
    xor eax, eax
    xor r8d, r8d
    xor r9d, r9d

loop_strcmp:
    mov r8b, BYTE [rdi + rcx]
    mov r9b, BYTE [rsi + rcx]
    cmp r8b, 65
    jl convert
    cmp r8b, 90
    jg convert
    add r8b, 32

convert:
    cmp r9b, 65
    jl continue
    cmp r9b, 90
    jg continue
    add r9b, 32

continue:
    test r8b, r8b
    je end
    test r9b, r9b
    je end
    inc rcx
    cmp rcx, rdx
    je end
    cmp r8b, r9b
    je loop_strcmp
    jmp end

end:
    mov eax, r8d
    sub eax, r9d
    pop rcx
    pop r9
    pop r8
    mov rsp, rbp
    pop rbp
    ret
