BITS 32
; ARCH INTEL x86

%define S_LEN 0x100
%define SYS_EXIT 1
%define SYS_WRITE 4

section .text
    global decrypt_32
    global decrypt_32_end

decrypt_32:

    ; Initialize _start function
    push ebp
    mov ebp, esp
    sub esp, S_LEN + 0x10

    mov edx, woody_len
    lea esi, [rel woody]
    mov edi, 1
    mov eax, SYS_WRITE
    int 0x80

    ; Initialize S array (S[i] = i)
    xor ecx, ecx
    .fill:
    mov [esp + ecx], cl
    inc ecx
    cmp ecx, S_LEN
    jne .fill

    ; Key Scheduling Algorithm (KSA)
    xor ecx, ecx
    xor ebx, ebx

    .ksa:
    ; [j = (j + S[i] + key[i % key_len]) % S_LEN]
    mov al, [esp + ecx]
    add bl, al
    mov eax, ecx
    mov ecx, [rel key_len]
    xor edx, edx
    div ecx
    lea edi, [rel key]
    add edi, edx 
    mov al, [edi]
    add bl, al

    mov eax, ebx
    xor edx, edx
    mov ecx, S_LEN
    div ecx
    mov ebx, edx

    ; [swap(S[i], S[j])]
    mov al, [esp + ecx]
    mov dl, [esp + ebx]
    mov [esp + ebx], al
    mov [esp + ecx], dl

    inc ecx
    cmp ecx, S_LEN
    jne .ksa

    ; Pseudo-random generation algorithm (PRGA)
    xor ecx, ecx
    xor ebx, ebx
    xor edi, edi

    .prga:
    ; [i = (i + 1) % S_LEN]
    inc ecx
    mov eax, ecx
    mov esi, S_LEN
    xor edx, edx
    div esi
    mov ecx, edx

    ; [j = (j + S[i]) % N]
    mov dl, [esp + ecx]
    add edi, edx
    mov eax, edi
    mov esi, S_LEN
    xor edx, edx
    div esi
    mov edi, edx

    ; [swap(S[%ecx], S[%edi])]
    mov al, [esp + ecx]
    mov dl, [esp + edi]
    mov [esp + edi], al
    mov [esp + ecx], dl

    ; [int %eax = S[(S[%ecx] + S[%edi]) % S_LEN]]
    mov al, [esp + ecx]
    mov dl, [esp + edi]
    add al, dl
    mov esi, S_LEN
    xor edx, edx
    div esi
    mov al, [esp + edx]

    ; [al = eax ^ text[ebx]]
    lea edi, [rel decrypt_addr]
    add edi, ebx
    mov dl, [edi]
    xor al, dl
    
    ; [cipher[n] = al]
    lea edi, [rel decrypt_addr]
    add edi, ebx
    mov [edi], al

    inc ebx
    cmp ebx, [rel decrypt_len]
    jne .prga
;
_end:

    leave
    xor ebx, ebx
    xor edi, edi
    xor ecx, ecx
    xor edx, edx
    xor eax, eax
    jmp [rel old_start]

; data
woody           db "....WOODY....", 10
woody_len       equ $-woody

old_start       dd 0x00000000
decrypt_addr    dd 0x00000000
decrypt_len     dd 0x00000000
key_len         dd 0x00000000
key             times 32 db 0x0
decrypt_32_end:

