function [Error] = lasso_regression_cost_function(Theta, Y, FeMatrix, lambda)

  [m, n] = size(FeMatrix);
  Error = 0;

  % sterg primul element ca sa pot sa inmultesc vectorii
  Theta(1) = [];

  for i = 1 : m % fac suma cu acea functie
    Error = Error + (FeMatrix(i, :) * Theta - Y(i)) .^ 2;
  endfor

  Error = Error / m; % impartirea
  Error = Error + lambda * norm(Theta, 1); % adaug restul

endfunction
