schedule(ankara, rize, 5).
schedule(ankara, izmir, 6).
schedule(ankara, istanbul, 1).
schedule(ankara, van, 4).
schedule(ankara, diyarbakir, 8).


schedule(van, ankara, 4).
schedule(van, gaziantep, 3).


schedule(diyarbakir, antalya, 4).
schedule(diyarbakir, ankara, 8).


schedule(gaziantep, van, 3).


schedule(antalya, izmir, 2).
schedule(antalya, erzincan, 3).
schedule(antalya, diyarbakir, 4).


schedule(canakkale, erzincan, 6).

schedule(erzincan, canakkale, 6).
schedule(erzincan, antalya, 3).


schedule(istanbul, izmir, 2).
schedule(istanbul, ankara, 1).
schedule(istanbul, rize, 4).



schedule(rize, ankara, 5).
schedule(rize, istanbul, 4).

schedule(izmir, istanbul, 2).
schedule(izmir, antalya, 2).
schedule(izmir, ankara, 6).



%rules 

run(X,Y,C,PATH,Visited) :-
    var(Y),
    schedule(X,Y,C).    

run(X,Y,C,PATH,Visited) :-
    nonvar(Y),
    \+ member(Y,Visited),
    append(Visited,[Y],Temp),
    schedule(X,Y,C),
    
    PATH = [X,Y].


run(X,Y,C,PATH, Visited) :-
    nonvar(Y),
    schedule(X,Z,C1),
    \+ member(Z,Visited),
    append(Visited,[Z],Temp),
    run(Z,Y,C2,P,Temp),
    nl,
    \+ member(Z,Visited),
    C is C1 + C2,
    PATH = [X | P].

%  connection(canakkale, diyarbakir, C,Path).

%  connection(canakkale, Y, C).

/*
connection(X,Y,_):-
    \+ schedule(X,Y,_),
    \+ schedule(Y,X,_).
*/

    
    
connection(X,Y,C):-
    Visited = [X],
    run(X,Y,C,PATH,Visited),
    (var(PATH) ->
        true;
        write(PATH) 
    ).





