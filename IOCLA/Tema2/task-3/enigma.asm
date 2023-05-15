%include "../include/io.mac"
;; defining constants, you can use these as immediate values in your code
LETTERS_COUNT EQU 26

section .data
    extern len_plain
    toCopy db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    toCopy2 db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

section .text
    global rotate_x_positions
    global enigma

; void rotate_x_positions(int x, int rotor, char config[10][26], int forward);
rotate_x_positions:
    ;; DO NOT MODIFY
    push ebp
    mov ebp, esp
    pusha

    mov eax, [ebp + 8]  ; x
    mov ebx, [ebp + 12] ; rotor
    mov ecx, [ebp + 16] ; config (address of first element in matrix)
    mov edx, [ebp + 20] ; forward
    ;; DO NOT MODIFY
    ;; TODO: Implement rotate_x_positions
    ;; FREESTYLE STARTS HERE

    cmp edx, dword 1
    jne set_to_shift_to_left
    jmp set_to_shift_to_right

set_to_shift_to_right:
    mov edx, dword 26
    sub edx, eax ; x = 26 - x
    jmp continue_shifting

set_to_shift_to_left:
    mov edx, eax ; x nu se schimba
    jmp continue_shifting

continue_shifting:
    add ebx, ebx ; imi trebuie 2 * rotor, nu rotor simplu

    xor eax, eax
    xor edi, edi

get_in_config: ; incerc sa ajung la config[2 * rotor][0]
    inc eax
    cmp eax, ebx
    jg exit_config ; inseamna ca am ajuns unde trebuie in config

    add edi, dword 26
    jmp get_in_config

exit_config:

    add ecx, edi
    mov edi, ecx ; vreau sa folosesc edi pt adresa

    xor eax, eax ; resetez contorul
loop_to_copy_arrays:
    xor ebx, ebx
    mov bl, byte [edi + eax]
    mov byte [toCopy + eax], bl ; iau primele x elemente si le tin minte

    xor ebx, ebx
    mov bl, byte [edi + eax + 26] ; la fel si aici
    mov byte [toCopy2 + eax], bl

    inc eax
    cmp eax, edx
    jl loop_to_copy_arrays

    mov ecx, edx ; x
    mov eax, ecx ; resetez contorul
loop_to_permute_in_config:
    mov esi, eax
    sub esi, ecx ; am nevoie de i - x

    xor ebx, ebx
    mov bl, byte [edi + eax] ; config[2 * rotor][i - x] = config[2 * rotor][i]
    mov byte [edi + esi], bl

    xor ebx, ebx
    mov bl, byte [edi + eax + 26] ; config[2 * rotor + 1][i - x] = config[2 * rotor + 1][i]
    mov byte [edi + esi + 26], bl

    inc eax
    cmp eax, dword 26
    jl loop_to_permute_in_config

    mov ecx, edx ; x
    mov eax, dword 26 ; resetez contorul
    sub eax, ecx
loop_final_permut:
    mov esi, eax
    add esi, ecx ; am nevoie de i + x

    xor ebx, ebx
    mov bl, byte [toCopy + esi - 26] ; config[2 * rotor][i] = toCopy[i + x - 26]
    mov byte [edi + eax], bl

    xor ebx, ebx
    mov bl, byte [toCopy2 + esi - 26] ; config[2 * rotor + 1][i] = toCopy2[i + x - 26]
    mov byte [edi + eax + 26], bl

    inc eax
    cmp eax, dword 26
    jl loop_final_permut

    ;; FREESTYLE ENDS HERE
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY

; void enigma(char *plain, char key[3], char notches[3], char config[10][26], char *enc);
enigma:
    ;; DO NOT MODIFY
    push ebp
    mov ebp, esp
    pusha

    mov eax, [ebp + 8]  ; plain (address of first element in string)
    mov ebx, [ebp + 12] ; key
    mov ecx, [ebp + 16] ; notches
    mov edx, [ebp + 20] ; config (address of first element in matrix)
    mov edi, [ebp + 24] ; enc
    ;; DO NOT MODIFY
    ;; TODO: Implement enigma
    ;; FREESTYLE STARTS HERE

    xor esi, esi ; contor

while_loop:

    xor ecx, ecx
    mov cl, [eax + esi]
    sub ecx, 'A'

    mov edi, dword 84 ; am nevoie sa fiu pe linia 9
    add edi, ecx

    mov cl, byte [edx + edi]
    sub ecx, 'A'    ; am gasit pozitia, adica config[9][plain[before] - 'A'] - 'A'

    mov edi, [ebp + 16] ; notches

    xor ebx, ebx
    xor ecx, ecx

    mov bl, byte [edi + 2]
    mov cl, byte [edi + 1]

    cmp bl, byte [edx + 84]
    jne try_notches_again

    cmp cl, byte [edx + 26]
    jne try_notches_again

    mov edx, dword 0
    mov ecx, [ebp + 20]
    mov ebx, dword 0
    mov eax, dword 1

    push edx
    push ecx
    push ebx
    push eax
    call rotate_x_positions ; rotate_x_positions(1, 0, config, 0)
    add esp, 16

    mov edx, dword 0
    mov ecx, [ebp + 20]
    mov ebx, dword 1
    mov eax, dword 1

    push edx
    push ecx
    push ebx
    push eax
    call rotate_x_positions ; rotate_x_positions(1, 1, config, 0)
    add esp, 16

    mov edx, dword 0
    mov ecx, [ebp + 20]
    mov ebx, dword 2
    mov eax, dword 1

    push edx
    push ecx
    push ebx
    push eax
    call rotate_x_positions ; rotate_x_positions(1, 2, config, 0)
    add esp, 16

    mov edx, [ebp + 20] ; config
    mov eax, [ebp + 8] ; plain
    jmp continue_while

try_notches_again:
    xor ebx, ebx
    mov bl, byte [edi + 2]
    cmp bl, byte [edx + 84]
    jne only_rotor_one

    mov edx, dword 0
    mov ecx, [ebp + 20]
    mov ebx, dword 1
    mov eax, dword 1

    push edx
    push ecx
    push ebx
    push eax
    call rotate_x_positions ; rotate_x_positions(1, 1, config, 0)
    add esp, 16

    mov edx, dword 0
    mov ecx, [ebp + 20]
    mov ebx, dword 2
    mov eax, dword 1

    push edx
    push ecx
    push ebx
    push eax
    call rotate_x_positions ; rotate_x_positions(1, 2, config, 0)
    add esp, 16

    mov edx, [ebp + 20] ; config
    mov eax, [ebp + 8] ; plain
    jmp continue_while

only_rotor_one:
    mov edx, dword 0
    mov ecx, [ebp + 20]
    mov ebx, dword 2
    mov eax, dword 1

    push edx
    push ecx
    push ebx
    push eax
    call rotate_x_positions ; rotate_x_positions(1, 2, config, 0)
    add esp, 16

    mov edx, [ebp + 20] ; config
    mov eax, [ebp + 8] ; plain
    jmp continue_while

continue_while:

    mov edi, [ebp + 24] ; enc
    xor ebx, ebx
    mov bl, byte [eax + esi]
    mov byte [edi + esi], bl

    inc esi
    cmp esi, dword [len_plain]
    jl while_loop

    ;; FREESTYLE ENDS HERE
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY