#lang racket
(require "suffix-tree.rkt")

(provide (all-defined-out))

; TODO 2
; Implementați o funcție care primește două cuvinte (liste
; de caractere) w1 și w2 și calculează cel mai lung prefix
; comun al acestora, împreună cu restul celor două cuvinte
; după eliminarea prefixului comun.
; ex:
; (longest-common-prefix '(#\w #\h #\y) '(#\w #\h #\e #\n))
; => '((#\w #\h) (#\y) (#\e #\n))
; Folosiți recursivitate pe coadă.
(define (longest-common-prefix w1 w2)
  (define (longest-aux word1 word2 pref)
    (cond
      [(equal? w1 #f) '('() '() '())]
      [(or (null? word1) (null? word2)) (list pref word1 word2)] ; prefixul e chiar un cuvant
      [(not (equal? (car word1) (car word2))) (list pref word1 word2)]
      [else (longest-aux (cdr word1) (cdr word2) (append pref (list (car word1))))]
      ))

  (longest-aux w1 w2 '()))

; TODO 3
; Implementați recursiv o funcție care primește o listă nevidă
; de cuvinte care încep cu același caracter și calculează cel
; mai lung prefix comun al acestora.
; Opriți căutarea (parcurgerea) în momentul în care aveți garanția
; că prefixul comun curent este prefixul comun final.
(define (longest-common-prefix-of-list words)
  (define (check-prefix prefix ws) ; check prefix from consecutive words
    (cond
      [(null? prefix) '()]
      [(null? ws) prefix]
      [else (let* ([pref (car (longest-common-prefix prefix (car ws)))] ; vad daca e mai mic
                   [other-words (cdr ws)])          ; restul cuvintelor
                  (check-prefix pref other-words))] ; ia urmatorul cuvant
      ))

  (check-prefix (car words) words))

  ;; Următoarele două funcții sunt utile căutării unui șablon
  ;; (pattern) într-un text cu ajutorul arborelui de sufixe.
  ;; Ideea de căutare este următoarea:
  ;; - dacă șablonul există în text, atunci există un sufix care
  ;;   începe cu acest șablon, deci există o cale care începe din
  ;;   rădăcina arborelui care se potrivește cu șablonul
  ;; - vom căuta ramura a cărei etichetă începe cu prima literă
  ;;   din șablon
  ;; - dacă nu găsim această ramură, șablonul nu apare în text
  ;; - dacă șablonul este conținut integral în eticheta ramurii,
  ;;   atunci el apare în text
  ;; - dacă șablonul se potrivește cu eticheta dar nu este conținut
  ;;   în ea (de exemplu șablonul "nana$" se potrivește cu eticheta
  ;;   "na"), atunci continuăm căutarea în subarborele ramurii
  ;; - dacă șablonul nu se potrivește cu eticheta (de exemplu
  ;;   șablonul "numai" nu se potrivește cu eticheta "na"), atunci
  ;;   el nu apare în text (altfel, eticheta ar fi fost "n", nu
  ;;   "na", pentru că eticheta este cel mai lung prefix comun al
  ;;   sufixelor din subarborele său)


; TODO 4
  ; Implementați funcția match-pattern-with-label care primește un
  ; arbore de sufixe și un șablon nevid și realizează un singur pas
  ; din procesul prezentat mai sus - identifică ramura arborelui a
  ; cărei etichetă începe cu prima literă din șablon, apoi
  ; determină cât de bine se potrivește șablonul cu eticheta,
  ; întorcând ca rezultat:
  ; - true, dacă șablonul este conținut integral în etichetă
  ; - lista (etichetă, nou pattern, subarbore), dacă șablonul se
  ;   potrivește cu eticheta dar nu este conținut în ea
  ;   (ex: ("na", "na$", subarborele de sub eticheta "na")
  ;   pentru șablonul inițial "nana$" și eticheta "na")
  ; - lista (false, cel mai lung prefix comun între etichetă și
  ;   șablon), dacă șablonul nu s-a potrivit cu eticheta sau nu
  ;   s-a găsit din start o etichetă care începe cu litera dorită
  ;   (ex1: (false, "n") pentru șablonul "numai" și eticheta "na")
  ;   (ex2: (false, "") pentru etichetă negăsită)
  ; Obs: deși exemplele folosesc stringuri pentru claritate, vă
  ; reamintim că în realitate lucrăm cu liste de caractere.
(define (match-pattern-with-label st pattern)
  (define (match-aux st2 pattern2 subtree L)
    (let* ([branch2 (get-ch-branch st2 (car pattern2))]
           [Labels2 (longest-common-prefix (get-branch-label branch2) pattern2)] ; '(pref w1 w2)
           [pref2 (car Labels2)]          ; caut prefixul dintre eticheta si pattern
           [w12 (cadr Labels2)]           ; ce ramane din eticheta dupa functie
           [w22 (caddr Labels2)]          ; ce ramane din pattern dupa functie
           [child (list (list (list #\$)) branch2)] ; subarborele ramas
           [parent (list pattern2 child)] ; prefix parinte
           [subtree (append L parent)])   ; final result
                (cond
                  [(equal? #f branch2) (list #f '())]   ; nu exista sufixul
                  [(equal? pref2 pattern2) subtree]     ; exista subsirul
                  [(null? w22) subtree]                 ; patternul e un subsir
                  [(not (null? w12)) (list #f pref2)]   ; labelul difera de pattern
                  [else (match-aux (other-branches branch2) w22 subtree (append L pref2))]
                  )))

  (let* ([branch (get-ch-branch st (car pattern))]
         [Labels (longest-common-prefix (get-branch-label branch) pattern)] ; '(pref w1 w2)
         [pref (car Labels)]        ; caut prefixul dintre eticheta si pattern
         [w1 (cadr Labels)]         ; ce ramane din eticheta dupa functie
         [w2 (caddr Labels)])       ; ce ramane din pattern dupa functie
            (cond
              [(equal? #f branch) (list #f '())]  ; nu exista sufixul
              [(equal? pref pattern) #t]          ; exista subsirul
              [(null? w2) #t]                     ; patternul e un subsir
              [(not (null? w1)) (list #f pref)]   ; labelul difera de pattern
              [else (match-aux (other-branches branch) w2 branch (list pref))]
              )))

; TODO 5
  ; Implementați funcția st-has-pattern? care primește un
  ; arbore de sufixe și un șablon și întoarce true dacă șablonul
  ; apare în arbore, respectiv false în caz contrar.
(define (st-has-pattern? st pattern)
  (let* ([result (match-pattern-with-label st pattern)]) ; #t || (#f common) || (tree)
    (cond
      [(equal? #t result) #t]         ; verific daca e deja sablonul
      [(equal? (car result) #f) #f]   ; verific daca nu exista subsirul
      [else #t]                       ; e un subarbore
      )))