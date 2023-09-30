function [Error] = ridge_regression_cost_function(Theta, Y, FeatureMatrix, lambda)

  [m, n] = size(FeatureMatrix);
  Error = 0;

  % sterg primul element ca sa pot sa inmultesc vectorii
  Theta(1) = [];

  for i = 1 : m % fac suma cu functia
    Error = Error + (FeatureMatrix(i, :) * Theta - Y(i)) .^ 2;
  endfor

  Error = Error / (2 * m); % impartirea
  Error = Error + lambda * norm(Theta) .^ 2; % adaug restul
endfunction