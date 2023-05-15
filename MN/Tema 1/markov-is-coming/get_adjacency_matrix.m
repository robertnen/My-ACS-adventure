function [Adj] = get_adjacency_matrix(Labyrinth)

    [m, n] = size(Labyrinth);

    A = Labyrinth; % ca sa fie mai usor de urmarit
    Adj = zeros(m * n, m * n + 2); % se adauga starile win / lose

    % merg prin labirint si verific drumurile
    for i = 1 : m
        for j = 1 : n
            % verific nordul
            if(i > 1 && ~bitand(A(i, j), 8)) % 8 = 1000
                Adj((i - 1) * n + j, (i - 2) * n + j) = 1;
            endif

            % verific sudul
            if(i < m && ~bitand(A(i, j), 4)) % 4 = 0100
                Adj((i - 1) * n + j, i * n + j) = 1;
            endif

            % verific estul
            if(j < n && ~bitand(A(i, j), 2)) % 2 = 0010
                aux = (i - 1) * n + j; % pentru nu a calcula de 2 ori
                Adj(aux, aux + 1) = 1;
            endif

            % verific vestul
            if(j > 1 && ~bitand(A(i, j), 1)) % 1 = 0001
                aux = (i - 1) * n + j; % pentru nu a calcula de 2 ori
                Adj(aux, aux - 1) = 1;
            endif
        endfor
    endfor

    % ca sa nu calculez de multe ori
    aux = m * n;

    % verific daca castig
    Adj(aux + 1, aux + 1) = 1; % win <=> win
    for j = 1 : n % ma uit in sus si in jos
        if ~bitand(A(1, j), 8)      % pot sa ies prin nord
            Adj(j, aux + 1) = 1;
        endif

        if ~bitand(A(m, j), 4)      % pot sa ies prin sud
            Adj((m - 1) * n + j, aux + 1) = 1;
        endif
    endfor

    % verific daca pierd
    Adj(aux + 2, aux + 2) = 1; % lose <=> lose
    for i = 1 : m % ma uit in sus si in jos
        if ~bitand(A(i, 1), 1)      % pot sa ies prin vest
            Adj((i - 1) * n + 1, aux + 2) = 1;
        endif

        if ~bitand(A(i, n), 2)      % pot sa ies prin est
            Adj(i * n, aux + 2) = 1;
        endif
    endfor
endfunction
