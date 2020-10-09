
global exit
global string_length
global print_string
global print_char
global print_newline
global print_uint
global print_int
global read_char
global read_word
global string_equals
global string_copy
global parse_int
global parse_uint

section .text

exit:
	mov rax, 60
	syscall
	ret

string_length:
	xor rax, rax
.loop:
	cmp byte [rdi+rax],0
	je .end
	inc rax
	jmp .loop
.end: 
	ret

print_string:
	xor rax, rax
	mov rsi, rdi
	call string_length
	mov rdx, rax
	mov rax, 1
	mov rdi, 1
	syscall
	ret

print_char:
	push rdi
	mov rax, 1
	mov rsi, rsp
	mov rdi, 1
	mov rdx, 1
	syscall
	pop rdi
	ret

print_newline:
	mov rdi, 0xA
	call print_char
	ret

print_uint:
	xor rax, rax
  xor rcx, rcx
  mov rax, rdi
  mov rdi, 10
  push 0x00
.loop:
  xor rdx, rdx
  div rdi
  add rdx, '0'
  push rdx
  test rax, rax
  jnz .loop
.out:
  pop rdi
  cmp rdi, 0x00
  je .exit
  call print_char
  jmp .out
.exit:
  ret
  
print_int:
	test rdi, rdi
	jns print_uint
	push rdi
	mov rdi, '-'
	call print_char
	pop rdi
	neg rdi
	jmp print_uint

read_char:
	xor rax, rax
	xor rdi, rdi
	mov rdx, 1
	push 0
	mov rsi, rsp
	syscall
	pop rax
	ret

read_word:
	mov r9, rdi
	mov r10, rsi
	push r9
	xor r8, r8
	mov r8, 0
.loop1:
	push r9
	push r10
	push r8
	call read_char
	pop r8
	pop r10
	pop r9
	test rax, rax
	jz .end
	cmp rax, ' '
	jle .loop1
.loop2:
	cmp  r8, r10
	jae .not
	mov [r9], al
	inc r9
	inc r8
	push r9
	push r10
	push r8
	call read_char
	pop r8
	pop r10
	pop r9
	cmp rax, ' '
	jg .loop2
.end:
	mov byte[r9], 0x00
	pop r9
	mov rax, r9
	mov rdx, r8
	ret
.not:
	pop r9
	mov byte[r9], 0x00
	mov rax, 0
	ret

string_equals:
  push rdi
  push rsi
	call string_length
	pop rsi
  pop rdi
  mov rcx, rax
	push rdi
  push rsi
	mov rdi, rsi
	call string_length
	pop rsi
  pop rdi
	cmp rcx, rax
	js .not
	cld
	repe cmpsb
	jecxz .yes
.not:
	mov rax, 0x00
	ret
.yes:
	mov rax, 0x01
	ret

string_copy:
	xor rax, rax
.loop:
	xor rcx, rcx
	mov cl, byte[rdi]
	mov byte[rsi], cl
	cmp rsi, rdx                           
	jz .exit
	inc rdi
	inc rsi
	test rcx, rcx
	jnz .loop
.exit:
	xor rax, rax
	ret

parse_uint:
	xor rax, rax
	xor r9, r9
	xor r8, r8
	mov rcx, 10
	push r13
	mov r13, 0

.loop2:
	cmp byte[rdi+r9], 48
  jb .no
  cmp byte[rdi+r9], 57
  ja .no
	xor rdx, rdx
	mul rcx
	mov r8b, byte[rdi+r9]
	sub r8b, '0'
	add rax, r8
	inc r13
	inc r9
	jmp .loop2
	
.no:
	cmp r13, 0
	jne .end
	xor rax, rax
	xor rdx, rdx
	ret
.end:	
	mov rdx, r13
	pop r13
	ret
	

parse_int:	
	cmp byte[rdi+r9], '-'
	jne parse_uint
	inc rdi
	call parse_uint
  inc rdx
  neg rax
  ret
