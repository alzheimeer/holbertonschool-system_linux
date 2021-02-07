BITS 64

    global asm_strcmp:
	; the order of registers used is: %rdi, %rsi, %rdx, %rcx, %r8, and %r9
    section .text

asm_strcmp:

while:
	cmp rdx, 0;comparamos el 3 argumento con 0
	je equal; si es 0 acabo la comparacion
    mov r8b, BYTE [rdi];pasamos a registro de 8 bit
    mov r9b, BYTE [rsi];pasamos a registro de 8 bit
    inc rdi;pasamos a la siguiente letra
	inc rsi;pasamos a la siguiente letra
    cmp r8b, r9b;comparamos las dos letras
    jl menor;salta si es menor A<B (con signo)
    jg mayor;salta si mayor A>B (con signo)
	cmp r8b, 0;verificamos que no haya llegado al final de el string
    je igual;salta si igual
	dec rdx; decrementamos en uno rdx
    jmp while; salta a while:

mayor:
    mov eax, 1;seteamos eax con 1
    ret; salida

menor:
    mov eax, -1;seteamos eax con -1
    ret; salida

igual:
	mov eax, 0;seteamos eax con 0
    ret; salida