BITS 64

    global asm_strcmp:

    section .text

asm_strcmp:

while:
    mov r8b, BYTE [rdi]
    mov r9b, BYTE [rsi]
    inc rdi
	inc rsi
    cmp r8b, r9b
    jl menor
    jg mayor
	cmp r8b, 0
    je igual
    jmp while

mayor:
    mov eax, 1
    ret

menor:
    mov eax, -1
    ret

igual:
	mov eax, 0
    ret
