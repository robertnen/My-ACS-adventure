#lang racket
(require "suffix-tree.rkt")
(require "etapa1.rkt")

(provide (all-defined-out))

; functie care returneaza sufixele unui cuvant
; get-suffixes: text -> suffixes
(define (get-suffixes text)
  (if (null? text)
      '()
      (append (list text) (get-suffixes (cdr text)))
      ))

; functie care filtreaza o lista de cuvinte cu un caracter
; get-ch-words: words x ch -> cuvintele care incep cu ch
(define (get-ch-words words ch)
  (define (common-prefix? word)
    (let* ([pattern (list ch)]
           [ans (longest-common-prefix word pattern)]
           [pref (car ans)])
              (equal? pref pattern)))

  (filter common-prefix? words))

; functie care returneaza o lista cu primul caracter si restul cuvintelor
; ast-func: suffixes -> '(ch (word1 / ch) (word2 / ch) ... (wordn / ch))
(define (ast-func suffixes)
  (let*([ch (car (car suffixes))] ; caracterul cautat
        [label (list (list ch))]) ; il pun cum trebuie in lista
          (append label (foldr (λ (suff acc) (append (list (cdr suff)) acc)) '() suffixes))
          ))

; functie care returneaza o lista cu prefixul comun si restul cuvintelor
; cst-func: suffixes -> '(prefix (word1 / prefix) (word2 / prefix) ... (wordn / prefix))
(define (cst-func suffixes)
  (let*([f (λ (suff acc) (car (longest-common-prefix suff acc)))] ; functie de scos prefixul
        [acc (car suffixes)]  ; caut prefixul comun incepand folosind primul cuvant
        [prefix (foldr f acc suffixes)] ; prefixul comun
        [g (λ (suff) (car (cdr (longest-common-prefix suff prefix))))]) ; scot partea ramasa
        (append (list prefix) (map g suffixes)) ; rezultatul
        ))

; functie care construieste arborele de sufixe atomic sau compact dupa labeling-func
; suffixes->st: labeling-func x suffixes x alphabet -> AST/CST-st
(define (suffixes->st labeling-func suffixes alphabet)
  (define (suff-aux suff alpha ans)
    (if (null? alpha)
          ans   ; raman cu labelul construit
          (let* ([words (get-ch-words suff (car alpha))]
                 [oth-alpha (cdr alpha)])
                    (if (null? words)
                          (suff-aux suff oth-alpha ans) ; caut urmatorul caracter fara sa fac nimic
                          (suff-aux suff oth-alpha (append ans (list words))))))) ; am gasit label

  (define (merge branch)
    (let* ([ch (list (car branch))] ; primul label
           [suffs (cdr branch)])    ; restul labelurilor ce vor fi combinate dupa alfabet
            (if (null? suffs)
                ch                  ; sunt la frunza
                (append ch (suffixes->st labeling-func suffs alphabet)) ; grupez ramuri
              )))

  (let* ([common-words (suff-aux suffixes alphabet '())]
         [branches (map labeling-func common-words)])
            (map merge branches)))

; functie care pregateste functia de generare de arbori de sufixe si o apeleaza
; text->st: text -> st
(define text->st
  (λ (text)
    (λ (func)
      (let* ([fin (append text (list #\$))]        ; textul + $ la final
             [suffs (get-suffixes fin)]            ; generare de sufixe ale cuvantului
             [sorted (sort fin char<?)]            ; sortez caracterele care apar in cuvant
             [uniques (remove-duplicates sorted)]) ; ca sa nu se repete
                 (suffixes->st func suffs uniques)))))

; functie care genereaza arbore atomic
; text->ast: text -> st - atomic
(define text->ast
  (λ (text) ((text->st text) ast-func)))

; functie care genereaza arbore compact
; text->cst: text -> st - compact
(define text->cst
  (λ (text) ((text->st text) cst-func)))
