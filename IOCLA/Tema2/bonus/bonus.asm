section .data

section .text
    global bonus

bonus:
    ;; DO NOT MODIFY
    push ebp
    mov ebp, esp
    pusha

    mov eax, [ebp + 8]	; x
    mov ebx, [ebp + 12]	; y
    mov ecx, [ebp + 16] ; board

    ;; DO NOT MODIFY
    ;; FREESTYLE STARTS HERE

    xchg eax, ebx ; le-am facut invers...

    ; if(!x && !y)
    cmp eax, dword 0
    jne try_top_right

    cmp ebx, dword 0
    jne try_top_right

    mov esi, 1
    shl esi, 9
    or [ecx + 4], esi ; (1, 1) = 1
    jmp exit_function

    ; if(x == 7 && y == 7)
try_top_right:
    cmp eax, dword 7
    jne try_bottom_right

    cmp ebx, dword 7
    jne try_bottom_right

    mov esi, 1
    shl esi, 22
    or [ecx], esi ; (6, 6) = 1
    jmp exit_function

    ; if(x == 7 && !y)
try_bottom_right:
    cmp eax, dword 7
    jne try_top_left

    cmp ebx, dword 0
    jne try_top_left

    mov esi, 1
    shl esi, 14
    or [ecx + 4], esi ; (1, 6) = 1
    jmp exit_function

    ; if(!x && y == 7)
try_top_left:
    cmp eax, dword 0
    jne try_lower_mid_left

    cmp ebx, dword 7
    jne try_lower_mid_left

    mov esi, 1
    shl esi, 17
    or [ecx], esi ; (6, 1)
    jmp exit_function

    ; sunt pe marginea din stanga
    add ecx, ebx

    ; if(!x && y == 3)
try_lower_mid_left:
    cmp eax, dword 0
    jne try_lower_mid_right

    cmp ebx, dword 3
    jne try_lower_mid_right

    mov esi, 1
    shl esi, 17
    or [ecx + 4], esi ; (1, 2)

    mov esi, 1
    shl esi, 1
    or [ecx], esi ; (1, 4)
    jmp exit_function

    ; if(x == 7 && y == 3)
try_lower_mid_right:
    cmp eax, dword 7
    jne try_upper_mid_left

    cmp ebx, dword 3
    jne try_upper_mid_left

    mov esi, 1
    shl esi, 22
    or [ecx + 4], esi ; (6, 2)

    mov esi, 1
    shl esi, 6
    or [ecx], esi ; (6, 4)
    jmp exit_function

    ; if(x == 0 && y == 4)
try_upper_mid_left:
    cmp eax, dword 0
    jne try_upper_mid_right

    cmp ebx, dword 4
    jne try_upper_mid_right

    mov esi, 1
    shl esi, 25
    or [ecx + 4], esi ; (1, 3)

    mov esi, 1
    shl esi, 9
    or [ecx], esi ; (1, 5)
    jmp exit_function

    ; if(x == 7 && y == 4)
try_upper_mid_right:
    cmp eax, dword 7
    jne try_left_side

    cmp ebx, dword 4
    jne try_left_side

    mov esi, 1
    shl esi, 30
    or [ecx + 4], esi ; (6, 3)

    mov esi, 1
    shl esi, 14
    or [ecx], esi ; (6, 5)
    jmp exit_function

    ; if(!x)
try_left_side:
    cmp eax, dword 0
    jne try_right_side

    mov edx, ebx
    dec edx
    shl edx, 3 ; inmultesc cu 8
    ; zona respectiva are valoarea (x - 1) * 8
    add edx, 9

    cmp edx, 32
    jge is_upper_side_left
    jmp is_lower_side_left

is_upper_side_left: ; calculez (y - 1) * 8, unde y e in {5, 6}
    sub ebx, 4 ; y e in {1, 2}
    mov esi, ebx
    shl esi, 3 ; am calculat (y - 1) * 8
    mov edx, esi ; fac o copie
    add esi, 9
    push ecx ; am nevoie pentru shl de ecx
    mov ecx, esi
    mov esi, 1
    shl esi, cl ; am gasit numarul corespondent
    pop ecx ; recuperez ecx
    or [ecx], esi

    mov esi, edx
    sub esi, 7
    push ecx ; am nevoie pentru shl de ecx
    mov ecx, esi
    mov esi, 1
    shl esi, cl ; am gasit numarul corespondent
    pop ecx ; recuperez ecx
    or [ecx], esi
    jmp exit_function

is_lower_side_left: ; calculez (y - 1) * 8, unde y e in {1, 2}
    mov esi, ebx
    shl esi, 3 ; am calculat (y - 1) * 8
    mov edx, esi ; fac o copie
    add esi, 9
    push ecx ; am nevoie pentru shl de ecx
    mov ecx, esi
    mov esi, 1
    shl esi, cl ; am gasit numarul corespondent
    pop ecx ; recuperez ecx
    or [ecx + 4], esi

    mov esi, edx
    sub esi, 7
    push ecx ; am nevoie pentru shl de ecx
    mov ecx, esi
    mov esi, 1
    shl esi, cl ; am gasit numarul corespondent
    pop ecx ; recuperez ecx
    or [ecx + 4], esi
    jmp exit_function

    ; if(x == 7)
try_right_side:
    cmp eax, dword 7
    jne try_upper_side

    mov edx, ebx
    dec edx
    shl edx, 3 ; inmultesc cu 8
    ; zona respectiva are valoarea (x - 1) * 8
    add edx, 9

    cmp edx, 32
    jge is_upper_side_right
    jmp is_lower_side_right

is_upper_side_right: ; calculez (y - 1) * 8 + 7, unde y e in {5, 6}
    sub ebx, 4 ; y e in {1, 2}
    mov esi, ebx
    shl esi, 3 ; am calculat (y - 1) * 8
    add esi, 7
    mov edx, esi ; fac o copie
    add esi, 7
    push ecx ; am nevoie pentru shl de ecx
    mov ecx, esi
    mov esi, 1
    shl esi, cl ; am gasit numarul corespondent
    pop ecx ; recuperez ecx
    or [ecx], esi

    mov esi, edx
    sub esi, 9
    push ecx ; am nevoie pentru shl de ecx
    mov ecx, esi
    mov esi, 1
    shl esi, cl ; am gasit numarul corespondent
    pop ecx ; recuperez ecx
    or [ecx], esi
    jmp exit_function

is_lower_side_right: ; calculez (y - 1) * 8, unde y e in {1, 2}
    mov esi, ebx
    shl esi, 3 ; am calculat (y - 1) * 8
    add esi, 7
    mov edx, esi ; fac o copie
    add esi, 7
    push ecx ; am nevoie pentru shl de ecx
    mov ecx, esi
    mov esi, 1
    shl esi, cl ; am gasit numarul corespondent
    pop ecx ; recuperez ecx
    or [ecx + 4], esi

    mov esi, edx
    sub esi, 9
    push ecx ; am nevoie pentru shl de ecx
    mov ecx, esi
    mov esi, 1
    shl esi, cl ; am gasit numarul corespondent
    pop ecx ; recuperez ecx
    or [ecx + 4], esi
    jmp exit_function

    ; if(y == 7)
try_upper_side:
    cmp ebx, dword 7
    jne try_lower_side

    mov esi, 15
    add esi, eax ; am nevoie de 16 + x - 1 si apoi de 16 + x + 1
    mov edx, esi ; fac si pe a doua
    add edx, 2 ; 16 + x + 1

    push ecx
    mov ecx, esi
    mov esi, 1
    shl esi, cl
    pop ecx
    or [ecx], esi

    push ecx
    mov ecx, edx
    mov esi, 1
    shl esi, cl
    pop ecx
    or [ecx], esi
    jmp exit_function

    ; if(!y)
try_lower_side:
    cmp ebx, dword 0
    jne is_inside

    mov esi, 7
    add esi, eax ; am nevoie de 8 + x - 1 si apoi de 8 + x + 1
    mov edx, esi ; fac si pe a doua
    add edx, 2 ; 8 + x + 1

    push ecx
    mov ecx, esi
    mov esi, 1
    shl esi, cl
    pop ecx
    or [ecx + 4], esi

    push ecx
    mov ecx, edx
    mov esi, 1
    shl esi, cl
    pop ecx
    or [ecx + 4], esi
    jmp exit_function

is_inside: ; aflu mai intai unde ma aflu: calculez y * 8 + x
    mov esi, ebx
    shl esi, 3 ; y * 8
    add esi, eax ; am gasit unde ma aflu
    mov edx, ecx ; mut ecx in edx pentru usurinta
    mov edi, esi ; fac o copie

    mov ebx, 4 ; tine minte daca sunt jos sau nu (implicit sunt jos)
    add esi, 7
    cmp esi, 32
    jge is_up_1
    jmp is_down_1

is_up_1: ; sunt in edx
    sub esi, 32
    mov ebx, 0

is_down_1: ; sunt in edx + 4
    mov ecx, esi
    mov esi, 1
    shl esi, cl
    or [edx + ebx], esi

    add cl, 2 ; adaug elementul din dreapta-sus
    mov esi, 1
    shl esi, cl
    or [edx + ebx], esi

    mov esi, edi
    mov ebx, 4
    sub esi, 9
    cmp esi, 32
    jge is_up_2
    jmp is_down_2

is_up_2: ; sunt in edx
    sub esi, 32
    mov ebx, 0

is_down_2: ; sunt in edx + 4
    mov ecx, esi
    mov esi, 1
    shl esi, cl
    or [edx + ebx], esi

    add cl, 2 ; adaug elementul din dreapta-sus
    mov esi, 1
    shl esi, cl
    or [edx + ebx], esi

exit_function:
    ;; FREESTYLE ENDS HERE
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY