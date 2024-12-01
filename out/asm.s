	.text
	.globl  prog
prog:
	push %rbp
	mov %rsp, %rbp
	sub $8, %rsp
	lea -8(%rbp), %rax
	push %rax
	mov $3, %rax
	pop %rdi
	mov %rax, (%rdi)
	lea -8(%rbp), %rax
	mov (%rax), %rax
	mov $2, %rax
	push %rax
	mov $4, %rax
	push %rax
	mov $3, %rax
	push %rax
	mov $1, %rax
	pop %rdi
	sub %rdi, %rax
	pop %rdi
	imul %rdi, %rax
	pop %rdi
	cqo
	idiv %rdi
	push %rax
	lea -8(%rbp), %rax
	mov (%rax), %rax
	push %rax
	mov $5, %rax
	pop %rdi
	add %rdi, %rax
	pop %rdi
	add %rdi, %rax
	mov %rbp, %rsp
	pop %rbp
	ret
