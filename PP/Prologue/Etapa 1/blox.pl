:- dynamic detailed_mode_disabled/0.
:- dynamic debug_moves/0.
:- ensure_loaded('files.pl').


% % empty_state/1
% % empty_state(-SNew)
% % Construiește o stare goală (fără nicio informație), care va fi dată
% % primului apel set/4
empty_state(SNew) :- SNew = [].


% % set_tile/3
% % set_tile(+S, +Pos, -SNew)
% % Construiește starea SNew, care conține aceleași informații ca și S
% % și în plus faptul că la poziția Pos se află o pătrățică normală.
set_tile(S, Pos, SNew) :- SNew = [tile(Pos) | S].


% % set_blank/3
% % set_blank(+S, +Pos, -SNew)
% % Construiește starea SNew, care conține aceleași informații ca și S.
% % Va fi apelat de tester doar pentru pozițiile fără pătrățele de la
% % coordonate unde pentru același x și y mai mare, sau pentru același y
% % și x mai mare, există pătrățele. Puteți să nu faceți nimic în acest
% % predicat - depinde de cum vă reprezentați intern starea.
set_blank(S, Pos, SNew) :- SNew = [blank(Pos) | S].


% % set_target/3
% % set_target(+S, +Pos, -SNew)
% % Construiește starea SNew, care conține aceleași informații ca și S
% % și în plus faptul că la poziția Pos se află gaura (scopul).
set_target(S, Pos, SNew) :- SNew = [target(Pos) | S].


% % set_fragile/3
% % set_fragile(+S, +Pos, -SNew)
% % Construiește starea SNew, care conține aceleași informații ca și S
% % și în plus faptul că la poziția Pos se o pătrățică fragilă, pe care
% % blocul nu poate sta în picioare.
set_fragile(S, Pos, SNew) :- SNew = [fragile(Pos) | S].


% % set_block_initial/3
% % set_block_initial(+S, +Pos, -SNew)
% % Construiește starea SNew, care conține aceleași informații ca și S
% % și în plus faptul că la poziția Pos se află inițial blocul, plasat în
% % picioare.
set_block_initial(S, Pos, SNew) :- SNew = [block(Pos) | S].


% % get_b_pos/2
% % get_b_pos(+S, -BlockPos)
% % Obtine pozitia sau pozitiile blocului (în funcție de dacă blocul este
% % în picioare sau culcat, ca (X, Y) sau ca [(X1, Y1), (X2, Y2)]
get_b_pos([], []).
get_b_pos([block(Pos) | _], Pos).
get_b_pos([_ | Oth], BlockPos) :- get_b_pos(Oth, BlockPos).


% % get_bounds/5
% % get_bounds(+S, -Xmin, -Xmax, -Ymin, -Ymax).
% % Obtine coordonatele limită de pe hartă la care exită celule.
find_bound(S, Xs, Ys) :-
    findall(X, member(tile((X, _)), S), XTile),
    findall(X, member(fragile((X, _)), S), XFrag),
    findall(X, member(target((X, _)), S), XTarget),

    findall(Y, member(tile((_, Y)), S), YTile),
    findall(Y, member(fragile((_, Y)), S), YFrag),
    findall(Y, member(target((_, Y)), S), YTarget),

    append([XTile, XFrag, XTarget], Xs),
    append([YTile, YFrag, YTarget], Ys).

get_bounds(S, Xmin, Xmax, Ymin, Ymax) :-
    find_bound(S, Xlist, Ylist),
    min_list(Xlist, Xmin), max_list(Xlist, Xmax),
    min_list(Ylist, Ymin), max_list(Ylist, Ymax).


% % get_cell/3
% % get_cell(S, Pos, Type).
% % Leagă Type la tipul pătrățelei de la poziția Pos. Type trebuie legat
% % la:
% % tile - pentru o pătrățică obișnuită.
% % fragile - pentru o pătrățică fragilă.
% % target - pentru scop (gaura).
% % oswitch - pentru switch de tip o.
% % xswitch - pentru switch de tip x.
% %
% % Dacă la poziția respectivă nu se află nimic, sau este în afara
% % limitelor date de get_bounds, predicatul întoarce false.
get_cell(S, Pos, Type) :-
    member(tile(Pos), S),    !, Type = tile;
    member(fragile(Pos), S), !, Type = fragile;
    member(target(Pos), S),  !, Type = target;
    member(oswitch(Pos), S), !, Type = oswitch;
    member(xswitch(Pos), S), !, Type = xswitch.

% % move/3
% % move(S, Move, SNext)
% % Calculează în SNext starea care rezultă din realizarea mutării Move în
% % starea S.
% % Mutarea este una dintre d, u, l, r.
% % Întoarce false dacă mutarea duce la căderea blocului în vid (nu dacă
% % blocul a ajuns la scop).

move(S, Move, SNext) :- get_b_pos(S, (X, Y)),
                        %* find direction
                        (Move = d -> X1 is X, Y1 is Y + 1;
                         Move = u -> X1 is X, Y1 is Y - 1;
                         Move = l -> X1 is X - 1, Y1 is Y;
                         Move = r -> X1 is X + 1, Y1 is Y),

                        get_bounds(S, Xmin, Xmax, Ymin, Ymax),

                        %* check if we are inside
                        Xmin =< X1, X1 =< Xmax,
                        Ymin =< Y1, Y1 =< Ymax,

                        delete(S, block(_, _), S1),
                        SNext = [block((X1, Y1), u) | S1].

% % is_final/1
% % is_final(S)
% % Întoarce adevărat dacă în starea S blocul este în picioare, pe aceeași
% % poziție cu gaura (scopul).
is_final(S) :- member(BlockPos, S).

% % pentru etapa 2
% % set_switch(+S, +Pos, +Switch, +Func, +Positions, SOut)
% % Switch: o sau x
% % Func: switch, uponly sau dnonly
% % Position: pozitiile podului
set_switch(S, Pos, Switch, Func, Positions, SOut) :- SOut = [switch(Pos, Switch, Func, Positions) | S].





