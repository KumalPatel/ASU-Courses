foo(X,Y,Z):- % stopping condition
	Y =< 0,
	Z is X.

foo(X,Y,Z):- % stopping condition 
	X =< 0,
	Z is Y.

foo(X,Y,Z):- % size-n problem
	X >= Y,
	X1 is X - 1,
	Y1 is Y - 2,
	foo(X1, Y1, Z1), % size-m problem 
	Z is X + Z1. % soltion of size-n problem

foo(X,Y,Z):- % size-n problem
	X < Y,
	X1 is X -2,
	Y1 is Y -3,
	foo(X1, Y1, Z1), % size-m problem 
	Z is Y + Z1. % soltion of size-n problem
 	

