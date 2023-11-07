BITS 64
; ARCH INTEL x86_64

%define S_LEN 0x100
%define SYS_EXIT 0x3c
%define SYS_WRITE 0x01

section .text
    global decrypt_64
    global decrypt_64_end

decrypt_64:

    ; Initialize _start function
    push rbp
    mov rbp, rsp
    sub rsp, S_LEN + 0x10

    mov rdx, woody_len
    lea rsi, [rel woody]
    mov rdi, 1
    mov rax, SYS_WRITE
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
    mov rcx, [rel key_len]
    xor rdx, rdx
    div rcx
    lea rdi, [rel key]
    add rdi, rdx 
    movzx rax, byte [rdi]
    add r9, rax

    mov rax, r9
    xor rdx, rdx
    mov rcx, S_LEN
    div rcx
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

    xor rsi, rsi
    xor rdi, rdi

    ; [al = rax ^ text[r10]]
    mov rdi, [rel current_start]
    sub rdi, [rel decrypt_addr]
    lea rsi, [rel decrypt_64]
    sub rsi, rdi
    add rsi, r10
    movzx rdx, byte [rsi]
    xor al, dl
    
    ; [cipher[n] = al]
    mov rdi, [rel current_start]
    sub rdi, [rel decrypt_addr]
    lea rsi, [rel decrypt_64]
    sub rsi, rdi
    add rsi, r10
    mov [rsi], al

    inc r10
    cmp r10, [rel decrypt_len]
    jne .prga
;
_end:

    leave
    xor r10, r10
    xor r9, r9
    xor r8, r8
    xor rdx, rdx
    xor rax, rax
    mov rdi, [rel current_start]
    sub rdi, [rel old_start]
    lea rsi, [rel decrypt_64]
    sub rsi, rdi
    xor rdi, rdi
    jmp rsi
    ;ret

; data
woody           db "....WOODY....", 10
woody_len       equ $-woody

current_start   dq 0x0000000000000000
old_start       dq 0x0000000000000000
decrypt_addr    dq 0x0000000000000000
decrypt_len     dq 0x0000000000000000
key_len         dq 0x0000000000000000
key             times 32 db 0x0
decrypt_64_end:
