:- dynamic detailed_mode_disabled/0.
:- dynamic debug_moves/0.
:- ensure_loaded('files.pl').


% empty_state/1
% empty_state(-SNew)
% Construiește o stare goală (fără nicio informație), care va fi dată
% primului apel set/4
empty_state(_) :- false.
empty_state(([], [])).

%%%%%%
% coordonata (0, 0) este coltul din stanga/sus (chiar dacă nu există un
% tile acolo)

% set_tile/3
% set_tile(+S, +Pos, -SNew)
% Construiește starea SNew, care conține aceleași informații ca și S
% și în plus faptul că la poziția Pos se află o pătrățică normală.
set_tile(_, _, _) :- false.
set_tile((S, O), P, ([(P, tile) | S], O)).

% set_blank/3
% set_blank(+S, +Pos, -SNew)
% Construiește starea SNew, care conține aceleași informații ca și S.
% Va fi apelat de tester doar pentru pozițiile fără pătrățele de la
% coordonate unde pentru același x și y mai mare, sau pentru același y
% și x mai mare, există pătrățele. Puteți să nu faceți nimic în acest
% predicat - depinde de cum vă reprezentați intern starea.
set_blank(_, _, _) :- false.
set_blank(S, _, S).

% set_target/3
% set_target(+S, +Pos, -SNew)
% Construiește starea SNew, care conține aceleași informații ca și S
% și în plus faptul că la poziția Pos se află gaura (scopul).
set_target(_, _, _) :- false.
set_target((S, O), P, ([(P, target) | S], O)).

% set_fragile/3
% set_fragile(+S, +Pos, -SNew)
% Construiește starea SNew, care conține aceleași informații ca și S
% și în plus faptul că la poziția Pos se o pătrățică fragilă, pe care
% blocul nu poate sta în picioare.
set_fragile(_, _, _) :- false.
set_fragile((S, O), P, ([(P, fragile) | S], O)).

% set_block_initial/3
% set_block_initial(+S, +Pos, -SNew)
% Construiește starea SNew, care conține aceleași informații ca și S
% și în plus faptul că la poziția Pos se află inițial blocul, plasat în
% picioare.
set_block_initial(_, _, _) :- false.
set_block_initial((S, O), P, (S1, [(block, [P]) | O])) :- set_tile((S, O), P, (S1, _)).


% get_b_pos/2
% get_b_pos(+S, -BlockPos)
% Obtine pozitia sau pozitiile blocului (în funcție de dacă blocul este
% în picioare sau culcat, ca (X, Y) sau ca [(X1, Y1), (X2, Y2)]
get_b_pos(_, _) :- false.
get_b_pos((_, O), P1) :- member((block, P), O), (P = [(X, Y)], P1 = (X, Y), !; P1 = P).

% get_bounds/5
% get_bounds(+S, -Xmin, -Xmax, -Ymin, -Ymax).
% Obtine coordonatele limită de pe hartă la care exită celule.
get_bounds(_, _, _, _, _) :- false.
get_bounds((S, _), Xm, XM, Ym, YM) :-
    findall(X, member(((X, _), _), S), Xs), min_list(Xs, Xm), max_list(Xs, XM),
    findall(Y, member(((_, Y), _), S), Ys), min_list(Ys, Ym), max_list(Ys, YM).


% get_cell/3
% get_cell(S, Pos, Type).
% Leagă Type la tipul pătrățelei de la poziția Pos. Type trebuie legat
% la:
% tile - pentru o pătrățică obișnuită.
% fragile - pentru o pătrățică fragilă.
% target - pentru scop (gaura).
% oswitch - pentru switch de tip o.
% xswitch - pentru switch de tip x.
%
% Dacă la poziția respectivă nu se află nimic, sau este în afara
% limitelor date de get_bounds, predicatul întoarce false.
get_cell(_S, (_X, _Y), _What) :- false.
get_cell((S, _), Pos, T) :- member((Pos, T), S).

% move/3
% move(S, Move, SNext)
% Calculează în SNext starea care rezultă din realizarea mutării Move în
% starea S.
% Mutarea este una dintre d, u, l, r.
% Întoarce false dacă mutarea duce la căderea blocului în vid (nu dacă
% blocul a ajuns la scop).
move(_, _, _) :- false.
move(S, Move, S1) :- S = (Board, A),
    % block is up
    member((block, [P]), A), !,
    neighbor(P, Move, P1),
    neighbor2(P, Move, P2),
    get_cell(S, P1, _),
    get_cell(S, P2, _),
    S1 = (Board, [(block, [P1, P2])]).
move(S, Move, S1) :- S = (Board, A),
    % block is laying, move to standing
    member((block, [P1, P2]), A),
    member(Pivot, [P1, P2]), member(Other, [P1, P2]),
    neighbor(Other, Move, Pivot), !,
    neighbor(Pivot, Move, P),
    get_cell(S, P, T), T \= fragile,
    S1 = (Board, [(block, [P])]).
move(S, Move, S1) :- S = (Board, A),
    % block is laying, move to laying
    member((block, [P1, P2]), A),
    neighbor(P1, Move, P1A),
    neighbor(P2, Move, P2A),
    get_cell(S, P1A, _), get_cell(S, P2A, _),
    S1 = (Board, [(block, [P1A, P2A])]).

% is_final/1
% is_final(S)
% Întoarce adevărat dacă în starea S blocul este în picioare, pe aceeași
% poziție cu gaura (scopul).
is_final(_) :- false.
is_final(S) :-
    get_b_pos(S, (X, Y)),
    get_cell(S, (X, Y), target).

%%%%%%%%%% Etapa 2

%% TODO
% set_switch/6
% set_switch(+S, +Pos, +Switch, +Func, +Positions, -SNew)
% Leagă starea SNew la o stare cu aceleași informații ca și S, și în
% plus un switch la poziția Pos, cu parametrii dați.
%
% Switch: oswitch sau xswitch.
% Func: switch, uponly sau dnonly.
% Positions: pozițiile podului.
set_switch((S, O), Pos, Switch, Func, Positions, SNew) :-
    New = (Pos, Switch, Func, Positions),
    SNew = ([New | S], O).

%% TODO
% solve/2
% solve(+S, -Moves)z
% Solve găsește o soluție pentru problema din starea S. Soluția este
% reprezentată ca secvența de mutări Moves.
%
% Pentru a fi soluție, mutările din Moves trebuie să ducă blocul în
% picioare pe poziția scop (target).
solve(_, _) :- false.






