#lang racket

(provide (all-defined-out))

; arborele de sufixe vid
; empty-st: -> ST
(define empty-st '())

; operatorul care verifică dacă un ST este vid
; st-empty?: ST -> Bool
(define (st-empty? st)
  (equal? st empty-st))

; operatorul care extrage prima ramură a unui ST
; first-branch: ST -> (Label, ST)
(define (first-branch st)
  (cond
    [(st-empty? st) '()]
    [else (car st)]
    ))

; operatorul care extrage restul ramurilor unui ST (fără prima)
; other-branches: ST -> [(Label, ST)]
(define (other-branches st)
  (cond
    [(st-empty? st) '()]
    [else (cdr st)]
    ))

; operatorul care extrage eticheta din vârful unei ramuri
; get-branch-label: (Label, ST) -> Label
(define (get-branch-label branch)
  (cond
    [(st-empty? branch)'()]
    [(list? branch) (car branch)]
    [else #f]
    ))

; operatorul care extrage subarborele de sub eticheta ramurii
; get-branch-subtree: (Label, ST) -> ST
(define (get-branch-subtree branch)
  (cond
    [(st-empty? branch) '()]
    [else (cdr branch)]
    ))

; operatorul care identifică ramura unui ST a cărei etichetă
; get-ch-branch: ST x Char -> (Label, ST) - ramura, dacă există
;                          -> Bool        - altfel fals
(define (get-ch-branch st ch)
  (let*([fst (first-branch st)]
        [ost (other-branches st)])
    (cond
      [(null? st) #f] ; frunza
      [(char=? ch (car (get-branch-label fst))) fst]
      [else (get-ch-branch ost ch)])
      ))


