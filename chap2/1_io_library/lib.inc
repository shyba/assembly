section .data
fail_msg: db 'panic: buffer too small', 0
char_buf: db 0
numbers: db '0123456789'

section .text

_write: ; whatever is on rsi, rdx len!
    mov rax, 1 ; write
    mov rdi, 1 ; stdout
    syscall
    ret

_fail:
    mov rsi, fail_msg
    mov rdx, 1
    call _write

string_length:
    xor rax, rax
    .loop:
        cmp byte[rdi+rax], 0
        jz .done
        inc rax
        jmp .loop
    .done:
        ret

print_string:
    call string_length
    mov rdx, rax
    mov rsi, rdi
    call _write
    ret

string_copy:
    call string_length
    cmp rdx, rax
    jl _fail
    mov rdx, rax
    xor rax, rax
    .loop:
        mov al, byte[rdi+rdx]
        mov byte[rsi+rdx], al
        dec rdx
        cmp rdx, 0
        jl .exit
        jmp .loop
    .exit:
        ret


print_char:
    xor rax, rax
    mov [char_buf], rdi
    mov rsi, char_buf
    mov rdx, 1
    call _write
    ret

print_newline:
    xor rax, rax
    ret


print_uint:
    mov rax, rdi ; store quotient, which starts as the argument rdi
    mov r10, 10
    push 0
    .loop:
        xor rdx, rdx ; clean rdx as its used on divisor (rdx:rax)
        div r10 ; divide by 10
        mov r9b, byte[numbers+rdx]
        push r9
        cmp rax, 0 ; test quotient
        jnz .loop ; repeat if its not zero
    .print_loop:
        pop rdi
        cmp rdi, 0
        jz .exit
        call print_char
        jmp .print_loop
    .exit:
        ret


print_int:
    xor rax, rax
    ret

string_equals:
    xor rax, rax
    ret


read_char:
    xor rax, rax
    mov rdi, 1 ; stdint
    mov rsi, char_buf
    mov rdx, 1 ; size
    syscall
    mov ax, [char_buf]
    ret 

read_word:
    ret

; rdi points to a string
; returns rax: number, rdx : length
parse_uint:
    xor rax, rax
    ret

; rdi points to a string
; returns rax: number, rdx : length
parse_int:
    xor rax, rax
    ret 
