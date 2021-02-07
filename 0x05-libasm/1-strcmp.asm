BITS 64
	global asm_strcmp

	section .text

asm_strcmp:

while:
	mov r8b, [rdi] ;pasamos a registro de 8 bit
	mov r9b, [rsi] ;pasamos a registro de 8 bit
	cmp r8b, r9b ;comparamos las dos letras
	jl menor ;salta si es menor A<B (con signo)
	jg mayor ;salta si mayor A>B (con signo)
	cmp r8b, 0 ;verificamos que la letra no sea 0
	je igual ;salta si igual	A=B
	inc rdi ;pasamos a la siguiente letra
	inc rsi ;pasamos a la siguiente letra
	jmp while ;volvemos a empezar el loop
menor:
	mov eax, -1
    ret
mayor:
	mov eax, 1
	ret
igual:
	mov eax, 0
