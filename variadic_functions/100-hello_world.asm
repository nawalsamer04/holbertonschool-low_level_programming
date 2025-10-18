; 100-hello_world.asm — print "Hello, World\n" using Linux syscalls (x86_64)

section .data
msg:    db "Hello, World", 10    ; The string (10 is '\n')
len     equ $ - msg              ; Length of the string

section .text
global _start

_start:
    ; write(1, msg, len)
    mov     rax, 1        ; syscall number for write
    mov     rdi, 1        ; file descriptor 1 = stdout
    mov     rsi, msg      ; pointer to the string
    mov     rdx, len      ; number of bytes to print
    syscall

    ; exit(0)
    mov     rax, 60       ; syscall number for exit
    xor     rdi, rdi      ; exit code 0
    syscall
