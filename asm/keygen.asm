BITS 64
; ARCH INTEL x86_64

section .data
    urandom db "/dev/urandom", 0        ; urandom = label, db = define bytes, path, next bytes
    urandom_len equ $ - urandom         ; urandom_len = labal, equ = equal to, ($ - urandom) = current addr - urandom addr

    key db 32
    key_len equ 32

section .bss
    fd resq 1

section .text
    global _keygen

_keygen:
    xor rsi, rsi                        ; O_RONLY
    mov rdi, urandom                    ; filepath
    mov rax, 0x2                        ; syscall open
    syscall

    mov [fd], rax
    mov rdx, key_len
    mov rsi, key
    mov edi, [fd]
    xor rax, rax 
    syscall

    mov rdi, [fd]
    mov rax, 0x3
    syscall

    mov rdx, key_len
    mov rsi, key
    mov edi, 1
    mov eax, 0x1
    syscall

    mov rax, key
    ret
