#lang racket

(require "suffix-tree-stream.rkt")
(require "etapa4.rkt")
(require "datadump.rkt")
(provide (all-defined-out))

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

; Funcție care convertește o listă într-un flux.
; list->stream : List -> Stream
(define (list->stream L)
  (if (null? L)
      empty-stream
      (stream-cons (car L) (list->stream (cdr L)))))

; Convertește un ST implementat cu fluxuri în varianta lui "eager"/normală.
; streamy->eager : ST -> ~ST~?
(define (streamy->eager st)
  (map
   (lambda (branch) (cons (car branch) (streamy->eager (cdr branch))))
   (stream->list st)))

; Verifică dacă o valoare dată este un stream. Listele obișnuite satisfac
; interfața pentru `stream?`, așa că verificăm explicit împotriva lor.
; real-stream? : Any -> Bool
(define (real-stream? s)
  (and (stream? s) (not (list? s))))


; Test care ignoră comparația cu un rezultat exact, pentru a testa doar condiții.
(define just-conds (cons (lambda (_ __) #t) "this shouldn't happen?..."))

; Condiție care oprește verificarea dacă un rezultat este placeholder-ul pentru
; funcții neimplementate. Util când testul presupune că rezultatul are o anumită
; formă, iar placeholder-ul ar provoca o eroare.
(define (attempted res) (or (not (equal? 'your-code-here res)) "e placeholder-ul, nu ai încercat exercițiul"))

; Condiție ca o funcție să întoarcă fluxuri și fiecare flux să conțină colecția corectă de cuvinte.
(define (correct-collection res)
  (lambda (candidate)
    (cond
      [(not (andmap real-stream? candidate))           "nu este o listă de fluxuri"]
      [(not (equal? res (map stream->list candidate))) (format "diferă de rezultatul corect ~s" res)]
      [else                                            true])))

; Condiție ca ast-func/cst-func să întoarcă o pereche etichetă-flux cu conținutul corect
(define (correct-pair res-labels res-suffixes)
  (lambda (candidate)
    (cond
      [(not (andmap pair? candidate))                            "nu este o listă de perechi"]
      [(not (andmap real-stream? (map cdr candidate)))           "nu este o listă de perechi etichetă-flux"]
      [(not (equal? res-labels (map car candidate)))             (format "nu are etichetele corecte ~s" res-labels)]
      [(not (equal? res-suffixes
                    (map (compose stream->list cdr) candidate))) (format "nu determină corect noile sufixe ~s" res-suffixes)]
      [else                                                      true])))


; Sufixe corecte.
(define res-suffixes '(((#\w #\h #\a #\t #\' #\s #\$) (#\h #\a #\t #\' #\s #\$) (#\a #\t #\' #\s #\$) (#\t #\' #\s #\$) (#\' #\s #\$) (#\s #\$) (#\$))
                       ((#\i #\n #\$) (#\n #\$) (#\$))
                       ((#\a #\$) (#\$))
                       ((#\n #\a #\m #\e #\? #\$) (#\a #\m #\e #\? #\$) (#\m #\e #\? #\$) (#\e #\? #\$) (#\? #\$) (#\$))))

; ch-words corecte.
(define res-ch-words '(((#\w #\e #\a #\t #\h #\e #\r #\e #\d) (#\w #\e #\t #\t #\e #\r) (#\w #\e #\a #\t #\h #\e #\r))
                       ((#\p #\e #\c #\k) (#\p #\i #\c #\k #\l #\e #\d) (#\p #\e #\p #\p #\e #\r #\s) (#\p #\i #\c #\k #\e #\d #\.))
                       ()))

; Etichete și noi sufixe corecte pentru ast-func.
(define res-ast-labels '((#\w) (#\a)))
(define res-ast-new-suffixes '(((#\h #\e #\n) (#\h #\e #\r #\e) (#\h #\y) (#\h #\o))
                               ((#\l #\l) (#\b #\o #\u #\t) (#\n #\t #\s) (#\s) ())))

; Etichete și noi sufixe corecte pentru cst-func.
(define res-cst-labels '((#\w #\h) (#\a)))
(define res-cst-new-suffixes '(((#\e #\n) (#\e #\r #\e) (#\y) (#\o))
                               ((#\l #\l) (#\b #\o #\u #\t) (#\n #\t #\s) (#\s) ())))

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
  '(((#\$))
    ((#\a) ((#\$)) ((#\n) ((#\a) ((#\$)) ((#\n) ((#\a) ((#\$)))))))
    ((#\b) ((#\a) ((#\n) ((#\a) ((#\n) ((#\a) ((#\$))))))))
    ((#\n) ((#\a) ((#\$)) ((#\n) ((#\a) ((#\$))))))))


; Testele încep de aici.
(sunt 4 exerciții)

(exercițiul 1 : 30 puncte)
(check-part 'a (/ 1 5)
            (map (λ (S) (longest-common-prefix-of-collection (stream-map string->list S)))
                 (map list->stream '(("when" "where" "why" "who")
                                     ("when" "when is it" "when?")
                                     ("when is it" "when?" "wendy")
                                     ("so many" "so" "soo many tests"))))
            is '((#\w #\h) (#\w #\h #\e #\n) (#\w) (#\s #\o)))
(check-part 'b (/ 1 5)
            (map (compose get-suffixes string->list) '("what's$" "in$" "a$" "name?$"))
            just-conds 'nil attempted (correct-collection res-suffixes))
(check-part 'c (/ 1 5)
            (map (λ (S ch) (get-ch-words (stream-map string->list S) ch))
                 (map list->stream '(("Lesser" "leather" "never" "weathered" "wetter" "weather" "better")
                                     ("A" "peck" "of" "pickled" "peppers" "Peter" "Piper" "picked.")
                                     ("Betty" "Botter" "bought" "some" "butter")))
                 '(#\w #\p #\u))
            just-conds 'nil attempted (correct-collection res-ch-words))
(check-part 'd (/ 1 5)
            (map (λ (S) (ast-func (stream-map string->list S)))
                 (map list->stream '(("when" "where" "why" "who")
                                     ("all" "about" "ants" "as" "a"))))
            just-conds 'nil attempted (correct-pair res-ast-labels res-ast-new-suffixes))
(check-part 'e (/ 1 5)
            (map (λ (S) (cst-func (stream-map string->list S)))
                 (map list->stream '(("when" "where" "why" "who")
                                     ("all" "about" "ants" "as" "a"))))
            just-conds 'nil attempted (correct-pair res-cst-labels res-cst-new-suffixes))


(exercițiul 2 : 30 puncte)
; Condiție care verifică recursiv dacă un ST dat are structura dorită (cu fluxuri).
(define (correct-stream-structure st)
  (cond
    [(not (real-stream? st))        "nu e bun; fiecare ST trebuie să fie stream"]
    [(not (stream-andmap pair? st)) "nu e bun; fiecare ramură trebuie să fie o pereche obișnuită"]
    [else
     ; Verificăm recursiv toți subarborii.
     (stream-fold (lambda (res b)
                    (if (string? res) res ; Dacă am găsit deja o eroare, o propagăm.
                        (correct-stream-structure (get-branch-subtree b))))
                  true st)]))

; Condiție care verifică dacă un ST este varianta cu fluxuri a unui ST normal dat.
(define (is-stream-of st-res)
  (lambda (st)
    (if (equal? st-res (streamy->eager st)) true
        "nu e bun; nu are etichetele corecte (îl poți vizualiza cu `streamy->eager`)")))

(when (andmap procedure? (list text->ast text->cst))
  (check-part 'a (/ 1 2) (text->ast (string->list "banana"))
              just-conds 'nil attempted correct-stream-structure (is-stream-of stree-1a))
  (check-part 'b (/ 1 2) (text->cst (string->list "banana"))
              just-conds 'nil attempted correct-stream-structure (is-stream-of stree-1c))
  )


(exercițiul 3 : 30 puncte)
(let ([input-list (string->list text-big)]) ; Text mare definit în fișierul datadump.rkt
  (check-part 'a (/ 1 2)
              (map ((curry substring?) input-list) (map string->list '("particularly" "definitely" "comu" "computer-based")))
              is '(#t #f #f #t))
  (check-part 'b (/ 1 2)
              (map ((curry substring?) input-list) (map string->list '("racket" "Can Programming Be Liberated" "Scheme, ")))
              is '(#f #t #t)))


(exercițiul 4 : 30 puncte)
(let ([input-list (string->list text-big)]) ; Text mare definit în fișierul datadump.rkt
  (check-part 'a (/ 1 3) (repeated-substring-of-given-length input-list 20) is
              '(#\newline #\newline #\F #\u #\n #\c #\t #\i #\o #\n #\a #\l #\space #\p #\r #\o #\g #\r #\a #\m))
  (check-part 'b (/ 1 3) (repeated-substring-of-given-length input-list 11) is
              '(#\newline #\newline #\? #\- #\space #\m #\o #\t #\h #\e #\r))
  (check-part 'c (/ 1 3) (repeated-substring-of-given-length input-list 28) is
              '(#\newline #\newline #\H #\i #\g #\h #\e #\r #\- #\o #\r #\d #\e #\r #\space #\f #\u #\n #\c #\t #\i #\o #\n #\s #\space #\a #\r #\e)))

(sumar)
