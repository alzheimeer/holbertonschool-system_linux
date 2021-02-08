BITS 64

	global asm_strspn

    section .text

asm_strspn:
	push rbp
	mov rbp, rsp
	push rbx
	push rcx
	push r11
	mov rcx, 0
	mov r11, 0
counter_1:
	cmp byte [rdi + rcx], 0
	je end
	mov rbx, 0
counter_2:
	mov r11b, [rsi + rbx]
	cmp r11b, 0
	je end
	inc rbx
	cmp r11b, [rdi + rcx]
	jne counter_2
	inc rcx
	jmp counter_1
end:
	mov rax, rcx
	pop r11
	pop rcx
	pop rbx
	mov rsp, rbp
	pop rbp
	ret
