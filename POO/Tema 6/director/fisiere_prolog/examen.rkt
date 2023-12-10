#lang racket
(define (factorial x)
  (if (= x 1)
      1
      (* x (factorial (- x 1)))))
  
(define (mult-map-by q)
  (lambda (x)
    (* x q)))

(map (mult-map-by 5) '(1 2 3))
(define (comp f g)
  (lambda (x)
    (f (g x))))
((comp car cdr) '(1 2 3))