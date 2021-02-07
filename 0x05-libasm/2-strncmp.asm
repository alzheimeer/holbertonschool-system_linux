BITS 64
	global asm_strncmp	; export 'asm_strncmp' function

	section .text

asm_strncmp:


while:
	cmp rdx, 0
	je igual
	mov r8b,	[rdi]
	mov r9b,	[rsi]
	cmp r8b,	r9b
	jl menor
	jg mayor
	cmp r8b,	0
	je igual
	inc rdi
	inc rsi
	dec rdx
	jmp while

menor:
	mov eax, -1
	ret

mayor:
	mov eax, 1
	ret

igual:
	mov eax, 0
    ret
