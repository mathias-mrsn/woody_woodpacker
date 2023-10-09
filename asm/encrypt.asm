BITS 64

%define S_LEN 0x100 ; 256
%define SYS_EXIT 0x3c
%define SYS_WRITE 0x01

section .data
    text db "This is a text", 0
    text_len equ $-text

    key db "This is a password"
    key_len equ $-key

section .text
    global _start

; RSP = S array
; r8 = index
_start:

    ; Initialize _start function
    push r8
    push r9
    push r10
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
    ; [j = (j + S[i] + key[i % key_len]) % S_LEN]
    movzx rcx, byte [rsp + r8]
    add r9, rcx
    mov rax, r8
    mov ecx, key_len 
    xor rdx, rdx
    div ecx
    mov rdi, key
    add rdi, rdx 
    movzx rax, byte [rdi]
    add r9, rax

    mov rax, r9
    xor rdx, rdx
    mov ecx, S_LEN
    div ecx
    mov r9, rdx

    ; [swap(S[i], S[j])]
    mov al, [rsp + r8]
    mov cl, [rsp + r9]
    mov [rsp + r9], al
    mov [rsp + r8], cl
 
    inc r8
    cmp r8, S_LEN
    jne .ksa

    ; Pseudo-random generation algorithm (PRGA)
    xor r8, r8
    xor r9, r9
    xor r10, r10

    .prga:
    ; [i = (i + 1) % S_LEN]
    inc r8
    mov rax, r8
    mov ecx, S_LEN
    xor rdx, rdx
    div ecx
    mov r8, rdx

    ; [j = (j + S[i]) % N]
    mov dl, [rsp + r8]
    add r9, rdx
    mov rax, r9
    mov ecx, S_LEN
    xor rdx, rdx
    div ecx
    mov r9, rdx

    ; [swap(S[%r8], S[%r9])]
    mov al, [rsp + r8]
    mov cl, [rsp + r9]
    mov [rsp + r9], al
    mov [rsp + r8], cl

    ; [int %rdx = S[(S[%r8] + S[%r9]) % S_LEN]]
    xor rax, rax
    mov al, [rsp + r8]
    add eax, [rsp + r9]
    ;mov ecx, S_LEN
    ;xor rdx, rdx
    ;div ecx
    ;mov rdx, [rsp + rax]









_end:

   
    ; mov rdx, S_LEN
    ; mov rsi, rsp
    ; mov rdi, 1
    ; mov rax, SYS_WRITE
    ; syscall

    ; Pop saved registers
    pop r8
    pop r9
    pop r10
    pop rbp
    add rsp, S_LEN + 0x10
    mov al, SYS_EXIT
    syscall





