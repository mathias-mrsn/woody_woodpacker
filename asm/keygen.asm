BITS 64
; ARCH INTEL x86_64

%define SYS_READ    0x0
%define SYS_WIRTE   0x1
%define SYS_OPEN    0x2
%define SYS_CLOSE   0x3

section .data
    urandom db "/dev/urandom", 0        ; urandom = label, db = define bytes, path, next bytes
    urandom_len equ $ - urandom         ; urandom_len = labal, equ = equal to, ($ - urandom) = current addr - urandom addr

section .text
    global keygen

keygen:
    
    ; Initialize keygen function
    push rsi
    push rdi
    push rbp
    mov rbp, rsp
    sub rsp, 0x10

    ; RBP:
    ; + 0x0 - 0x8 : Old RBP
    ; + 0x8 - 0x10 : Key size
    ; + 0x10 - 0x18 : Buffer address
    ; - 0x4 - 0x0 : File descriptor

    ; Open file [open("/dev/urandom")]
    xor rsi, rsi 
    mov rdi, urandom 
    mov rax, SYS_OPEN 
    syscall

    ; Read file [read(fd, buffer, size)]
    mov [rbp - 0x4], eax
    mov edx, [rbp + 0x8]
    mov rsi, [rbp + 0x10]
    movzx rdi, byte [rbp - 0x4]
    mov rax, SYS_READ 
    syscall

    ; Close file [close(fd)]
    mov rdi, [rbp - 0x4]
    mov rax, SYS_CLOSE
    syscall

_end:
    leave
    pop rdi
    pop rsi
    ret
