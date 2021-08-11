get_last([F],E):-
	E = F.
get_last([F,S],E):-
    _X = [F|S],
    E = S.
get_last(L,E):-
    L = [_Head|Tail],
    get_last(Tail,E).

remove_last([_X], []).
remove_last(L, R) :-
    L = [Head|Tail],
    remove_last(Tail, RT),
    append([Head], RT, R).

split(_,[],[],[]).
split(Pivot,[X|T],[X|Le],Gt):-
    X =< Pivot,split(Pivot,T,Le,Gt).
split(Pivot,[X|T],Le,[X|Gt]):-
    X > Pivot,
    split(Pivot,T,Le,Gt).
    
qsort([],[]).
qsort(L, Sorted):-
    get_last(L, Pivot),
    remove_last(L, NewL),
    split(Pivot,NewL,L1,L2),
    qsort(L1,Sorted1),
    qsort(L2,Sorted2),
    append(Sorted1,[Pivot|Sorted2],Sorted).
    
    
    