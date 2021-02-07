BITS 64
	global asm_strncmp	; export 'asm_strncmp' function

	section .text

asm_strncmp:


strncmp_loop:
	cmp rdx, 0h
	je equal
	mov r10b,	[rdi]
	mov r15b,	[rsi]
	cmp r10b,	r15b
	jl less
	jg greater
	cmp r10b,	0h
	je equal
	inc rdi
	inc rsi
	dec rdx
	jmp strncmp_loop

less:
	mov eax, -1h
	ret

greater:
	mov eax, 1h
	ret

equal:
	mov eax, 0h

	