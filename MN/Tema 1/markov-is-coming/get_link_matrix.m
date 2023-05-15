function [Link] = get_link_matrix(Labyrinth)

    % nu am vazut ca nu as avea voie sa folosesc o functie facuta deja
    Labyrinth = get_adjacency_matrix(Labyrinth);

    [m, n] = size(Labyrinth);

    for i = 1 : m
        % impart prin numarul de elemente nenule
        [chance, ~] = size(nonzeros(Labyrinth(i, 1 : n)));
            Labyrinth(i, 1 : n) = Labyrinth(i, 1 : n) / chance;
    endfor
    Link = Labyrinth; % returnez matricea ceruta
endfunction
