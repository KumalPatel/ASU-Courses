 
;CSE 240 Spring 2019 HW12
; Name: Kumal Patel

; For testing a procedure, you may comment out other procedures.

;Q1: (8 points) creates a list with alternative values from the 3 given lists

(define (alternate lst1 lst2 lst3) ; size-n problem
(if(or(null? lst1)(null? lst2)(null? lst3)) ; stopping condition and corresponding return value
   '()
   (append(list(car lst1)(car lst2)(car lst3))(alternate (cdr lst1) (cdr lst2) (cdr lst3))) ; size-m problem and solution of size-n problem
)
)
;Test case:
(alternate '(1 2 3 4) '(a b c d) '(m n o p))
; Test output:
;'(1 a m 2 b n 3 c o 4 d p).

;Q2: (8 points) shuffle lists one and two in pairs

(define (pairs lst1 lst2) ; size-n problem
(if(or(null? lst1)(null? lst2)) ; stopping condition and corresponding return value
   '()
   (append(list(cons(car lst1)(car lst2)))(pairs(cdr lst1)(cdr lst2))) ; size-m problem and solution of size-n problem
)  
)
;Test case:
(pairs '(1 2 3 4) '(a b c d))
;Test output
;'((1 . a) (2 . b) (3 . c) (4 . d))

  
;Q3: (9 points)
; encryption
(define encrypt
  (lambda (str)
    (define character-encryption
  (lambda(ch)
  (if(or(char-alphabetic? ch)(char-numeric? ch))
     (character-rotation ch)
     ch
)
))
    (define character-rotation
  (lambda(ch)
    (integer->char(+(char->integer ch)encryptkey)
)))
    (define encryptkey (read))
(list->string(map character-encryption
                   (string->list str)
))
))        
;decryption
(define decrypt
  (lambda (str)
    (define character-decryption
  (lambda(ch)
  (if(or(char-alphabetic? ch)(char-numeric? ch)(and(>(char->integer ch)59)(<(char->integer ch)63)))
     (character-rotation2 ch)
     ch
)
))
    (define character-rotation2
  (lambda(ch)
    (integer->char(-(char->integer ch)decryptkey)
)))
    (define decryptkey (read))    
(list->string(map character-decryption
                  (string->list str)
))
))
; Test cases:
(encrypt "Hello CSE240!")
(decrypt "Lipps GWI684!")
(encrypt "Hello CSE598?")
(decrypt "Lipps GWI9=<?")

; Test outputs:
;4
;"Lipps GWI684!"
;4
;"Hello CSE240!"
;4
;"Lipps GWI9=<?"
;4
;"Hello CSE598?"
> 