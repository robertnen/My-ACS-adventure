section .data

section .text
	global checkers

checkers:
    ;; DO NOT MODIFY
    push ebp
    mov ebp, esp
    pusha

    mov eax, [ebp + 8]	; x
    mov ebx, [ebp + 12]	; y
    mov ecx, [ebp + 16] ; table

    ;; DO NOT MODIFY
    ;; FREESTYLE STARTS HERE

    ; if(x >= 1 && x <= 6 && y >= 1 && y <= 6)
    cmp eax, dword 1
    jl is_outside

    cmp eax, dword 6
    jg is_outside

    cmp ebx, dword 1
    jl is_outside

    cmp ebx, dword 6
    jg is_outside

    dec ebx
    add ecx, ebx
    mov [ecx + 8 * eax - 8], byte 1 ; (x - 1, y - 1) = 1
    mov [ecx + 8 * eax + 8], byte 1 ; (x + 1, y - 1) = 1

    add ecx, 2
    mov [ecx + 8 * eax - 8], byte 1 ; (x - 1, y + 1) = 1
    mov [ecx + 8 * eax + 8], byte 1 ; (x + 1, y + 1) = 1
    jmp exit_function

    ; if(!x && !y)
is_outside:
    cmp eax, dword 0
    jnz not_bottom_left

    cmp ebx, dword 0
    jnz not_bottom_left

    inc ecx
    mov [ecx + 8], byte 1 ; (1, 1) = 1
    jmp exit_function

    ; if(x == 7 && y == 7)
not_bottom_left:
    cmp eax, dword 7
    jne not_top_right

    cmp ebx, dword 7
    jne not_top_right

    dec ebx
    add ecx, ebx
    mov [ecx + 8 * eax - 8], byte 1 ; (6, 6) = 1
    jmp exit_function

    ; if(x == 7 && !y)
not_top_right:
    cmp eax, dword 7
    jne not_bottom_right

    cmp ebx, dword 0
    jne not_bottom_right

    inc ecx
    mov [ecx + 8 * eax - 8], byte 1 ; (1, 6)
    jmp exit_function

    ; if(!x && y == 7)
not_bottom_right:
    cmp eax, dword 0
    jne not_top_left

    cmp ebx, dword 7
    jne not_top_left

    dec ebx
    add ecx, ebx
    mov [ecx + 8 * eax + 8], byte 1 ; (6, 1)
    jmp exit_function

    ; sunt pe marginea din stanga
    add ecx, ebx

    ; if(!x)
not_top_left:
    cmp eax, dword 0
    jne not_left

    inc ebx
    add ecx, ebx
    mov [ecx + 8 * eax + 8], byte 1 ; (x + 1, y + 1) = 1
    sub ecx, 2
    mov [ecx + 8 * eax + 8], byte 1 ; (x + 1, y - 1) = 1
    jmp exit_function

    ; if(x == 7)
not_left:
    cmp eax, dword 7
    jne not_right

    inc ebx
    add ecx, ebx
    mov [ecx + 8 * eax - 8], byte 1 ; (x - 1, y + 1) = 1
    sub ecx, dword 2
    mov [ecx + 8 * eax - 8], byte 1 ; (x - 1, y - 1) = 1
    jmp exit_function

    ; if(!y)
not_right:
    cmp ebx, dword 0
    jne not_down

    inc ecx
    mov [ecx + 8 * eax + 8], byte 1 ; (x + 1, y + 1) = 1
    mov [ecx + 8 * eax - 8], byte 1 ; (x - 1, y + 1) = 1
    jmp exit_function

    ; if(y == 7)
not_down:
    dec ebx
    add ecx, ebx
    mov [ecx + 8 * eax + 8], byte 1 ; (x + 1, y - 1) = 1
    mov [ecx + 8 * eax - 8], byte 1 ; (x - 1, y - 1) = 1
    jmp exit_function

exit_function:
    ;; FREESTYLE ENDS HERE
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY