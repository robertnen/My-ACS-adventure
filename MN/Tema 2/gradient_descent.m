function [Theta] = gradient_descent(FeatureMatrix, Y, n, m, alpha, iter)

  Theta = zeros(n, 1);

  for step = 1 : iter
      for j = 1 : n
        % calculez suma cu functia
        s = 0;
        for i = 1 : m
          s = s + (FeatureMatrix(i, :) * Theta - Y(i)) * FeatureMatrix(i, j);
        endfor
        s = s / m;
        Theta(j) = Theta(j) - alpha * s; % formez theta
      endfor
  endfor

  Theta = [0; Theta]; % adaug theta 0

endfunction
