BITS 64

    global asm_strcmp:

    section .text

asm_strcmp:

           

loop_strcmp:
    mov r8b, BYTE [rdi + rcx]
    mov r9b, BYTE [rsi + rcx]
    inc rdi
	inc rsi
    test r8b, r8b
    je check_null              
    test r9b, r9b
    je set_one               
    cmp r8b, r9b
    je loop_strcmp             
    jmp compare

check_null:
    test r9b, r9b
    je end_strcmp
    jmp set_negative

compare:
    cmp r8b, r9b
    jl set_negative
    jmp set_one

set_one:
    mov eax, 1
    ret

set_negative:
    mov eax, -1            
    ret

end_strcmp:
	mov eax, 0
    ret
