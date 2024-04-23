#lang racket
(require "suffix-tree.rkt")
(require "etapa1.rkt")
(require "etapa2.rkt")

(provide (all-defined-out))

;; Această etapă este dedicată aplicațiilor
;; arborelui de sufixe:
;; - găsirea unui șablon într-un text
;; - cel mai lung subșir comun a două texte
;; - găsirea unui subșir de lungime dată care se
;;   repetă în text
;; Conform convenției din etapele anterioare, un text
;; este întotdeauna reprezentat ca listă de caractere.
;; Rezultatele funcțiilor de mai jos sunt de asemenea
;; reprezentate ca liste de caractere.


; TODO 1
; Implementați funcția substring? care primește un text și
; un șablon nevid și întoarce true dacă șablonul apare în
; text, respectiv false în caz contrar.
; Observație: ați implementat deja logica principală a
; acestei căutări în etapa 1, în funcția st-has-pattern?,
; care este un operator al tipului ST. Acum aveți toate
; uneltele necesare implementării operatorului corespunzător
; pentru tipul text (pentru că în etapa 2 ați implementat
; construcția arborelui de sufixe asociat unui text).
(define (substring? text pattern)
  (let stree ([st (text->ast text)]) (st-has-pattern? st pattern)))


; TODO 2
; Implementați funcția longest-common-substring care primește
; două texte și determină cel mai lung subșir comun al
; acestora, folosind algoritmul următor:
; 1. Construiește arborele de sufixe ST1 pentru primul text.
; 2. Pentru fiecare sufix din al doilea text (de la cel mai
;    lung la cel mai scurt), găsește cea mai lungă potrivire
;    cu sufixele din primul text, urmând căile relevante în ST1.
; 3. Rezultatul final este cel mai lung rezultat identificat
;    la pasul 2 (în caz de egalitate a lungimii, păstrăm
;    primul șir găsit).
; Folosiți named let pentru a parcurge sufixele.
; Observație: pentru sufixele din al doilea text nu dorim
; marcajul de final $ pentru a nu crește artificial lungimea
; șirului comun cu acest caracter.
; Hint: Revizitați funcția match-pattern-with-label (etapa 1).
(define (longest-common-substring text1 text2)
  (define (get-prefix st word)
    (let ([ans (match-pattern-with-label st word)]) ; search for possible common
            ; verific daca am primit (#f '(restul branch-ului)) altfel merg mai departe
            (cond
              [(equal? ans #t) word]   ; e ce cautam
              [(= (length word) 1) #f] ; poate nu exista nimic in comun
              [(and (list? ans) (equal? (car ans) #f)) (get-prefix st (drop-right word 1))]
              [else word])))           ; l-am gasit

  (let *([st (text->ast text1)]
         [suffixes (get-suffixes text2)])
            (let iter ([stree st] [suffs suffixes] [ans '()]) ; named let
                          (if (null? suffs) ; nu mai am sufixe
                              ans           ; nu mai am solutii
                              (letrec ([word (car suffs)] ; primul sufix
                                       [oth (cdr suffs)]  ; celelalte
                                       [len (sub1 (length word))] ; lungimea maxima posibilaa a prefixului
                                       [result (get-prefix stree word)]) ; prefixul comun unui sufix
                                          (cond
                                            [(not (list? result)) (iter st oth ans)]
                                            [(> (length result) (length ans)) (iter st oth result)]
                                            [else (iter st oth ans)]))))))


; TODO 3
; Implementați funcția repeated-substring-of-given-length
; care primește un text și un număr natural len și
; parcurge arborele de sufixe al textului până găsește un
; subșir de lungime len care se repetă în text.
; Dacă acest subșir nu există, funcția întoarce false.
; Obs: din felul în care este construit arborele de sufixe
; (pe baza alfabetului sortat), rezultatul va fi primul
; asemenea subșir din punct de vedere alfabetic.
; Ideea este următoarea: orice cale în arborele de sufixe
; compact care se termină cu un nod intern (un nod care
; are copii, nu este o frunză) reprezintă un subșir care
; se repetă, pentru că orice asemenea cale reprezintă un
; prefix comun pentru două sau mai multe sufixe ale textului.
; Folosiți interfața definită în fișierul suffix-tree
; atunci când manipulați arborele.
; (define (repeated-substring-of-given-length text len)
;   (let *([st (tree->cst text)])

(define (repeated-substring-of-given-length text len)
  (letrec ([st (text->cst text)]
           [search (λ (repeated-func st leng acr) ; ca sa merg pe fiecare copil
                        (cond
                          [(null? st) #f]
                          [else (repeated-func st leng acr)]))]
           [repeated (λ (st size acr) ; un fel de dfs
                          (let* ([fst (first-branch st)]
                                 [oth (other-branches st)]
                                 [ost (get-branch-subtree fst)]
                                 [label (get-branch-label fst)]
                                 [lmax (+ size (length label))])
                                    (cond
                                      [(null? ost) (search repeated oth size acr)] ; nu mai am ce face cu prima ramura
                                      [(<= len lmax) (letrec ([smsize (- len size)] ; tai din substring
                                                              [tag (take label smsize)]) (append acr tag))]
                                      [else (let* ([acl (append acr label)] ; coboram
                                                   [lst (search repeated ost lmax acl)]  ; pe stanga
                                                   [rst (search repeated oth size acr)]) ; pe dreapta
                                                        (if (not (equal? lst #f))
                                                              lst
                                                              rst))])
                            ))]) (repeated st 0 '()) ; plec din radacina
        ))

