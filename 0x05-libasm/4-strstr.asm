	bits 64

	section .text			; Code section
	global asm_strstr		; Exporting the function name

	section .data

asm_strstr:
	mov r9, rdi		        ; save the 1st arg in r9 memory
	mov r10, rsi		    ; start the 2nd arg in r10 memory
	mov r9d, dword 0 	    ; start the iterator 1 in 0
	mov r10d, dword 0	    ; start the iterator 2 in 0
	mov r11, 0				; set to 0 the r11 register
	mov r12, 0				; set to 0 the r12 register

	mov rcx, 0
	mov cl, [rsi]
	cmp cl, 0x00
	je ret_same

while:					    ; start loop
	inc dword r9d		    ; increment by 1 the iterator 1
	mov r11d, r9d		    ; copy the iter value to r11

	mov rcx, 0				; set to 0 the rbx register
	mov cl, [rsi + r12]		; set a single byte to rcx register
	cmp cl, 0x00			; compare the previous byte with null char
	je equ_c                ; if they are the same go out because a haystack

	mov rbx, 0				; set to 0 the rbx register
	mov bl, [rdi + r11 - 1]	; set a single byte to rbx register
	cmp bl, 0x00			; compare the previous byte with null char
	je while2				; if they are the same go out because any haystack was found

	cmp bl, cl				; if not, compare the first arg byte with the second arg byte
	je inc_arg_2			; if they are equal continue the comparison
	mov r12, 0				; else set the comparison arg2 from begining
	mov r10d, r12d
	jmp while				; and continue the loop

while2:						; else go out of loop
	mov rax, 0				; set return value to 0

end_c:						; end
	mov rsi, r10		    ; restore previous value of rsi
	ret						; return the len value

equ_c:						; if they are equal set the pointer to that byte
	mov rax, r15	        ; set the pointer in return value
	jmp end_c				; end program

inc_arg_2:					; increment the byte comparison
	cmp r12, 0x00			; if it is the first byte of the substring
	je save_p				; save the begining of substring

inc_next:					; increment the iterator of the 2nd substring
	inc dword r10d		    ; increment by 1
	mov r12d, r10d		    ; and paste in the register
	jmp while				; come back to the funtion was call

save_p:						; save the beginig of substring
	dec r11					; set the right index to the substring
	mov r12, rdi			; copy the arg1 pointer
	add r12, r11			; add the offset pointer
	mov r15, r12        	; save in memory
	inc r11					; set back the iterator 1
	mov r12, 0				; set back the iterator 2
	jmp inc_next			; come back to the function was call

ret_same:					; if the char in arg2 is null
	mov r15, rdi	        ; get the first byte of arg1
	jmp equ_c				; return the program
