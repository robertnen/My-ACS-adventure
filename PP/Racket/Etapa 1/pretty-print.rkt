#lang racket
(require "suffix-tree.rkt")

(provide (all-defined-out))

; Numerotează elementele unei liste (asemănător cu `enumerate` din Python).
; Returnează perechi de forma `(indice . valoare)`.
(define (enumerate l) (map cons (range (length l)) l))

; Formatează un ST ca un șir de caractere.
(define (pretty-print st)
  ; Creează prefixul pentru indentare al unui rând din desenul final. `lasts`
  ; este o listă cu valori boolene, care pentru fiecare nivel de indentare
  ; reține dacă elementul indentat este ultimul de pe nivelul respective.
  (define (make-indent lasts)
    (if (null? lasts) ""
        (let ([prev-last (take lasts (sub1 (length lasts)))]
              [curr-last (last lasts)])
          (string-append
           (apply string-append (map (lambda (is-last) (if is-last "    " "│   ")) prev-last))
           (if curr-last "└───" "├───")))))

  ; Formatează o etichetă (un rând din desenul final).
  (define (print-label lasts str)
    (format "~a~a\n" (make-indent lasts) str))

  ; Formatează recursiv un ST.
  (define (helper lasts tree)
    (let* ([label (list->string (get-branch-label tree))]
           [subs (get-branch-subtree tree)]
           [last-index (sub1 (length subs))])

      (apply string-append
             (print-label lasts label)
             (map (lambda (pair)
                    (match-let* ([(cons index branch) pair]
                                 [next-lasts (append lasts (list (= index last-index)))])
                      (helper next-lasts branch)))
                  (enumerate subs)))))

  ; Ca să tratăm toate cazurile uniform, inserăm o etichetă falsă pentru
  ; rădăcină. Fără etichetă, arborele top-level diferă de subarbori prin faptul
  ; că subarborii sunt liste ce încep cu câte o etichetă.
  (define augmented-tree (cons (string->list "*") st))

  (helper '() augmented-tree))


; ST pentru "banana".
(define stree-1
  '(((#\$))
    ((#\a) ((#\$))
           ((#\n #\a) ((#\$))
                      ((#\n #\a #\$))))
    ((#\b #\a #\n #\a #\n #\a #\$))
    ((#\n #\a) ((#\$))
               ((#\n #\a #\$)))))

; ST pentru sufixele nevide ale lui "abb".
(define stree-2
  '(((#\a #\b #\b #\$))
    ((#\b) ((#\$))
           ((#\b #\$)))))

(displayln (pretty-print '(((#\a)))))
(displayln (pretty-print '(((#\b) ((#\b #\$)) ((#\$))))))
(displayln (pretty-print stree-1))
(displayln (pretty-print stree-2))
