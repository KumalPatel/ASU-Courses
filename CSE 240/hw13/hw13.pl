/* Question 1.1 */

edge(wa,or).
edge(wa,id).

edge(or,wa).
edge(or,id).
edge(or,nv).
edge(or,ca).

edge(ca,az).
edge(ca,nv).
edge(ca,or).

edge(id,wa).
edge(id,or).
edge(id,nv).
edge(id,ut).
edge(id,wy).
edge(id,mt).

edge(nv,id).
edge(nv,or).
edge(nv,ca).
edge(nv,az).
edge(nv,ut).

edge(az,ca).
edge(az,nv).
edge(az,ut).
edge(az,nm).

edge(ut,az).
edge(ut,nv).
edge(ut,id).
edge(ut,wy).
edge(ut,co).

edge(mt,id).
edge(mt,wy).
edge(mt,nd).
edge(mt,sd).

edge(wy,mt).
edge(wy,id).
edge(wy,ut).
edge(wy,sd).
edge(wy,ne).

edge(co,nm).
edge(co,az).
edge(co,ut).
edge(co,wy).
edge(co,ne).
edge(co,ks).

edge(nm,az).
edge(nm,co).

edge(nd,mt).
edge(nd,sd).

edge(sd,nd).
edge(sd,mt).
edge(sd,wy).
edge(sd,ne).

edge(ne,sd).
edge(ne,wy).
edge(ne,co).
edge(ne,ks).

edge(ks,ne).
edge(ks,co).


/* Question 1.2 */

% Colors: orange, yellow, red, blue 

color(wa,orange).
color(or,yellow).
color(ca,red).
color(id,red).
color(nv,orange).
color(az,yellow).
color(ut,blue).
color(mt,orange).
color(wy,yellow).
color(co,red).
color(nm,blue).
color(nd,red).
color(sd,blue).
color(ne,orange).
color(ks,orange). % should be yellow 

/* Question 1.3 */

population(wa,8).
population(or,4).
population(ca,40).
population(id,2).
population(nv,3).
population(az,7).
population(ut,3).
population(mt,1).
population(wy,1).
population(co,6).
population(nm,2).
population(nd,1).
population(sd,1).
population(ne,2).
population(ks,3).

/* Question 1.4 */

adjacent(X,Y):-
	edge(X,Y);
	edge(Y,X).

miscolor(S1,S2,Color1):-
	adjacent(S1,S2),
	color(S1,Color1),
	color(S2,Color1).

/* Question 1.5 */

totalpopulation([],0).

totalpopulation(Lst,Total):-
	Lst = [Head|Tail],
	Head = [_State, Population],
	totalpopulation(Tail, TT),
	Total is TT + Population.

/* Test Case */

q1:-
	miscolor(S1, S2, Color1),
	write(S1), write(' and '), write(S2),
	write(' have conflict color: '), write(Color1), nl,
	totalpopulation([[wa,8],[or,4],[ca,40],[id,2],[nv,3],[az,7],[ut,3],[mt,1],[wy,1],[co,6],[nm,2],[nd,1],[sd,1],[ne,2],[ks,3]], Total),
	write('Total = '),
	write(Total), nl.

/* Question 2.1 */

%  P: 0-9, M: 0-4, B: 0-6, O: 0-15, C: 0-5

pizza(P,M,B,O,C):-
	member(P,[0,1,2,3,4,5,6,7,8,9]),
	member(M,[0,1,2,3,4]),
	member(B,[0,1,2,3,4,5,6]),
	member(O,[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]),
	member(C,[0,1,2,3,4,5]),
	Total is P*5 + M*10 + B*7 + O*3 + C*8,
	Total =:= 45.

/* Question 2.2 */

q2:-
	pizza(2,1,2,1,1),
	pizza(1,M2,1,O2,C2),
	pizza(P3,M3,1,O3,1),
	write('M2 = '), write(M2),
	write(' O2 = '), write(O2),
	write(' C2 = '), write(C2), nl,
	write('P3 = '), write(P3),
	write(' M3 = '), write(M3),
	write(' O3 = '), write(O3),nl. 
