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
    mov esi, woody
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
    movzx eax, byte [esp + ecx]
    add ebx, eax
    mov eax, ecx
    mov edx, [key_len]
    xor esi, esi
    div edx
    mov edi, key
    add edi, esi
    movzx eax, byte [edi]
    add ebx, eax

    mov eax, ebx
    xor edx, edx
    mov esi, S_LEN
    div esi
    mov ebx, edx

    ; [swap(S[i], S[j])]
    mov al, [esp + ecx]
    mov cl, [esp + ebx]
    mov [esp + ebx], al
    mov [esp + ecx], cl

    inc ecx
    cmp ecx, S_LEN
    jne .ksa

    ; Pseudo-random generation algorithm (PRGA)
    xor ecx, ecx
    xor ebx, ebx
    xor esi, esi
    .prga:
    ; [i = (i + 1) % S_LEN]
    inc ecx
    mov eax, ecx
    mov edx, S_LEN
    xor ebx, ebx
    div edx
    mov ecx, ebx

    ; [j = (j + S[i]) % N]
    movzx edx, byte [esp + ecx]
    add ebx, edx
    mov eax, ebx
    mov edx, S_LEN
    xor esi, esi
    div edx
    mov ebx, edx

    ; [swap(S[%ecx], S[%ebx])]
    mov al, [esp + ecx]
    mov cl, [esp + ebx]
    mov [esp + ebx], al
    mov [esp + ecx], cl

    ; [int %eax = S[(S[%ecx] + S[%ebx]) % S_LEN]]
    movzx eax, byte [esp + ecx]
    movzx edi, byte [esp + ebx]
    add eax, edi
    mov edx, S_LEN
    xor esi, esi
    div edx
    movzx eax, byte [esp + edx]

    ; [al = eax ^ text[esi]]
    mov edi, [decrypt_addr]
    add edi, esi
    movzx edx, byte [edi]
    xor al, dl
    
    ; [cipher[n] = al]
    mov edi, [decrypt_addr]
    add edi, esi
    mov [edi], al

    inc esi
    cmp esi, [decrypt_len]
    jne .prga

_end:

    leave
    ;jmp [old_start]
    ret

; data
woody           db "....WOODY....", 10
woody_len       equ $-woody

old_start       dd 0x00000000
decrypt_addr    dd 0x00000000
decrypt_len     dd 0x00000000
key_len         dd 0x00000000
key             times 32 db 0x0
decrypt_32_end:

