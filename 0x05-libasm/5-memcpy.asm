BITS 64

	global asm_memcpy

	section .text

asm_memcpy:

while:
	cmp rdx, rdx
	je end
	mov bl, BYTE[rsi]
	mov BYTE[rdi], bl
	inc rdi
	inc rsi
	dec rdx
	jmp while
end:
	ret
