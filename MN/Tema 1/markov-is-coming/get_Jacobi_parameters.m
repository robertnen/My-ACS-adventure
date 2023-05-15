function [G, c] = get_Jacobi_parameters(Link)

    [n, ~] = size(Link);
    % iau din Link exact cat am nevoie
    n = n - 2;
    G = Link(1 : n, 1 : n);
    c = Link(1 : n, n + 1);
endfunction
