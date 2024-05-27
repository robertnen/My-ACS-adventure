
:- ensure_loaded('files.pl').

editall :- forall(member(File, [
                             blox, util, testing, files, levels, checker, points1, points2
                         ]), edit(File)).


% lista de poosibile direcții
directions([u,d,l,r]).

% neighbor(+Pos, +Direction, -NeighborPos)
% Leagă NeighborPos la poziția vecină cu Pos, aflată către direcția Dir
% e.g. Pentru Pos = (5, 4) și Direction = d
% va lega NeighborPos la (5, 5)
neighbor((X, Y), Dir, (XN, YN)) :- delta(Dir, DX, DY), XN is X + DX, YN is Y + DY.
% neighbor2(+Pos, +Direction, -NextNeighborPos)
% Leagă NextNeighborPos la poziția la distanță de 2 de Pos, aflată către
% direcția Dir.
% e.g. Pentru Pos = (5, 4) și Direction = d va lega
% NeighborPos la (5, 6)
neighbor2((X, Y), Dir, (XN, YN)) :- delta(Dir, DX, DY),
    XN is X + 2 * DX, YN is Y + 2 * DY.

delta(Dir, DX, DY) :- member((Dir, DX, DY),
                             [(u, 0, -1), (d, 0, 1), (r, 1, 0), (l, -1, 0)]).




% Afișează o stare, folosind predicatele
% get_bounds/5, get_b_pos/2, și get_cell/3
print_state(S) :-
    get_bounds(S, Xmin, Xmax, Ymin, Ymax),
    get_b_pos(S, BlockPos),
    findall(Row, (
        between(Ymin, Ymax, Y),
        findall(Cell, (
            between(Xmin, Xmax, X),
            cell_to_string(S, BlockPos, (X, Y), Cell)
        ), Cols),
        atomics_to_string(Cols, '', Row)
    ), Rows),
    atomics_to_string(Rows, '\n', String),
    writeln(String).

cell_to_string(_, Pos, Pos, 'B') :- !.
cell_to_string(_, BlockPos, Pos, 'b') :- member(Pos, BlockPos), !.
cell_to_string(S, _, Pos, CellPrint) :- get_cell(S, Pos, Cell), !, cell_print(Cell, CellPrint).
cell_to_string(_, _, _, ' ').

% cell_print(?Type, ?Print)
% Realizează corespondența între tipul unei celule și caracterul afișat.
cell_print(target, $).
cell_print(fragile, ^).
cell_print(tile, +).
cell_print(oswitch, o).
cell_print(xswitch, x).
