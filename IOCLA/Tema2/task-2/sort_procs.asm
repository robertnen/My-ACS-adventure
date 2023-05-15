%include "../include/io.mac"

struc proc
    .pid: resw 1
    .prio: resb 1
    .time: resw 1
endstruc

section .data
    isSortedB db 0

section .text
    global sort_procs

sort_procs:
    ;; DO NOT MODIFY
    enter 0,0
    pusha

    mov edx, [ebp + 8]      ; processes
    mov eax, [ebp + 12]     ; length
    ;; DO NOT MODIFY

    ;; Your code starts here

    mov esi, edx ; esi va contine fiecare element
    dec eax

loop_while:
    mov byte [isSortedB], 1 ; bubblesort
    mov edi, dword 0
    mov esi, edx    ; merg de la inceput

loop_for:

    mov ecx, edi ; merg pana la len - 1 elemente

    cmp ecx, eax ; si verific sa fiu in vector
    jge end_for

    mov cl, [esi + proc.prio] ; proc[i].prio
    mov bl, [esi + 5 + proc.prio] ; proc[i + 1].prio

    cmp cl, bl
    jg swap_val
    jnz cont_for ; daca valorile sunt mai mici

    mov cx, [esi + proc.time] ; proc[i].time
    mov bx, [esi + 5 + proc.time] ; proc[i + 1].time

    cmp cx, bx
    jg swap_val
    jnz cont_for

    mov cx, [esi + proc.pid] ; proc[i].pid
    mov bx, [esi + 5 + proc.pid] ; proc[i + 1].pid

    cmp cx, bx
    jg swap_val
    jmp cont_for ; nu am unde sa ma mai ma duc

swap_val:
    mov byte [isSortedB], 0 ; sortarea nu e gata

    ; proc[i].prio <=> proc[i + 1].prio
    mov cl, [esi + proc.prio]
    mov bl, [esi + 5 + proc.prio]
    mov [esi + proc.prio], bl
    mov [esi + 5 + proc.prio], cl

    ; proc[i].time <=> proc[i + 1].time
    mov cx, [esi + proc.time]
    mov bx, [esi + 5 + proc.time]
    mov [esi + proc.time], bx
    mov [esi + 5 + proc.time], cx

    ; proc[i].pid <=> proc[i + 1].pid
    mov cx, [esi + proc.pid]
    mov bx, [esi + 5 + proc.pid]
    mov [esi + proc.pid], bx
    mov [esi + 5 + proc.pid], cx

    jmp cont_for

cont_for:
    add esi, dword 5 ; merg la urmatorul element
    inc edi
    jmp loop_for

end_for:
    cmp byte [isSortedB], 1
    jl loop_while

    ;; Your code ends here

    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY