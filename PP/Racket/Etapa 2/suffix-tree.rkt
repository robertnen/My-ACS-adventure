#lang racket

(provide (all-defined-out))

;; Un arbore de sufixe este un arbore care conține toate sufixele
;; unui text T (de obicei un text lung asupra căruia sunt necesare
;; prelucrări multiple), ca în figura de mai jos (arborele de
;; sufixe pentru textul "BANANA", unde nodurile sunt reprezentate
;; prin *, iar muchiile sunt etichetate cu subșiruri din T).
;;
;;                            *
;;   __________ ______________|______________
;;  |          |              |              |
;;  $          A           BANANA$           NA
;;  |          |              |              |
;;  *          *              *              *
;;       ______|______                 ______|______
;;      |             |               |             |
;;      $             NA              $            NA$
;;      |             |               |             |
;;      *             *               *             *
;;                 ___|___
;;                |       |
;;                $      NA$
;;                |       |
;;                *       *
;;
;; Fiecare cale în arborele de sufixe corespunde unui subșir al
;; textului T, iar fiecare cale completă corespunde unui sufix
;; (pentru a nu "pierde" sufixele care sunt prefixele altor sufixe,
;; adăugăm la sfârșitul fiecărui sufix caracterul special $).
;; În figură, calea cea mai din stânga corespunde sufixului vid.
;;
;; Arborele de mai sus este un arbore de sufixe compact, adică
;; folosește minimul de muchii posibile (fiecare muchie este
;; etichetată cu cel mai lung prefix comun al sufixelor de mai jos.
;;
;; În contrast, un arbore de sufixe atomic folosește numărul maxim
;; de muchii, fiecare muchie fiind etichetată cu un singur caracter.
;; Exemplu (pentru textul "BANANA"):
;;
;;                            *
;;   __________ ______________|______________
;;  |          |              |              |
;;  $          A              B              N
;;  |          |              |              |
;;  *          *              *              *
;;         ____|____          |              |
;;        |         |         |              |
;;        $         N         A              A
;;        |         |         |              |
;;        *         *         *              *
;;                  |         |          ____|____
;;                  |         |         |         |
;;                  A         N         $         N
;;                  |         |         |         |
;;                  *         *         *         *
;;                __|__       |                   |
;;               |     |      |                   |
;;               $     N      A                   A
;;               |     |      |                   |
;;               *     *      *                   *
;;                     |      |                   |
;;                     A      N                   $
;;                     |      |                   |
;;                     *      *                   *
;;                     |      |
;;                     $      A
;;                     |      |
;;                     *      *
;;                            |
;;                            $
;;                            |
;;                            *
;;
;; Indiferent cu care din cele două reprezentări lucrăm,
;; reprezentăm un arbore de sufixe ca pe o listă de ramuri,
;; unde fiecare ramură este o pereche între eticheta primei
;; muchii și subarborele de sub această muchie. Pentru textul
;; "banana", reprezentarea arborelui de sufixe compact este:
;;
;;'(("$")
;;  ("a" ("$")
;;       ("na" ("$")
;;             ("na$")))
;;  ("banana$")
;;  ("na" ("$")
;;        ("na$")))
;;
;; Am oferit reprezentarea cu stringuri pentru claritate. În
;; realitate, pentru a profita de funcțiile de lucru cu liste,
;; vom reține fiecare string ca listă de caractere, iar
;; reprezentarea reală devine:
;;
;;'(((#\$))
;;  ((#\a) ((#\$))
;;         ((#\n #\a) ((#\$))
;;                    ((#\n #\a #\$))))
;;  ((#\b #\a #\n #\a #\n #\a #\$))
;;  ((#\n #\a) ((#\$))
;;             ((#\n #\a #\$))))
;;
;; În continuare veți defini o bibliotecă pentru manipularea
;; arborilor de sufixe definiți anterior.


; TODO 1
; Definiți următorii constructori și operatori ai structurii
; de date Arbore de Sufixe (pe viitor vom prescurta numele
; acestei structuri de date ca ST, de la denumirea în engleză).
; Obs: Tipul de date Label este de fapt tipul [Char] (listă
; de caractere), dar am folosit aliasul Label pentru a clarifica
; semnificația valorilor de tip Label).

; arborele de sufixe vid
; empty-st : -> ST
(define empty-st '())

; operatorul care verifică dacă un ST este vid
; st-empty? : ST -> Bool
(define (st-empty? st)
  (equal? st empty-st))

; operatorul care extrage prima ramură a unui ST
; first-branch : ST -> (Label, ST)
(define (first-branch st)
  (cond
    [(st-empty? st) '()]
    [else (car st)]
    ))

; operatorul care extrage restul ramurilor unui ST (fără prima)
; other-branches : ST -> [(Label, ST)]
; Obs: signatura [(Label, ST)] se citește ca "listă de perechi
; între o etichetă și un ST"
(define (other-branches st)
  (cond
    [(st-empty? st) '()]
    [else (cdr st)]
    ))

; operatorul care extrage eticheta din vârful unei ramuri
; get-branch-label : (Label, ST) -> Label
(define (get-branch-label branch)
  (cond
    [(st-empty? branch)'()]
    [(list? branch) (car branch)]
    [else #f]
    ))

; operatorul care extrage subarborele de sub eticheta ramurii
; get-branch-subtree : (Label, ST) -> ST
(define (get-branch-subtree branch)
  (cond
    [(st-empty? branch) '()]
    [else (cdr branch)]
    ))

; operatorul care identifică ramura unui ST a cărei etichetă
; începe cu caracterul ch, dacă o asemenea ramură există
; Obs: din felul în care sunt construiți arborii, nu vor exista
; niciodată două ramuri care încep cu același caracter.
; get-ch-branch : ST x Char -> (Label, ST) - ramura, dacă există
;                           -> Bool        - altfel fals
; Important: Pentru manipularea arborelui folosiți operatorii de
; mai sus, astfel încât implementarea funcției get-ch-branch să
; nu trebuiască schimbată în caz că schimbăm modul de reprezentare
; a arborilor de sufixe.
(define (get-ch-branch st ch)
  (let*([fst (first-branch st)]
        [ost (other-branches st)])
    (cond
      [(null? st) #f] ; frunza
      [(char=? ch (car (get-branch-label fst))) fst]
      [else (get-ch-branch ost ch)])
      ))


