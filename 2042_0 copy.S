section .data
    i1: db "%lld",0
    i3: db "%lld %lld %lld",0
    o1: db "%lld",10,0

    n: times 8 db 0
    m: times 8 db 0
    k: times 8 db 0

    tree: times 32000000 db 0

section .text
    global main
    extern scanf
    extern printf

; start, end, index, pos, value
update:
    push rbp
    mov rbp, rsp
    sub rsp, 32

    mov eax, DWORD [rbp + 40] ; end
    cmp eax, DWORD [rbp + 24] ; pos
    jl update_return

    mov eax, DWORD [rbp + 24] ; pos
    cmp eax, DWORD [rbp + 48] ; start
    jl update_return

    mov eax, DWORD [rbp + 48]
    cmp eax, DWORD [rbp + 40]
    je update_base_case

    mov eax, DWORD [rbp + 48]
    add eax, DWORD [rbp + 40]
    shr eax, 1
    mov DWORD [rbp - 4], eax

    mov eax, DWORD [rbp + 48]
    push rax
    mov eax, DWORD [rbp - 4]
    push rax
    mov eax, DWORD [rbp + 32]
    add eax, eax
    push rax
    mov eax, DWORD [rbp + 24]
    push rax
    mov rax, QWORD [rbp + 16]
    push rax
    mov rax, 0
    call update
    add rsp, 40

    mov eax, DWORD [rbp - 4]
    add eax, 1
    push rax
    mov eax, DWORD [rbp + 40]
    push rax
    mov eax, DWORD [rbp + 32]
    add eax, eax
    add eax, 1
    push rax
    mov eax, DWORD [rbp + 24]
    push rax
    mov rax, QWORD [rbp + 16]
    push rax
    mov rax, 0
    call update
    add rsp, 40

    mov ebx, DWORD [rbp + 32]
    add ebx, ebx
    mov rax, QWORD [tree + 8*rbx]
    add ebx, 1
    add rax, QWORD [tree + 8*rbx]
    mov ebx, DWORD [rbp + 32]
    mov QWORD [tree + 8*ebx], rax

    jmp update_return

update_base_case:
    mov ebx, DWORD [rbp + 32]
    mov rax, QWORD [rbp + 16]
    mov QWORD [tree + 8*ebx], rax
update_return:
    mov rax, 0
    leave
    ret

; start, end, index, left, right
query:
    push rbp
    mov rbp, rsp
    sub rsp, 32

    mov eax, DWORD [rbp + 40] ; end
    cmp eax, DWORD [rbp + 24] ; left
    jl query_base_case_2

    mov eax, DWORD [rbp + 16] ; right
    cmp eax, DWORD [rbp + 48] ; start
    jl query_base_case_2
 
    mov eax, DWORD [rbp + 24] ; left
    cmp eax, DWORD [rbp + 48] ; start
    jg normal

    mov eax, DWORD [rbp + 40] ; end
    cmp eax, DWORD [rbp + 16] ; right
    jg normal

    jmp query_base_case

normal:
    mov eax, DWORD [rbp + 48]
    add eax, DWORD [rbp + 40]
    shr eax, 1
    mov DWORD [rbp - 4], eax

    mov eax, DWORD [rbp + 48]
    push rax
    mov eax, DWORD [rbp - 4]
    push rax
    mov eax, DWORD [rbp + 32]
    add eax, eax
    push rax
    mov eax, DWORD [rbp + 24]
    push rax
    mov eax, DWORD [rbp + 16]
    push rax
    mov rax, 0
    call query
    add rsp, 40

    mov QWORD [rbp - 12], rax

    mov eax, DWORD [rbp - 4]
    add eax, 1
    push rax
    mov eax, DWORD [rbp + 40]
    push rax
    mov eax, DWORD [rbp + 32]
    add eax, eax
    add eax, 1
    push rax
    mov eax, DWORD [rbp + 24]
    push rax
    mov eax, DWORD [rbp + 16]
    push rax
    mov rax, 0
    call query
    add rsp, 40

    add rax, QWORD [rbp - 12]

    jmp query_return

query_base_case:
    mov ebx, DWORD [rbp + 32]
    mov rax, QWORD [tree + 8*ebx]
    jmp query_return
query_base_case_2:
    mov rax, 0
    jmp query_return
query_return:
    leave
    ret

main:
	push rbp
    mov rbp, rsp
    sub rsp, 32

    mov rdi, i3
    lea rsi, [n]
    lea rdx, [m]
    lea rcx, [k]
    mov rax, 0
    call scanf

    mov DWORD [rbp - 4], 0
    jmp input_check_condition
input_loop:
    mov rdi, i1
    lea rsi, [rbp - 12]
    mov rax, 0
    call scanf

    push 0
    mov rax, QWORD [n]
    sub rax, 1
    push rax
    push 1
    mov eax, DWORD [rbp - 4]
    push rax
    mov rax, QWORD [rbp - 12]
    push rax
    mov rax, 0
    call update
    add rsp, 40

    add DWORD [rbp - 4], 1

input_check_condition:
    mov rax, [n]
    cmp eax, DWORD [rbp - 4]
    jg input_loop

    mov DWORD [rbp - 4], 0
query_input_loop:
    mov rdi, i3
    lea rsi, [rbp - 12]
    lea rdx, [rbp - 20]
    lea rcx, [rbp - 28]
    mov rax, 0
    call scanf

    mov rax, [rbp - 12]
    cmp rax, 1
    je _update
    
    cmp rax, 2
    je _query

_update:
    push 0
    mov rax, QWORD [n]
    sub rax, 1
    push rax
    push 1
    mov rax, QWORD [rbp - 20]
    sub rax, 1
    push rax
    mov rax, QWORD [rbp - 28]
    push rax
    mov rax, 0
    call update
    add rsp, 40

    add DWORD [rbp - 4], 1
    jmp query_input_check_condition
_query:
    push 0
    mov rax, QWORD [n]
    sub rax, 1
    push rax
    push 1
    mov rax, QWORD [rbp - 20]
    sub rax, 1
    push rax
    mov rax, QWORD [rbp - 28]
    sub rax, 1
    push rax
    mov rax, 0
    call query
    add rsp, 40
    
    mov rdi, o1
    mov rsi, rax
    mov rax, 0
    call printf

    add DWORD [rbp - 4], 1
    jmp query_input_check_condition
query_input_check_condition:
    mov rax, [m]
    add rax, [k]
    cmp eax, DWORD [rbp - 4]
    jg query_input_loop

	mov rax,0
    leave
    ret