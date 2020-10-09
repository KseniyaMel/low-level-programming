global find_word
extern string_equals
section .text

find_word:
	xor rax, rax
.loop:
	test rsi, rsi
	jz .end
	
	push rdi
	add rsi, 8
	call sring_equals
	pop rdi
	test rax, rax
	jnz .end

	mov rsi, [rsi-8]
	jmp .loop
.end:
	mov rax, rsi
	ret
