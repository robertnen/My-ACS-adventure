function [x, err, steps] = perform_iterative(G, c, x0, tol, max_steps)
    % initializare
    y = x0;
    x = x0;
    for steps = 1 : max_steps
        y = G * x + c;
        % verific daca se indeplineste conditia de oprire
        err = norm(y - x);
        if err < tol
            return; % am gasit o soltuie care imi place
        endif
        x = y;
    endfor
endfunction
