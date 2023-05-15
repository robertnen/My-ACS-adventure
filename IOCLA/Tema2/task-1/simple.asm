%include "../include/io.mac"

section .text
    global simple

simple:
    ;; DO NOT MODIFY
    push    ebp
    mov     ebp, esp
    pusha

    mov     ecx, [ebp + 8]  ; len
    mov     esi, [ebp + 12] ; plain
    mov     edi, [ebp + 16] ; enc_string
    mov     edx, [ebp + 20] ; step

    ;; DO NOT MODIFY

    ;; Your code starts here

    xor eax, eax
    jmp loop_thru_string

loop_thru_string:
    mov bl, [esi + eax] ; if(plain[i] != NULL)
    test bl, bl
    jz exit_code ; ies din functie

    add bl, dl ; adaug pasul
    cmp bl, 'Z' ; if(plain[i] <= 'Z')
    jle add_letter

    sub bl, 26 ; else

add_letter:
    mov [edi + eax], bl ; adaug litera
    inc eax ; merg mai departe
    jmp loop_thru_string

exit_code:
    ;; Your code ends here

    ;; DO NOT MODIFY

    popa
    leave
    ret

    ;; DO NOT MODIFY
