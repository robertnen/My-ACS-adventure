function [decoded_path] = decoded_path(path, lines, cols)

  path = nonzeros(path)'; % scap de elementele care nu ma ajuta
  [~, len] = size(path);

  % prealoc cu exact cate elemente am nevoie
  decoded_path = zeros(len - 1, 2);

  for i = 1 : len - 1
      tmp = path(i); % scot inceputul cozii

      % formez perechi
      if ~mod(tmp, cols) % inseamna ca sunt pe marginea din dreapta
        decoded_path(i, 1) = tmp / cols;
        decoded_path(i, 2) = cols;
      else % nu ma aflu pe marginea din dreapta, deci pot aplica formula:
        decoded_path(i, 1) = (tmp - mod(tmp, cols)) / cols + 1;
        decoded_path(i, 2) = mod(tmp, cols);
      end
  endfor
endfunction
