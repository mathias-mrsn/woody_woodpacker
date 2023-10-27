BITS 64
; ARCH INTEL x86_64

%define S_LEN 0x100 ; 256
%define SYS_EXIT 0x3c
%define SYS_WRITE 0x01

section .text
    global encrypt

encrypt:

    ; Initialize _start function
    push r9
    push rdi
    push rsi
    push rdx
    push rcx
    push r8

    push rbp
    mov rbp, rsp
    sub rsp, S_LEN + 0x10

    ; RBP:
    ; + 0x0 - 0x8 : Old RBP
    ; + 0x8 - 0x10 : Cipher address
    ; + 0x10 - 0x18 : Key length
    ; + 0x18 - 0x20 : Key address
    ; + 0x20 - 0x28 : Plain text length
    ; + 0x28 - 0x30 : Plain text address

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
    mov ecx, [rbp + 0x10] 
    xor rdx, rdx
    div ecx
    mov rdi, [rbp + 0x18]
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
    mov rdi, [rbp + 0x28]
    add rdi, r10
    movzx rdx, byte [rdi]
    xor al, dl
    
    ; [cipher[n] = al]
    mov rdi, [rbp + 0x8]
    add rdi, r10
    mov [rdi], al

    inc r10
    cmp r10, [rbp + 0x20]
    jne .prga

_end:

    leave
    pop r8
    pop rcx
    pop rdx
    pop rsi
    pop rdi
    pop r9
    ret