BITS 64
; ARCH INTEL x86_64

%define S_LEN 0x100
%define SYS_EXIT 0x3c
%define SYS_WRITE 0x01

section .text
    global _start

_start:

    ; Initialize _start function
    push rbp
    mov rbp, rsp
    sub rsp, S_LEN + 0x10

    mov rdx, woody_len
    mov rsi, woody
    mov rdi, 1
    mov al, SYS_WRITE
    syscall

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
    mov ecx, key
    xor rdx, rdx
    div ecx
    mov rdi, key_len
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
    movzx rdx, byte [rsp + r8]
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

    ; [int %rax = S[(S[%r8] + S[%r9]) % S_LEN]]
    movzx rax, byte [rsp + r8]
    movzx rcx, byte [rsp + r9]
    add rax, rcx
    mov ecx, S_LEN
    xor rdx, rdx
    div ecx
    movzx rax, byte [rsp + rdx]

    ; [al = rax ^ text[r10]]
    mov rdi, decrypt_addr
    add rdi, r10
    movzx rdx, byte [rdi]
    xor al, dl
    
    ; [cipher[n] = al]
    mov rdi, decrypt_addr
    add rdi, r10
    mov [rdi], al

    inc r10
    cmp r10, decrypt_len
    jne .prga

_end:

    ; jmp old_start
    leave
    mov al, SYS_EXIT
    syscall


; data
woody           db "....WOODY...."
woody_len       equ $-woody

old_start       dq 0x00000000
decrypt_addr    dq 0x00000000
decrypt_len     dq 0x00000000
key             dq 0x00000000
key_len         dq 0x00000000
