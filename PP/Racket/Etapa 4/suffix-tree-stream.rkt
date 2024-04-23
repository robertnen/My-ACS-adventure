#lang racket

(provide (all-defined-out))

;; În etapele anterioare am lucrat cu reprezentarea 
;; arborelui de sufixe sub forma unei liste de ramuri,
;; unde fiecare ramură era o pereche între eticheta primei
;; muchii și subarborele de sub această muchie. Pentru textul
;; "banana", reprezentarea arborelui de sufixe compact
;; (cu stringuri pentru claritate) era:
;;
;;'(("$")
;;  ("a" ("$")
;;       ("na" ("$")
;;             ("na$")))
;;  ("banana$")
;;  ("na" ("$")
;;        ("na$")))
;;
;; Pentru aplicații ca găsirea unui șablon sau găsirea unui
;; subșir de lungime minimă dată care se repetă în text
;; este suficientă explorarea parțială a arborelui de
;; sufixe, ceea ce înseamnă că am avea de câștigat dacă
;; acesta ar fi construit "leneș" (lazy) - calculând
;; doar acele ramuri de care este nevoie și doar până la
;; adâncimea de care este nevoie. De exemplu, pentru a găsi
;; un subșir de lungime 3 care se repetă în textul 
;; "banana", ar trebui detaliate doar câteva muchii, ca în
;; reprezentarea de mai jos:
;;
;;'(("$")                  - această cale eșuează
;;  ("a" ("$")             - această cale eșuează
;;       ("na" <promise>)) - subarborele de sub eticheta "na"
;;                           este și el un flux (nevid)
;;  <promise>)               
;;
;; În momentul în care constatăm că nodul de sub eticheta
;; "na" este un nod intern și descoperim că șirul "ana"
;; (corespunzând căii de la rădăcină) are lungimea 3,
;; funcția întoarce "ana" fără a construi restul arborelui
;; (o economie importantă de timp în cazul textelor lungi).
;;
;; Pentru a obține acest comportament, vom schimba
;; reprezentarea astfel încât un arbore de sufixe să fie
;; un flux (nu o listă) de ramuri.
;; Fiecare ramură rămâne o pereche, nu un flux, între
;; eticheta primei muchii și subarborele de sub aceasta
;; (care subarbore este flux la rândul său, etc.).
;; Textele și etichetele rămân liste (nu fluxuri) de caractere.


;; În continuare veți redefini biblioteca pentru manipularea
;; arborilor de sufixe, pentru a ține cont de modificarea
;; reprezentării.


; TODO 1
; Redefiniți următorii constructori și operatori ai structurii
; de date ST. Este posibil ca anumite definiții să rămână
; ca în etapa 1.

; arborele de sufixe vid
; empty-st : -> ST
(define empty-st empty-stream)

; operatorul care verifică dacă un ST este vid
; st-empty? : ST -> Bool

(define (st-empty? st)
  (stream-empty? st))

; operatorul care extrage prima ramură a unui ST
; first-branch : ST -> (Label, ST)

(define (first-branch st)
  (cond
    [(stream-empty? st) st]
    [else (stream-first st)]
    ))

; operatorul care extrage restul ramurilor unui ST (fără prima)
; other-branches : ST -> [(Label, ST)]
; Obs: signatura [(Label, ST)] se citește aici ca "flux de  
; perechi între o etichetă și un ST"
(define (other-branches st)
  (cond
    [(stream-empty? st) st]
    [else (stream-rest st)]
    ))

; operatorul care extrage eticheta din vârful unei ramuri
; get-branch-label : (Label, ST) -> Label
(define (get-branch-label branch)
  (cond
    [(null? branch) empty-stream]
    [(pair? branch) (car branch)]
    [else #f]
    ))

; operatorul care extrage subarborele de sub eticheta ramurii
; get-branch-subtree : (Label, ST) -> ST
(define (get-branch-subtree branch)
  (cond
    [(null? branch) empty-stream]
    [else (cdr branch)]
    ))

; operatorul care identifică ramura unui ST a cărei etichetă
; începe cu caracterul ch, dacă o asemenea ramură există
; Obs: din felul în care sunt construiți arborii, nu vor exista
; niciodată două ramuri care încep cu același caracter.
; get-ch-branch : ST x Char -> (Label, ST) - ramura, dacă există
;                           -> Bool        - altfel fals
; Obs: Dacă în etapa 1 ați respectat bariera de abstractizare,
; implementarea funcției get-ch-branch nu va trebui modificată.
(define (get-ch-branch st ch)
  (let*([fst (first-branch st)]
        [ost (other-branches st)])
    (cond
      [(st-empty? st) #f] ; frunza
      [(char=? ch (car (get-branch-label fst))) fst]
      [else (get-ch-branch ost ch)])
      ))
