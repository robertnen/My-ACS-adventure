% A vectorized function for the sigmoid calculation.
% You can use this function in your implementations.

function [y] = sigmoid(x)
  y = 1 ./ (1 + e .^ (-x));
endfunction
