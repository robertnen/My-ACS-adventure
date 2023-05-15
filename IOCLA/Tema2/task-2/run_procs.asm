%include "../include/io.mac"

struc avg
    .quo resw 1
    .remain resw 1

struc proc
    .pid: resw 1
    .prio: resb 1
    .time: resw 1
endstruc

section .data
    prio_result dd 0, 0, 0, 0, 0
    time_result dd 0, 0, 0, 0, 0

section .text
    global run_procs

run_procs:
    ;; DO NOT MODIFY

    push ebp
    mov ebp, esp
    pusha

    xor ecx, ecx

clean_results:
    mov dword [time_result + 4 * ecx], dword 0
    mov dword [prio_result + 4 * ecx],  0

    inc ecx
    cmp ecx, 5
    jne clean_results

    mov ecx, [ebp + 8]      ; processes
    mov ebx, [ebp + 12]     ; length
    mov eax, [ebp + 16]     ; proc_avg
    ;; DO NOT MODIFY

    ;; Your code starts here

    push eax ; vreau un registru in plus

    mov esi, dword 0 ; contor

    xor eax, eax ; toate vor fi 0
    xor edx, edx ; calculeaza suma elementelor

    mov edi, ecx ; tin minte in edi adresa
    mov al, byte 1 ; primul prio e 1

thru_array:

    push ebx ; "scap" temporar de lungime

    xor ebx, ebx
    mov bl, byte [edi + proc.prio]
    cmp al, bl ; verific daca am alt prio
    jnz change_prio ; adevarat
    jmp continue_loop ; fals si merg mai departe

change_prio:
    add dword [time_result + eax * 4 - 4], edx ; adaug suma
    inc al ; maresc prio
    xor edx, edx ; resetez suma

    mov al, bl ; tin minte ultimul loc unde nu s-a pus nimic
    jmp continue_loop ; merg mai departe

continue_loop:

    mov bx, word [edi + proc.time]
    add edx, ebx ; adaug in suma

    inc dword [prio_result + eax * 4 - 4] ; am un element in plus

    pop ebx ; "recuperez" lungimea
    add edi, 5 ; merg mai departe in vector
    inc esi ; creste contorul
    cmp esi, ebx ; verfic daca ies
    jl thru_array

    mov [time_result + 4 * eax - 4], edx ; adaug ultimul element cautat

    pop edi ; recuperez adresa lui avg
    xor ebx, ebx ; resetez contorul

avg_loop:

    xor edx, edx ; double reset
    xor eax, eax
    mov eax, dword [time_result + 4 * ebx] ; deimpartit
    mov ecx, dword [prio_result + 4 * ebx] ; impartitor
    test ecx, ecx ; verific daca e 0

    jz is_zero ; da si pun 0 la elemente
    div ecx ; impart daca nu e

    mov [edi + avg.quo], ax ; catul
    mov [edi + avg.remain], dx ; restul
    jmp continue_avg

is_zero:

    mov [edi + avg.quo], word 0
    mov [edi + avg.remain], word 0

continue_avg:
    inc ebx ; cresc contorul
    add edi, 4 ; merg mai departe in vector
    cmp ebx, dword 5 ; verific daca am iesit din zona
    jne avg_loop


    ;; Your code ends here

    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY