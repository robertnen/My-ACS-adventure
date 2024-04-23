#lang racket

(provide (all-defined-out))

;; În acest fișier vă definiți constructorii și
;; operatorii tipului Collection.
;; În etapele anterioare, colecțiile erau de fapt
;; liste.
;; În definițiile de mai jos, veți considera că
;; o colecție este implementată ca flux.

; Întrucât stream-cons nu este o funcție obișnuită, 
; ci este definită ca o sintaxă specială, astfel
; încât ea să nu își evalueze argumentele înainte 
; de apel (comportament pe care ni-l dorim și pentru 
; collection-cons), nu putem folosi o definiție
; de tipul
;    (define collection-cons stream-cons)
; (genul acesta de definiție generează o eroare).
; Nici varianta
;    (define (collection-cons x xs) (stream-cons x xs))
; nu este o soluție, întrucât funcțiile definite de noi
; în Racket sunt funcții stricte, iar x și xs vor fi
; evaluate înainte de a intra în corpul funcției
; collection-cons și a descoperi că ele vor fi
; argumentele unui stream-cons.
; Modul de a defini collection-cons pentru a reproduce
; întocmai comportamentul lui stream-cons este:
; Obs: puteți schimba numele funcției, dacă nu vă
; place "collection-cons". Este o funcție folosită doar
; de voi în fișierul etapa4.rkt, nu de checker.


; TODO
; Scrieți în continuare restul definițiilor
; (care nu necesită o sintaxă specială).
(define empty-col empty-stream)

(define-syntax-rule (col-cons x xs) (stream-cons x xs))

(define-syntax-rule (col-empty? E) (stream-empty? E))
(define-syntax-rule (col-not-empty? E) (not (col-empty? E)))

(define-syntax-rule (col-car E) (stream-first E))
(define-syntax-rule (col-cdr E) (stream-rest E))
(define-syntax-rule (col-null-car? E) (null? (col-car E)))
(define-syntax-rule (col-null-cdr? E) (null? (col-cdr E)))

(define-syntax-rule (col-map func E) (stream-map func E))
(define-syntax-rule (col-filter func E) (stream-filter func E))

(define (list->col-aux L)
  (cond
    [(null? L) empty-stream]
    [else (let* ([first (car L)]
                 [last  (cdr L)]) (col-cons first (list->col-aux last)))]))

(define-syntax-rule (list->col L) (list->col-aux L))