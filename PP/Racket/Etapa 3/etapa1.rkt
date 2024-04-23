#lang racket
(require "suffix-tree.rkt")

(provide (all-defined-out))

; funcție care primește două cuvinte w1 și w2 și calculează cel mai lung prefix comun
; longest-common-prefix: w1 x w2 -> '(prefix (w1 / prefix) (w2 / prefix))
(define (longest-common-prefix w1 w2)
  (define (longest-aux word1 word2 pref)
    (cond
      [(equal? w1 #f) '('() '() '())]
      [(or (null? word1) (null? word2)) (list pref word1 word2)] ; prefixul e chiar un cuvant
      [(not (equal? (car word1) (car word2))) (list pref word1 word2)]
      [else (longest-aux (cdr word1) (cdr word2) (append pref (list (car word1))))]
      ))

  (longest-aux w1 w2 '()))

; functie care ofera cel mai lung prefix comun al unor cuvinte
; longest-common-prefix-of-list: words -> prefix
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


; functie care returneaza subarborele care are eticheta pattern sau o lista cu fals si prefixul maxim
; match-pattern-with-label: st x pattern -> '(#f '())    - daca nu exista sufixul
;                                        -> '(#f prefix) - patternul e subsir
;                                        -> subtree      - am gasit subarborele
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

; functie care verifica daca exista patternul ca subsir in etichete
; st-has-pattern?: st x pattern -> #t - daca e subsir
;                               -> #f - daca nu e subsir
(define (st-has-pattern? st pattern)
  (let* ([result (match-pattern-with-label st pattern)]) ; #t || (#f common) || (tree)
    (cond
      [(equal? #t result) #t]         ; verific daca e deja sablonul
      [(equal? (car result) #f) #f]   ; verific daca nu exista subsirul
      [else #t]                       ; e un subarbore
      )))