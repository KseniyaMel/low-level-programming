%include "words.inc"


global _start
extern find_word
extern string_length
extern print_string
extern read_word
extern exit

section .data
	m_fail1: db 'The word is too long', 0
	m_fail2: db 'There is not', 0
	buffer: times 255 db 0

section .text
print_err:
	mov rsi, rdi
	call string_length
	mov rdx, rax
	mov rax, 1
	mov rdi, 3
	syscall
	ret
_start:
	mov rdi, buffer
	mov rsi, 255
	call read_word
	test rax, rax
	jz .fail1
	
	mov rdi, rax
	mov rsi, last
	call find_word
	test rax, rax
	jz .fail2

	lea rdi, [rax+8]	
	call string_length
	add rdi, rax	
	inc rdi
	call print_string
	call exit

.fail1:
	mov rdi, m_fail1
	call print_string
	call exit
	
.fail2:
	mov rdi, m_fail2
	call print_string
	call exit
	
