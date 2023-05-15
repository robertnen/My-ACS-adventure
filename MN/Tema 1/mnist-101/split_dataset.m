function [X_train, y_train, X_test, y_test] = split_dataset(X, y, percent)

  [m, n] = size(X);

  % formez permutari
  permRow = randperm(n);
  permCol = randperm(m);

  % amestec matricea pe linii si coloane
  Aux = X(permRow, :);
  Aux = Aux(:, permCol);

  % aflu numarul de limii care trebuiesc scoase
  t = m * percent;

  % formez seturile X
  X_train = X([1 : t], :);
  X_test = X([t + 1 : m], :);

  % fac acelasi lucru si la Y
  Aux = y(permRow, :);
  y_train = y([1 : t], 1);
  y_test = y([t + 1 : m], 1);

endfunction
