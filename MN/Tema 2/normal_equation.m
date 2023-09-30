function [Theta] = normal_equation(FeatureMatrix, Y, tol, iter)

  % ca sa aplic metoda, imi trebuie o matrice patratica
  A = FeatureMatrix' * FeatureMatrix;
  b = FeatureMatrix' * Y;

  [n, ~] = size(b);

  % verific daca matricea e pozitiv definita
  % verific daca e simetrica
  if ~issymmetric(A)
    Theta = zeros(n + 1, 1);
    return; % nu
  endif

  % verific daca valorile pr. sunt strict pozitive
  Eigenvalues = eig(A);
  if ~all(Eigenvalues > 0)
    Theta = zeros(n + 1, 1);
    return; % nu
  end

  Theta = zeros(n, 1); % momentan fac fara theta 0

  % fac pseudocodul din enunt, dar putin modificat
  r = b - A * Theta;
  v = r;
  tol = tol .^ 2;
  i = 1;
  while(i <= iter && r' * r > tol)
    t = (r' * r) / (v' * A * v);
    Theta = Theta + t * v;
    u = r;
    r = r - t * A * v;
    s = (r' * r) / (u' * u);
    v = r + s * v;
    i = i + 1;
  endwhile

  % adaug theta 0
  Theta = [0; Theta];
endfunction
