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
    mov ecx, woody
    mov ebx, 1
    mov al, SYS_WRITE
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
    xor edx, edx

    .ksa:
    ; [j = (j + S[i] + key[i % key_len]) % S_LEN]
    movzx eax, byte [esp + ecx]
    add edx, eax
    mov ebx, ecx
    mov esi, key
    xor edi, edi
    div esi
    add edi, ebx
    movzx eax, byte [edi + key]
    add edx, eax

    mov eax, edx
    xor edx, edx
    mov ebx, S_LEN
    div ebx
    mov edx, edx

    ; [swap(S[i], S[j])]
    mov al, [esp + ecx]
    mov cl, [esp + edx]
    mov [esp + edx], al
    mov [esp + ecx], cl

    inc ecx
    cmp ecx, S_LEN
    jne .ksa

    ; Pseudo-random generation algorithm (PRGA)
    xor ecx, ecx
    xor edx, edx
    xor ebx, ebx

    .prga:
    ; [i = (i + 1) % S_LEN]
    inc ecx
    mov eax, ecx
    mov esi, S_LEN
    xor edi, edi
    div esi
    mov ecx, edi

    ; [j = (j + S[i]) % N]
    movzx edi, byte [esp + ecx]
    add edx, edi
    mov eax, edx
    mov esi, S_LEN
    xor edi, edi
    div esi
    mov edx, edi

    ; [swap(S[%ecx], S[%edx])]
    mov al, [esp + ecx]
    mov cl, [esp + edx]
    mov [esp + edx], al
    mov [esp + ecx], cl

    ; [int %eax = S[(S[%ecx] + S[%edx]) % S_LEN]]
    movzx eax, byte [esp + ecx]
    movzx edi, byte [esp + edx]
    add eax, edi
    mov esi, S_LEN
    xor edx, edx
    div esi
    movzx eax, byte [esp + edx]

    ; [al = eax ^ text[ebx]]
    mov edi, decrypt_addr
    add edi, ebx
    movzx edi, byte [edi]
    xor al, dl

    ; [cipher[n] = al]
    mov edi, decrypt_addr
    add edi, ebx
    mov [edi], al

    inc ebx
    cmp ebx, decrypt_len
    jne .prga

_end:

    ; jmp old_start
    leave
    mov al, SYS_EXIT
    int 0x80

; data
woody           db "....WOODY...."
woody_len       equ $-woody

old_start       dd 0x00000000
decrypt_addr    dd 0x00000000
decrypt_len     dd 0x00000000
key             dd 0x00000000
key_len         dd 0x00000000
decrypt_32_end:
