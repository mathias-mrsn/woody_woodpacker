BITS 64

%define S_LEN 0x100 ; 256
%define SYS_EXIT 0x3c
%define SYS_WRITE 0x01

section .data
    text db "This is a text", 0
    text_len equ $-text

    key db "This is a password", 0
    key_len equ $-key

section .text
    global _start

; RSP = S array
; r8 = index
_start:

    ; Initialize _start function
    push r8
    push r9
    push r11
    push rbp
    mov rbp, rsp
    sub rsp, S_LEN + 0x10

    ; Initialize S array (S[i] = i)
    xor r8, r8
    .fill:
    mov [rsp + r8], r8
    inc r8
    cmp r8, S_LEN
    jne .fill

    ; Key Scheduling Algorithm (KSA)
    xor r8, r8
    xor r9, r9

    .ksa:
    movzx rcx, byte [rsp + r8]
    add r9, rcx
    mov rax, r8
    mov ecx, key_len 
    xor rdx, rdx
    div ecx
    mov rdi, key
    add rdi, rax 
    movzx eax, byte [rdi]
    add r9, rax

    mov rax, r9
    xor rdx, rdx
    mov ecx, S_LEN
    div ecx
    mov r9, rax

    ; Swap
    mov al, [rsp + r8]
    mov cl, [rsp + r9]
    mov [rsp + r9], al
    mov [rsp + r8], cl
 
    inc r8
    cmp r8, S_LEN
    jne .ksa

_end:

   
    ; mov rdx, S_LEN
    ; mov rsi, rsp
    ; mov rdi, 1
    ; mov rax, SYS_WRITE
    ; syscall

    ; Pop saved registers
    pop r8
    pop r9
    pop r11
    pop rbp
    add rsp, S_LEN + 0x10
    mov al, SYS_EXIT
    syscall





