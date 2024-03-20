#lang racket

(require "suffix-tree.rkt")
(require "etapa2.rkt")

; ignorați următoarele linii de cod...
(define show-defaults 999) ; câte exerciții la care s-au întors rezultate default să fie arătate detaliat
(define prepend #t) (define nopoints #f) (define name-ex '(testul testele trecut capitolul))
(define default-results `(#f 0 () your-code-here)) (define (default-result r) (set! default-results (cons r default-results))) (define : 'separator) (define punct 'string) (define puncte 'string) (define BONUS 'string) (define exerciții 'string)
(define total 0) (define all '()) (define n-ex 0) (define p-ex 0) (define n-exercs -1) (define default-returns '()) (define (ex n sep p . s) (set! n-ex n) (set! p-ex p) (set! all (cons (list n p) all))) (define exercițiul ex) (define (sunt n s) (set! n-exercs n)) (define s-a string-append)
(define (p . L) (map (λ (e) (display e) (when (> (string-length (format "~a" e)) 0) (display " "))) L) (newline)) (define (p-n-ex) (format "[~a]" (if nopoints (string-join (list (symbol->string (cadddr name-ex)) (number->string n-ex) "/" (number->string n-exercs))) n-ex)))
(define (epart ep% pfix full) (if (< (caddr ep%) 1) (s-a pfix (if full "" (s-a (symbol->string (car name-ex)) " ")) (if (and nopoints (not full)) "" (number->string n-ex)) (symbol->string (cadr ep%))) (if (and nopoints (not full)) "" (s-a pfix (if full "" (s-a (symbol->string (car name-ex)) " ")) (number->string n-ex)))))
(define (whengood ep%) (let [(pts (* p-ex (caddr ep%)))] (and (if prepend (printf "+~v: " pts) (printf "~a[OK] " (p-n-ex))) (if nopoints (p (epart ep% "" #f) "rezolvat") (p (epart ep% "" #f) "rezolvat: +" pts (if (= pts 1) 'punct 'puncte))) (set! total (+ total pts)))))
(define (whenbad ep% gvn expcd msg) (and (when (member gvn default-results) (set! default-returns (cons (epart ep% "" #t) default-returns))) (when (or (not (member gvn default-results)) (<= (length default-returns) show-defaults)) (bad-res ep% gvn expcd msg))))
(define (bad-res ep% gvn expcd msg) (p (if prepend "+0.0:" (format "~a[--]" (p-n-ex))) (epart ep% "la " #f) 'rezultatul gvn msg expcd))
(define (check-conds e gvn conds) (or (null? conds) (let ([r ((car conds) gvn)]) (if (eq? r #t) (check-conds e gvn (cdr conds)) (whenbad e gvn "" (or r "nu îndeplinește condițiile (completitudine, stabilitate)"))))))
(define (check-part part per given main-test expected . conds) (let* ([e (list n-ex part per)] [p? (pair? (cdr main-test))] [p (if p? (car main-test) identity)] [t ((if p? cadr car) main-test)] [m ((if p? cddr cdr) main-test)]) (when (eq? #t (check-conds e given conds)) (if (t (p given) expected) (whengood e) (whenbad e (p given) expected m)))))
(define (check given main-test expected . conds) (apply check-part '- 1 given main-test expected conds))
(define the cons) (define is (cons equal? "diferă de cel așteptat")) (define in (cons member "nu se află printre variantele așteptate"))
(define same-set-as (cons (λ (x y) (apply equal? (map list->seteqv (list x y)))) "nu este aceeași mulțime cu"))
(define same-unique (cons (λ (x y) (and (apply = (map length (list x y))) ((car same-set-as) x y))) "nu sunt aceleași rezultate cu"))
(define (sumar) (when (and (not (null? default-returns)) (< show-defaults (length default-returns))) (p "... rezultatul implicit dat la" (cadr name-ex) (reverse default-returns))) (when (not nopoints) (p 'total: total 'puncte)))
(define (mark-helper) (printf "---~nEx  puncte    Total până aici~n") (foldr (λ (e-p t) (p (car e-p) ': (cadr e-p) "puncte. total 1 -" (car e-p) ': (+ t (cadr e-p))) (+ t (cadr e-p))) 0 all) (newline))


; Definițiile pentru tema aceasta încep de aici.

; sufixe banana
(define suff-1
  '((#\b #\a #\n #\a #\n #\a #\$)
    (#\a #\n #\a #\n #\a #\$)
    (#\n #\a #\n #\a #\$)
    (#\a #\n #\a #\$)
    (#\n #\a #\$)
    (#\a #\$)
    (#\$)))

; sufixe agcgacgag
(define suff-2
  '((#\a #\g #\c #\g #\a #\c #\g #\a #\g #\$)
    (#\g #\c #\g #\a #\c #\g #\a #\g #\$)
    (#\c #\g #\a #\c #\g #\a #\g #\$)
    (#\g #\a #\c #\g #\a #\g #\$)
    (#\a #\c #\g #\a #\g #\$)
    (#\c #\g #\a #\g #\$)
    (#\g #\a #\g #\$)
    (#\a #\g #\$)
    (#\g #\$)
    (#\$)))

; sufixe mississippi
(define suff-3
  '((#\m #\i #\s #\s #\i #\s #\s #\i #\p #\p #\i #\$)
    (#\i #\s #\s #\i #\s #\s #\i #\p #\p #\i #\$)
    (#\s #\s #\i #\s #\s #\i #\p #\p #\i #\$)
    (#\s #\i #\s #\s #\i #\p #\p #\i #\$)
    (#\i #\s #\s #\i #\p #\p #\i #\$)
    (#\s #\s #\i #\p #\p #\i #\$)
    (#\s #\i #\p #\p #\i #\$)
    (#\i #\p #\p #\i #\$)
    (#\p #\p #\i #\$)
    (#\p #\i #\$)
    (#\i #\$)
    (#\$)))

; ST compact pentru "banana".
(define stree-1c
  '(((#\$))
    ((#\a) ((#\$))
           ((#\n #\a) ((#\$))
                      ((#\n #\a #\$))))
    ((#\b #\a #\n #\a #\n #\a #\$))
    ((#\n #\a) ((#\$))
               ((#\n #\a #\$)))))

; ST atomic pentru "banana".
(define stree-1a
  '(((#\a) ((#\n) ((#\a) ((#\n) ((#\a) ((#\$)))) ((#\$)))) ((#\$)))
    ((#\b) ((#\a) ((#\n) ((#\a) ((#\n) ((#\a) ((#\$))))))))
    ((#\n) ((#\a) ((#\n) ((#\a) ((#\$)))) ((#\$))))
    ((#\$))))

; ST compact pentru "agcgacgag".
(define stree-2c
  '(((#\c #\g #\a) ((#\c #\g #\a #\g #\$)) ((#\g #\$)))
    ((#\a) ((#\c #\g #\a #\g #\$)) ((#\g) ((#\c #\g #\a #\c #\g #\a #\g #\$)) ((#\$))))
    ((#\g) ((#\c #\g #\a #\c #\g #\a #\g #\$)) ((#\a) ((#\c #\g #\a #\g #\$)) ((#\g #\$))) ((#\$)))
    ((#\$))))

; ST atomic pentru "agcgacgag".
(define stree-2a
  '(((#\$))
    ((#\a) ((#\c) ((#\g) ((#\a) ((#\g) ((#\$)))))) ((#\g) ((#\$)) ((#\c) ((#\g) ((#\a) ((#\c) ((#\g) ((#\a) ((#\g) ((#\$)))))))))))
    ((#\c) ((#\g) ((#\a) ((#\c) ((#\g) ((#\a) ((#\g) ((#\$)))))) ((#\g) ((#\$))))))
    ((#\g)
     ((#\$))
     ((#\a) ((#\c) ((#\g) ((#\a) ((#\g) ((#\$)))))) ((#\g) ((#\$))))
     ((#\c) ((#\g) ((#\a) ((#\c) ((#\g) ((#\a) ((#\g) ((#\$))))))))))))

; ST compact pentru "mississippi".
(define stree-3c
  '(((#\$))
    ((#\i) ((#\$)) ((#\p #\p #\i #\$)) ((#\s #\s #\i) ((#\p #\p #\i #\$)) ((#\s #\s #\i #\p #\p #\i #\$))))
    ((#\m #\i #\s #\s #\i #\s #\s #\i #\p #\p #\i #\$))
    ((#\p) ((#\i #\$)) ((#\p #\i #\$)))
    ((#\s) ((#\i) ((#\p #\p #\i #\$)) ((#\s #\s #\i #\p #\p #\i #\$))) ((#\s #\i) ((#\p #\p #\i #\$)) ((#\s #\s #\i #\p #\p #\i #\$)))))
  )

; ST atomic pentru "mississippi".
(define stree-3a
  '(((#\$))
    ((#\m) ((#\i) ((#\s) ((#\s) ((#\i) ((#\s) ((#\s) ((#\i) ((#\p) ((#\p) ((#\i) ((#\$)))))))))))))
    ((#\i)
     ((#\$))
     ((#\s) ((#\s) ((#\i) ((#\s) ((#\s) ((#\i) ((#\p) ((#\p) ((#\i) ((#\$)))))))) ((#\p) ((#\p) ((#\i) ((#\$))))))))
     ((#\p) ((#\p) ((#\i) ((#\$))))))
    ((#\s)
     ((#\i) ((#\s) ((#\s) ((#\i) ((#\p) ((#\p) ((#\i) ((#\$)))))))) ((#\p) ((#\p) ((#\i) ((#\$))))))
     ((#\s) ((#\i) ((#\s) ((#\s) ((#\i) ((#\p) ((#\p) ((#\i) ((#\$)))))))) ((#\p) ((#\p) ((#\i) ((#\$))))))))
    ((#\p) ((#\i) ((#\$))) ((#\p) ((#\i) ((#\$)))))))


; Testele încep de aici.
(sunt 6 exerciții)

(exercițiul 1 : 10 puncte)
(check-part 'a (/ 1 2) (map (compose get-suffixes string->list) '("what's$" "in$" "a$" "name?$"))  is
            '(((#\w #\h #\a #\t #\' #\s #\$) (#\h #\a #\t #\' #\s #\$) (#\a #\t #\' #\s #\$) (#\t #\' #\s #\$) (#\' #\s #\$) (#\s #\$) (#\$))
              ((#\i #\n #\$) (#\n #\$) (#\$))
              ((#\a #\$) (#\$))
              ((#\n #\a #\m #\e #\? #\$) (#\a #\m #\e #\? #\$) (#\m #\e #\? #\$) (#\e #\? #\$) (#\? #\$) (#\$))))
(check-part 'b (/ 1 2) (map (compose get-suffixes string->list) '("nothing,$" "unless$" "name$" "is$" "a$" "free$" "variable.$"))  is
            '(((#\n #\o #\t #\h #\i #\n #\g #\, #\$)
               (#\o #\t #\h #\i #\n #\g #\, #\$)
               (#\t #\h #\i #\n #\g #\, #\$)
               (#\h #\i #\n #\g #\, #\$)
               (#\i #\n #\g #\, #\$)
               (#\n #\g #\, #\$)
               (#\g #\, #\$)
               (#\, #\$)
               (#\$))
              ((#\u #\n #\l #\e #\s #\s #\$) (#\n #\l #\e #\s #\s #\$) (#\l #\e #\s #\s #\$) (#\e #\s #\s #\$) (#\s #\s #\$) (#\s #\$) (#\$))
              ((#\n #\a #\m #\e #\$) (#\a #\m #\e #\$) (#\m #\e #\$) (#\e #\$) (#\$))
              ((#\i #\s #\$) (#\s #\$) (#\$))
              ((#\a #\$) (#\$))
              ((#\f #\r #\e #\e #\$) (#\r #\e #\e #\$) (#\e #\e #\$) (#\e #\$) (#\$))
              ((#\v #\a #\r #\i #\a #\b #\l #\e #\. #\$)
               (#\a #\r #\i #\a #\b #\l #\e #\. #\$)
               (#\r #\i #\a #\b #\l #\e #\. #\$)
               (#\i #\a #\b #\l #\e #\. #\$)
               (#\a #\b #\l #\e #\. #\$)
               (#\b #\l #\e #\. #\$)
               (#\l #\e #\. #\$)
               (#\e #\. #\$)
               (#\. #\$)
               (#\$))))

(exercițiul 2 : 15 puncte)
(check-part 'a (/ 1 3) (get-ch-words (map string->list '("Lesser" "leather" "never" "weathered" "wetter" "weather" "better")) #\w) is
            '((#\w #\e #\a #\t #\h #\e #\r #\e #\d) (#\w #\e #\t #\t #\e #\r) (#\w #\e #\a #\t #\h #\e #\r)))
(check-part 'b (/ 1 3) (get-ch-words (map string->list '("A" "peck" "of" "pickled" "peppers" "Peter" "Piper" "picked.")) #\p) is
            '((#\p #\e #\c #\k) (#\p #\i #\c #\k #\l #\e #\d) (#\p #\e #\p #\p #\e #\r #\s) (#\p #\i #\c #\k #\e #\d #\.)))
(check-part 'c (/ 1 3) (map (λ (ch) (get-ch-words (map string->list '("Betty" "Botter" "bought" "some" "butter")) ch)) '(#\B #\u #\s)) is
            '(((#\B #\e #\t #\t #\y) (#\B #\o #\t #\t #\e #\r)) () ((#\s #\o #\m #\e))))

(exercițiul 3 : 10 puncte)
(check-part 'a (/ 1 2) (ast-func (map string->list '("when" "where" "why" "who"))) is
            '((#\w) (#\h #\e #\n) (#\h #\e #\r #\e) (#\h #\y) (#\h #\o)))
(check-part 'b (/ 1 2) (ast-func (map string->list '("all" "about" "ants" "as" "a"))) is
            '((#\a) (#\l #\l) (#\b #\o #\u #\t) (#\n #\t #\s) (#\s) ()))

(exercițiul 4 : 15 puncte)
(check-part 'a (/ 1 3) (cst-func (map string->list '("when" "where" "why" "who"))) is
            '((#\w #\h) (#\e #\n) (#\e #\r #\e) (#\y) (#\o)))
(check-part 'b (/ 1 3) (cst-func (map string->list '("all" "about" "ants" "as" "a"))) is
            '((#\a) (#\l #\l) (#\b #\o #\u #\t) (#\n #\t #\s) (#\s) ()))
(check-part 'c (/ 1 3) (cst-func (map string->list '("sometimes" "something" "somewhere"))) is
            '((#\s #\o #\m #\e) (#\t #\i #\m #\e #\s) (#\t #\h #\i #\n #\g) (#\w #\h #\e #\r #\e)))

(exercițiul 5 : 40 puncte)
(check-part 'a (/ 1 8) (suffixes->st ast-func suff-1 (string->list "abn$")) is stree-1a)
(check-part 'b (/ 1 8) (suffixes->st cst-func suff-1 (string->list "$abn")) is stree-1c)
(check-part 'c (/ 1 8) (suffixes->st ast-func suff-2 (string->list "$acg")) is stree-2a)
(check-part 'd (/ 1 8) (suffixes->st cst-func suff-2 (string->list "cag$")) is stree-2c)
(check-part 'e (/ 1 8) (suffixes->st ast-func suff-3 (string->list "$misp")) is stree-3a)
(check-part 'f (/ 1 8) (suffixes->st cst-func suff-3 (string->list "$imps")) is stree-3c)
(check-part 'g (/ 1 8) (suffixes->st ast-func suff-2 (string->list "$abcdefg")) is stree-2a)
(check-part 'h (/ 1 8) (suffixes->st cst-func suff-3 (string->list "$abcdefghijklmnopqrstuvwxyz")) is stree-3c)

(exercițiul 6 : 30 puncte)
(when (andmap procedure? (list text->ast text->cst))
  (check-part 'a (/ 1 6) (text->ast (string->list "banana")) is
              '(((#\$))
                ((#\a) ((#\$)) ((#\n) ((#\a) ((#\$)) ((#\n) ((#\a) ((#\$)))))))
                ((#\b) ((#\a) ((#\n) ((#\a) ((#\n) ((#\a) ((#\$))))))))
                ((#\n) ((#\a) ((#\$)) ((#\n) ((#\a) ((#\$))))))))
  (check-part 'b (/ 1 6) (text->cst (string->list "banana")) is stree-1c)
  (check-part 'c (/ 1 6) (text->ast (string->list "agcgacgag")) is stree-2a)
  (check-part 'd (/ 1 6) (text->cst (string->list "mississippi")) is stree-3c)
  (check-part 'e (/ 1 6) (text->ast (string->list "abracadabra")) is
              '(((#\$))
                ((#\a)
                 ((#\$))
                 ((#\b) ((#\r) ((#\a) ((#\$)) ((#\c) ((#\a) ((#\d) ((#\a) ((#\b) ((#\r) ((#\a) ((#\$))))))))))))
                 ((#\c) ((#\a) ((#\d) ((#\a) ((#\b) ((#\r) ((#\a) ((#\$)))))))))
                 ((#\d) ((#\a) ((#\b) ((#\r) ((#\a) ((#\$))))))))
                ((#\b) ((#\r) ((#\a) ((#\$)) ((#\c) ((#\a) ((#\d) ((#\a) ((#\b) ((#\r) ((#\a) ((#\$))))))))))))
                ((#\c) ((#\a) ((#\d) ((#\a) ((#\b) ((#\r) ((#\a) ((#\$)))))))))
                ((#\d) ((#\a) ((#\b) ((#\r) ((#\a) ((#\$)))))))
                ((#\r) ((#\a) ((#\$)) ((#\c) ((#\a) ((#\d) ((#\a) ((#\b) ((#\r) ((#\a) ((#\$)))))))))))))
  (check-part 'f (/ 1 6) (text->cst (string->list "hocus pocus preparatus")) is
              '(((#\space #\p) ((#\o #\c #\u #\s #\space #\p #\r #\e #\p #\a #\r #\a #\t #\u #\s #\$)) ((#\r #\e #\p #\a #\r #\a #\t #\u #\s #\$)))
                ((#\$))
                ((#\a) ((#\r #\a #\t #\u #\s #\$)) ((#\t #\u #\s #\$)))
                ((#\c #\u #\s #\space #\p)
                 ((#\o #\c #\u #\s #\space #\p #\r #\e #\p #\a #\r #\a #\t #\u #\s #\$))
                 ((#\r #\e #\p #\a #\r #\a #\t #\u #\s #\$)))
                ((#\e #\p #\a #\r #\a #\t #\u #\s #\$))
                ((#\h #\o #\c #\u #\s #\space #\p #\o #\c #\u #\s #\space #\p #\r #\e #\p #\a #\r #\a #\t #\u #\s #\$))
                ((#\o #\c #\u #\s #\space #\p)
                 ((#\o #\c #\u #\s #\space #\p #\r #\e #\p #\a #\r #\a #\t #\u #\s #\$))
                 ((#\r #\e #\p #\a #\r #\a #\t #\u #\s #\$)))
                ((#\p)
                 ((#\a #\r #\a #\t #\u #\s #\$))
                 ((#\o #\c #\u #\s #\space #\p #\r #\e #\p #\a #\r #\a #\t #\u #\s #\$))
                 ((#\r #\e #\p #\a #\r #\a #\t #\u #\s #\$)))
                ((#\r) ((#\a #\t #\u #\s #\$)) ((#\e #\p #\a #\r #\a #\t #\u #\s #\$)))
                ((#\s)
                 ((#\space #\p) ((#\o #\c #\u #\s #\space #\p #\r #\e #\p #\a #\r #\a #\t #\u #\s #\$)) ((#\r #\e #\p #\a #\r #\a #\t #\u #\s #\$)))
                 ((#\$)))
                ((#\t #\u #\s #\$))
                ((#\u #\s)
                 ((#\space #\p) ((#\o #\c #\u #\s #\space #\p #\r #\e #\p #\a #\r #\a #\t #\u #\s #\$)) ((#\r #\e #\p #\a #\r #\a #\t #\u #\s #\$)))
                 ((#\$))))))

(sumar)
