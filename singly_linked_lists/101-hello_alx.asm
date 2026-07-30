global main
extern printf

section .data
	msg db "Hello, Frontier", 10, 0

section .text
main:
	push rbp
	mov rbp, rsp
	lea rdi, [rel msg]
	xor eax, eax
	call printf
	mov eax, 0
	pop rbp
	ret
