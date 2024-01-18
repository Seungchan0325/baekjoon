section .data
	msg: db "Hello World!", 0xa, 0

section .text
    global main
	extern printf

main:
	push rbp
	mov rbp, rsp
	xor rax, rax

	mov rdi, msg
	mov rsi, rax
	mov rax, 0
	call printf

	xor rax, rax
	pop rbp
	ret