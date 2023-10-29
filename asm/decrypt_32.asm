BITS 32
; ARCH INTEL x86

%define S_LEN 0x100
%define SYS_EXIT 1
%define SYS_WRITE 4

section .text
    global decrypt_32
    global decrypt_32_end

decrypt_32:

    ; Initialize decrypt_32 function
    push ebp
    mov ebp, esp
    sub esp, S_LEN + 0x10

    call get_fixed_addr
    add edx, woody - reference
    mov ecx, edx
    mov ebx, 1
    mov eax, SYS_WRITE
    mov edx, woody_len
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
    call get_fixed_addr
    add edx, key_len - reference
    mov ecx, [edx]
    call get_fixed_addr
    add edx, key - reference
    mov edi, edx
    xor edx, edx
    div ecx
    add edi, edx 
    mov al, [edi]
    add bl, al

    mov eax, SYS_EXIT
    int 0x80

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
    call get_fixed_addr
    add edx, decrypt_addr - reference
    mov edi, edx
    add edi, ebx
    mov dl, [edi]
    xor al, dl

    ; [cipher[n] = al]
    call get_fixed_addr
    add edx, decrypt_addr - reference
    mov edi, edx
    add edi, ebx
    mov [edi], al

    inc ebx
    call get_fixed_addr
    add edx, decrypt_len - reference
    cmp ebx, [edx]
    jne .prga

_end:

    leave
    xor ebx, ebx
    xor edi, edi
    xor ecx, ecx

    call get_fixed_addr
    add edx, old_start - reference
    mov eax, edx
    xor edx, edx
    jmp [rel old_start]

get_fixed_addr:
    call reference
reference:
    pop edx
    ret

; data
woody           db "....WOODY....", 10
woody_len       equ $-woody

old_start       dd 0x11111111
decrypt_addr    dd 0x22222222
decrypt_len     dd 0x33333333
key_len         dd 0x44444444
key             times 32 db 0x0
decrypt_32_end:
