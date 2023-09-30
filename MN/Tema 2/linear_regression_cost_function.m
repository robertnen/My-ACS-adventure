function [Error] = linear_regression_cost_function(Theta, Y, FeatureMatrix)

  [m, n] = size(FeatureMatrix);
  Error = 0;

  % sterg primul element ca sa pot sa inmultesc vectorii
  Theta(1) = [];

  for i = 1 : m % aplic formula din enunt fara sa impart pe 2 * m
    Error = Error + (FeatureMatrix(i, :) * Theta - Y(i)) .^ 2;
  endfor

  % acum impart
  Error = Error / (2 * m);

  endfunction
