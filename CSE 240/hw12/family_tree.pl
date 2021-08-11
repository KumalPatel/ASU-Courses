/* Database for family tree. It consists of facts and rules. */
/* A portion of the family tree has been implemented for you */

/* Facts */
/* Question 4.1 */
female(ana).
female(may).
female(sue).
female(syd).
female(pam).
female(kat).
female(fey).
female(liz).

male(kam).
male(jeb).
male(rob).
male(tio).
male(zev).
male(dom).
male(dag).
male(gio).

mother_of(ana,rob).
mother_of(ana,syd).
mother_of(may,tio).
mother_of(may,pam).
mother_of(sue,kat).
mother_of(sue,dom).
mother_of(syd,dag).
mother_of(syd,fey).
mother_of(pam,liz).
mother_of(pam,gio).

father_of(kam,rob).
father_of(kam,syd).
father_of(jeb,tio).
father_of(jeb,pam).
father_of(rob,kat).
father_of(rob,dom).
father_of(tio,dag).
father_of(tio,fey).
father_of(zev,liz).
father_of(zev,geo).

/* Rules */
is_male(X) :-
        male(X);
        father_of(X,_).

/* Question 4.2 */
is_female(X) :-
        female(X);
        mother_of(X,_).

/* Question 4.3 */
parent_of(X,Y) :-
        mother_of(X,Y);
        father_of(X,Y).

/* Question 4.4 */
sibling_of(X,Y) :-
         parent_of(Z,X),
         parent_of(Z,Y),
         X \= Y.

/* Questoin 4.5 */
grandmother_of(X,Z) :-
        mother_of(X,Y),
        (mother_of(Y,Z); father_of(Y,Z)).

/* Question 4.5 */
grandfather_of(X,Z) :-
        father_of(X,Y),
        (father_of(Y,Z); mother_of(Y,Z)).

/* Question 4.5 */
descendent_of(X,Y) :-
         parent_of(Y,X).
descendent_of(X,Y) :-
         parent_of(Y,Z),
         descendent_of(X,Z).

