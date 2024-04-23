#lang racket

(require "etapa3.rkt")

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

; text mai lung
(define long-text (string->list "In computer science, functional programming is a programming paradigm where programs are constructed by applying and composing functions. It is a declarative programming paradigm in which function definitions are trees of expressions that map values to other values, rather than a sequence of imperative statements which update the running state of the program.

In functional programming, functions are treated as first-class citizens, meaning that they can be bound to names (including local identifiers), passed as arguments, and returned from other functions, just as any other data type can. This allows programs to be written in a declarative and composable style, where small functions are combined in a modular manner.

Functional programming is sometimes treated as synonymous with purely functional programming, a subset of functional programming which treats all functions as deterministic mathematical functions, or pure functions. When a pure function is called with some given arguments, it will always return the same result, and cannot be affected by any mutable state or other side effects. This is in contrast with impure procedures, common in imperative programming, which can have side effects (such as modifying the program's state or taking input from a user). Proponents of purely functional programming claim that by restricting side effects, programs can have fewer bugs, be easier to debug and test, and be more suited to formal verification.[1][2]

Functional programming has its roots in academia, evolving from the lambda calculus, a formal system of computation based only on functions. Functional programming has historically been less popular than imperative programming, but many functional languages are seeing use today in industry and education, including Common Lisp, Scheme,[3][4][5][6] Clojure, Wolfram Language,[7][8] Racket,[9] Erlang,[10][11][12] Elixir,[13] OCaml,[14][15] Haskell,[16][17] and F#.[18][19] Functional programming is also key to some languages that have found success in specific domains, like JavaScript in the Web,[20] R in statistics,[21][22] J, K and Q in financial analysis, and XQuery/XSLT for XML.[23][24] Domain-specific declarative languages like SQL and Lex/Yacc use some elements of functional programming, such as not allowing mutable values.[25] In addition, many other programming languages support programming in a functional style or have implemented features from functional programming, such as C++11, C#,[26] Kotlin,[27] Perl,[28] PHP,[29] Python,[30] Go,[31] Rust,[32] Raku,[33] Scala,[34] and Java (since Java 8).[35]"))

; subșir repetat de lungime 10 în textul lung
(define res-e '(#\newline #\newline #\F #\u #\n #\c #\t #\i #\o #\n))

; subșir repetat de lungime 30 în textul lung
(define res-g '(#\space #\f #\u #\n #\c #\t #\i #\o #\n #\a #\l #\space
                        #\p #\r #\o #\g #\r #\a #\m #\m #\i #\n #\g #\, #\space
                        #\s #\u #\c #\h #\space))


; Testele încep de aici.
(sunt 3 exerciții)

(exercițiul 1 : 10 puncte)
(check-part 'a (/ 1 2) (map ((curry substring?) (string->list "banana")) (map string->list '("b" "g" "n" "baa" "banana" "nan" "anab" " na"))) is
            '(#t #f #t #f #t #t #f #f))
(check-part 'b (/ 1 2) (map ((curry substring?) (string->list " xabxabxaaxbbxabxabxaaxbb")) (map string->list '("xax" " " "aax" "bba" "x" "abg" " xabxabxaaxbbxabxabx"))) is
            '(#f #t #t #f #t #f #t))

(exercițiul 2 : 50 puncte)
(check-part 'a (/ 1 5) (longest-common-substring (string->list "xabxa") (string->list "babxabxaaxxaba")) is '(#\x #\a #\b #\x #\a))
(check-part 'b (/ 1 5) (longest-common-substring (string->list "babcxabac") (string->list "babxabxaaxxaba")) is '(#\x #\a #\b #\a))
(check-part 'c (/ 1 5) (longest-common-substring (string->list "babcxabac") (string->list "babdxabdxadaxxdaba")) is '(#\b #\a #\b))
(check-part 'd (/ 1 5) (map ((curry longest-common-substring) (string->list "babcxabac")) (map string->list '("ghghghgh" "babcxabac" " babcxabac" "babcxabacx" "xab"))) is
            '(() (#\b #\a #\b #\c #\x #\a #\b #\a #\c) (#\b #\a #\b #\c #\x #\a #\b #\a #\c) (#\b #\a #\b #\c #\x #\a #\b #\a #\c) (#\x #\a #\b)))
(check-part 'e (/ 1 5) (longest-common-substring (string->list "banana") (string->list "bandana")) is '(#\b #\a #\n))

(exercițiul 3 : 60 puncte)
(let ([input-list (string->list "xabxabxaaxbbxabxabxaaxbb")])
  (check-part 'a (/ 1 6) (repeated-substring-of-given-length input-list 10) is '(#\a #\b #\x #\a #\b #\x #\a #\a #\x #\b))
  (check-part 'b (/ 1 6) (repeated-substring-of-given-length input-list 11) is '(#\a #\b #\x #\a #\b #\x #\a #\a #\x #\b #\b))
  (check-part 'c (/ 1 6) (repeated-substring-of-given-length input-list 12) is '(#\x #\a #\b #\x #\a #\b #\x #\a #\a #\x #\b #\b))
  (check-part 'd (/ 1 6) (repeated-substring-of-given-length input-list 13) is #f))
(check-part 'e (/ 1 6) (repeated-substring-of-given-length long-text 10) is res-e)
(check-part 'f (/ 1 6) (repeated-substring-of-given-length long-text 30) is res-g)


(sumar)
