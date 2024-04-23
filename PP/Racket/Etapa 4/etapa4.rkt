#lang racket
(require "suffix-tree-stream.rkt")
(require "collection.rkt")

(provide (all-defined-out))

;; Vom prelua toate funcțiile din etapele 1-3 (exceptând
;; longest-common-substring, care nu beneficiază de 
;; reprezentarea ca flux întrucât parcurge tot arborele)
;; și le vom adapta la noua reprezentare a unui ST.
;;
;; Pentru că un ST este construit pornind de la o colecție
;; de sufixe și pentru că ne dorim să nu calculăm toate
;; sufixele decât dacă este nevoie, vom modifica toate
;; funcțiile care prelucrau liste de sufixe pentru a
;; prelucra fluxuri de sufixe.
;;
;; Obs: fără această modificare a listelor de sufixe în
;; fluxuri de sufixe, și presupunând că am manipulat
;; arborii de sufixe doar prin interfața definită în
;; fișierul suffix-tree (respectând astfel bariera de 
;; abstractizare), ar trebui să alterăm doar funcția 
;; suffixes->st care este practic un constructor pentru
;; tipul ST.
;; Din cauza transformării listelor de sufixe în fluxuri,
;; avem mult mai multe implementări de modificat.
;; Puteam evita acest lucru? Da, utilizând conceptul de
;; colecție de sufixe de la început (în loc să presupunem
;; că ele vor fi prelucrate ca liste). În loc de cons,
;; car, cdr, map, filter, etc. am fi folosit de fiecare
;; dată collection-cons, collection-first, ... etc. -
;; aceste funcții fiind definite într-o bibliotecă
;; inițială ca fiind echivalentele lor pe liste, și
;; redefinite ulterior în stream-cons, stream-first,
;; ... etc. Operatorii pe colecții de sufixe ar fi 
;; folosit, desigur, doar funcții de tip collection-.
;;
;; Am ales să nu procedăm astfel pentru că ar fi provocat
;; confuzie la momentul respectiv (când chiar operatorii
;; pe liste erau o noutate) și pentru a vă da ocazia să
;; faceți singuri acest "re-design".


; TODO
; Copiați din etapele anterioare implementările funcțiilor
; de mai jos și modificați-le astfel:
; - Toate funcțiile care lucrează cu liste de sufixe vor
;   lucra cu un nou tip de date Collection, ai cărui
;   constructori și operatori vor fi definiți de voi
;   în fișierul collection.rkt.
; - Pentru toate funcțiile, trebuie să vă asigurați că
;   este respectată bariera de abstractizare (atât în 
;   cazul tipului ST cât și în cazul tipului Collection).
; Obs: cu cât mai multe funcții rămân nemodificate, cu atât
; este mai bine (înseamnă că design-ul inițial a fost bun).
(define (longest-common-prefix w1 w2)
  (define (longest-aux word1 word2 pref)
    (cond
      [(or (null? word1) (null? word2)) (list (reverse pref) word1 word2)] ; prefixul e chiar un cuvant
      [(not (equal? (car word1) (car word2))) (list (reverse pref) word1 word2)]
      [else (longest-aux (cdr word1) (cdr word2) (cons (car word1) pref))]
      ))

  (longest-aux w1 w2 '()))

; am schimbat, în numele funcției, cuvântul list în
; cuvântul collection
(define (longest-common-prefix-of-collection words)
  (define (check-prefix prefix ws) ; check prefix from consecutive words
    (cond
      [(col-empty? prefix) empty-col]
      [(col-empty? ws) prefix]
      [else (let* ([pref (col-car (longest-common-prefix prefix (col-car ws)))] ; vad daca e mai mic
                   [other-words (col-cdr ws)])          ; restul cuvintelor
                      (check-prefix pref other-words))] ; ia urmatorul cuvant
      ))

  (check-prefix (col-car words) words))


(define (match-pattern-with-label st pattern)
  (define (match-aux branch Label)
    (let* ([branch2 (get-ch-branch st Label)]
           [Label2 (get-branch-label branch2)]
           [Tag2 (longest-common-prefix (get-branch-label branch2) pattern)]
           [pref2 (car Tag2)])
                (cond
                  [(equal? pref2 pattern) #t]
                  [(equal? pref2 Label2) (list Label2 (car (take-right Tag2 1)) branch)]
                  [else (list #f pref2)])))

  (let* ([label (car pattern)]
         [branch (get-ch-branch st label)])
             (if (equal? branch #f)
                 (list #f '())
                 (match-aux (get-branch-subtree branch) label))))


(define (st-has-pattern? st pattern)
  (let* ([result (match-pattern-with-label st pattern)]) ; #t || (#f common) || (tree)
    (cond
      [(equal? #t result) #t]         ; verific daca e deja sablonul
      [(equal? (car result) #f) #f]   ; verific daca nu exista subsirul
      [(list? (cadr result)) ; subarbore de forma (label -> st)
                     (let* ([subtree-tag (cadr result)]
                            [subtree-label (caddr result)])
                                 (st-has-pattern? subtree-label subtree-tag))])
    ))


(define (get-suffixes text)
  (if (col-empty? text)
      empty-col
      (col-cons text (get-suffixes (col-cdr text)))
      ))


(define (get-ch-words words ch)
  (define (common-prefix? word)
    (let* ([pattern (list ch)]
           [ans (longest-common-prefix word pattern)]
           [pref (car ans)])
              (equal? pref pattern)))

  (col-filter common-prefix? words))


(define (ast-func suffixes)
  (let*([ch (car (col-car suffixes))] ; caracterul cautat
        [label (list (list ch))] ; pun labelul cum trebuie pe ramura
        [suffs (col-map cdr suffixes)])
          (append label suffs)
          ))


(define (cst-func suffixes)
  (let*([f (λ (suff acc) (car (longest-common-prefix suff acc)))] ; functie de scos prefixul
        [acc (col-car suffixes)]  ; caut prefixul comun incepand folosind primul cuvant
        [pref (longest-common-prefix-of-collection suffixes)] ; prefixul comun
        [g (λ (suff) (car (cdr (longest-common-prefix suff pref))))]) ; scot partea ramasa
            (cons pref
                  (col-map g suffixes)) ; rezultatul
        ))


; considerați că și parametrul alphabet este un flux
; (desigur, și suffixes este un flux, fiind o colecție
; de sufixe)
(define (suffixes->st labeling-func suffixes alphabet)
    (if (col-null-car? suffixes)
        empty-col
        (letrec ([label (λ (word) (get-branch-label word))]
                 [ch-words (λ (letter) (get-ch-words suffixes letter))] ; caut sufixele dupa carcactere
                 [get-subst (λ (word) (get-branch-subtree word))]

                 [get-st (λ (text) (labeling-func (ch-words text)))] ; formez arborele
                 [alpha (col-filter  (λ (letter) (col-not-empty? (ch-words letter))) alphabet)] ; caut literele folosite in text
                 [branches (col-map (λ (text) (get-st text)) alpha)]
                 
                 [group (λ (word) (cons (label word)
                                        (suffixes->st labeling-func (get-subst word) alphabet)))])
                    (col-map group branches))
      ))


; nu uitați să convertiți alfabetul într-un flux
(define text->st
  (λ (text)
    (λ (func)
      (let* ([fin (append text (list #\$))]        ; textul + $ la final
             [suffs (get-suffixes fin)]            ; generare de sufixe ale cuvantului
             [sorted (sort fin char<?)]            ; sortez caracterele care apar in cuvant
             [uniques (list->col (remove-duplicates sorted))]) ; ca sa nu se repete
                 (suffixes->st func suffs uniques)))))


(define text->ast
  (λ (text) ((text->st text) ast-func)))


(define text->cst
  (λ (text) ((text->st text) cst-func)))


; dacă ați respectat bariera de abstractizare,
; această funcție va rămâne nemodificată.
(define (substring? text pattern)
  (let stree ([st (text->ast text)]) (st-has-pattern? st pattern)))

; dacă ați respectat bariera de abstractizare,
; această funcție va rămâne nemodificată.
(define (repeated-substring-of-given-length text len)
  (let ([st (text->cst text)])
  (letrec (
           [search (λ (repeated-func st leng acr) ; ca sa merg pe fiecare copil
                        (cond
                          [(col-empty? st) #f]
                          [else (repeated-func st leng acr)]))]
           [repeated (λ (st size acr) ; un fel de dfs
                          (let* ([fst (first-branch st)]
                                 [oth (other-branches st)]
                                 [ost (get-branch-subtree fst)]
                                 [label (get-branch-label fst)]
                                 [lmax (+ size (length label))])
                                    (cond
                                      [(col-empty? ost) (search repeated oth size acr)] ; nu mai am ce face cu prima ramura
                                      [(<= len lmax) (letrec ([smsize (- len size)] ; tai din substring
                                                              [tag (take label smsize)]) (append acr tag))]
                                      [else (let* ([acl (append acr label)] ; coboram
                                                   [lst (search repeated ost lmax acl)])  ; pe stanga
                                                        (if (not (equal? lst #f))
                                                              lst
                                                              (search repeated oth size acr)))]) ; pe dreapta
                            ))]) (repeated st 0 '()) ; plec din radacina
        )))