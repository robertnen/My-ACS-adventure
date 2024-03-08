#lang racket

(require "suffix-tree.rkt")
(require "etapa1.rkt")

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

; ST compact pentru "banana".
(define stree-1
  '(((#\$))
    ((#\a) ((#\$))
           ((#\n #\a) ((#\$))
                      ((#\n #\a #\$))))
    ((#\b #\a #\n #\a #\n #\a #\$))
    ((#\n #\a) ((#\$))
               ((#\n #\a #\$)))))

; ST compact pentru sufixele nevide ale lui "abb".
(define stree-2
  '(((#\a #\b #\b #\$))
    ((#\b) ((#\$))
           ((#\b #\$)))))

; Convertește primul "semn" al unui string într-un caracter.
(define (chr s) (car (string->list s)))


; Testele încep de aici.
(sunt 5 exerciții)

; Numerotat de la 0 ca să urmăm numărul TODO-urilor.
(exercițiul 0 : 15 puncte)
(when (andmap procedure? (list st-empty? first-branch other-branches get-branch-label get-branch-subtree))
  (check-part 'a (/ 1. 6) (and (list? empty-st) (zero? (length empty-st))) is #t) 
  (check-part 'b (/ 1. 6) (and (st-empty? empty-st) (not (st-empty? stree-1)) (not (st-empty? stree-2))) is #t)
  (check-part 'c (/ 1. 6) (first-branch stree-2) is '((#\a #\b #\b #\$)))
  (check-part 'd (/ 1. 6) (other-branches stree-2) is '(((#\b) ((#\$)) ((#\b #\$)))))
  (let [(branch '((#\u) ((#\k #\u #\l #\e #\l #\e #\$)) ((#\l #\e #\l #\e #\$))))] ; Ramură ce stochează "ukulele" și "ulele".
    (check-part 'e (/ 1. 6) (get-branch-label branch) is '(#\u))
    (check-part 'f (/ 1. 6) (get-branch-subtree branch) is '(((#\k #\u #\l #\e #\l #\e #\$)) ((#\l #\e #\l #\e #\$))))))

(exercițiul 1 : 15 puncte)
(check-part 'a (/ 1 5) (get-ch-branch stree-1 (chr "a")) is '((#\a) ((#\$)) ((#\n #\a) ((#\$)) ((#\n #\a #\$)))))
(check-part 'b (/ 1 5) (get-ch-branch stree-1 (chr "b")) is '((#\b #\a #\n #\a #\n #\a #\$)))
(check-part 'c (/ 1 5) (get-ch-branch stree-1 (chr "c")) is #f)
(check-part 'd (/ 1 5) (get-ch-branch stree-1 (chr "$")) is '((#\$)))
(check-part 'e (/ 1 5) (get-ch-branch stree-1 (chr "n")) is '((#\n #\a) ((#\$)) ((#\n #\a #\$))))

(exercițiul 2 : 20 puncte)
(check-part 'a (/ 1 4) (longest-common-prefix (string->list "why") (string->list "when")) is '((#\w #\h) (#\y) (#\e #\n)))
(check-part 'b (/ 1 4) (longest-common-prefix (string->list "why") (string->list "how")) is '(() (#\w #\h #\y) (#\h #\o #\w)))
(check-part 'c (/ 1 4) (longest-common-prefix (string->list "why") (string->list "why not")) is '((#\w #\h #\y) () (#\space #\n #\o #\t)))
(check-part 'd (/ 1 4) (longest-common-prefix (string->list "why not") (string->list "why not")) is '((#\w #\h #\y #\space #\n #\o #\t) () ()))

(exercițiul 3 : 20 puncte)
(check-part 'a (/ 1 4) (longest-common-prefix-of-list (map string->list (list "when" "where" "why" "who"))) is '(#\w #\h))
(check-part 'b (/ 1 4) (longest-common-prefix-of-list (map string->list (list "when" "when is it" "when?"))) is '(#\w #\h #\e #\n))
(check-part 'c (/ 1 4) (longest-common-prefix-of-list (map string->list (list "when is it" "when?" "wendy"))) is '(#\w))
(check-part 'd (/ 1 4) (longest-common-prefix-of-list (map string->list (list "so many" "so" "soo many tests"))) is '(#\s #\o))

(exercițiul 4 : 30 puncte)
; Găsim șablonul la pasul curent.
(check-part 'a (/ 1 6) (match-pattern-with-label stree-1 (string->list "na")) is #t)
(check-part 'b (/ 1 6) (match-pattern-with-label stree-1 (string->list "banan")) is #t)
; Găsim un nod, dar nu este conținut de șablon.
(check-part 'c (/ 1 6) (match-pattern-with-label stree-1 (string->list "baba")) is '(#f (#\b #\a)))
(check-part 'd (/ 1 6) (match-pattern-with-label stree-1 (string->list "cab")) is '(#f ()))
; Găsim un prefix al șablonului și trebuie să continuăm căutarea.
(check-part 'e (/ 1 6) (match-pattern-with-label stree-1 (string->list "ana")) is '((#\a) (#\n #\a) (((#\$)) ((#\n #\a) ((#\$)) ((#\n #\a #\$))))))
(check-part 'f (/ 1 6) (match-pattern-with-label stree-1 (string->list "nan")) is '((#\n #\a) (#\n) (((#\$)) ((#\n #\a #\$)))))

(exercițiul 5 : 20 puncte)
(check-part 'a (/ 1 5) (st-has-pattern? stree-1 (string->list "na")) is #t)
(check-part 'b (/ 1 5) (st-has-pattern? stree-1 (string->list "bananana")) is #f)
(check-part 'c (/ 1 5) (st-has-pattern? stree-1 (string->list "ana")) is #t)
(check-part 'd (/ 1 5) (st-has-pattern? stree-1 (string->list "anan")) is #t)
(check-part 'e (/ 1 5) (st-has-pattern? stree-1 (string->list "ananb")) is #f)

(sumar)
