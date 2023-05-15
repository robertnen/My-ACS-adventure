function [path] = heuristic_greedy(start_position, probabilities, Adj)

    % prealoc si adaug elemente in path si isVisited
    [n, ~] = size(Adj);
    n = n - 2;
    path = zeros(1, n);
    len = 1;
    isVisited = zeros(n, n);

    path(len) = start_position;
    isVisited(start_position) = 1;

    while len ~= 0
        pos = path(1, len);

        % verific daca am castigat
        if(Adj(pos, n + 1) == 1)
            path(len + 1) = n + 1;
            path = nonzeros(path);
            return; % da
        endif

        maxChance = -1; % ca sa nu iau caz separat
        newPos = 0; % tine minte pozitia unde e cea mai mare sansa
        for i = 1 : n
            if(Adj(pos, i) == 1 && ~isVisited(pos, i))
                if(maxChance < probabilities(i))
                    maxChance = probabilities(i);
                    newPos = i; % am gasit unde trebuie sa merg
                endif
            endif
        endfor

        if newPos % am o zona nevizitata
            len = len + 1;
            path(len) = newPos;
            isVisited(pos, newPos) = 1;
            isVisited(newPos, pos) = 1;
        else
            len = len - 1; % ma intorc
        endif
    endwhile

    % path poate contine la final zerouri asa ca scap de ele
    path = nonzeros(path)';
endfunction
