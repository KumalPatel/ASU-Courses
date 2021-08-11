(define foo ; size-n problem
  (lambda(x y)
    (if(or(< y 0)(= y 0)) ; stopping condition 
       x
    (if(or(< x 0)(= x 0)) ; stopping condition
       y
    (if(or(> x y)(= x y))
       (+ x (foo(- x 1)(- y 2))) ; size-m problem and solution of size-n problem
    (if(< x y)
       (+ y (foo(- x 2)(- y 3))) ; size-m problem and solution of size-n problem
))))
))