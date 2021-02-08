BITS 64

	global asm_memcpy

	section .text

asm_memcpy:

while:
	test rdx, rdx;un AND origen y destino no save, modifica flaqs
	je end
	mov bl, BYTE[rsi]
	mov BYTE[rdi], bl
	inc rdi
	inc rsi
	dec rdx
	jmp while
end:
	ret
