BITS 64

    global asm_strchr:

    section .text

asm_strchr:
	; the order of registers used is: %rdi, %rsi, %rdx, %rcx, %r8, and %r9
while:
    mov r8b, [rdi];pasamos a registro de 8 bites
    cmp r8b, sil;como el argumento es de 1 bit llega en sil
    je igual;salta si igual
	cmp r8b, 0;verificamos que no haya llegado al final de el string
    je noesta;salta si igual
    inc rdi;pasamos a la siguiente letra
    jmp while; salta a while:

igual:
	mov rax, rdi
    ret; salida

noesta:
    mov eax, 0;seteamos eax con 0
    ret; salida
