global find_word
extern string_equals
section .text

find_word:
	xor rax, rax
.loop:
	test rsi, rsi
	jz .no
	
	push rdi
	push rsi
	add rsi, 8
	call string_equals
	pop rsi
	pop rdi
	test rax, rax
	jnz .yes

	mov rsi, [rsi]
	jmp .loop
.no:
	xor rax, rax
	ret
.yes:
	mov rax, rsi
	ret
