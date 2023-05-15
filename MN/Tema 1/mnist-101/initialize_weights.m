function [matrix] = initialize_weights(L_prev, L_next)

  eps = sqrt(6 / (L_prev + L_next)); % calculez epsilon

  % pentru ca nu merge pe checker pkg-ul statistics, voi improviza
  aux = floor(eps * 10000);

  % formez matricea cu valori intregi arbitrare
  randi([-aux, aux], L_next, L_prev + 1)
  matrix = randi([-aux, aux], L_next, L_prev + 1);
  matrix = matrix / 10000; % si le impart ca sa fie in intervalul [-eps; eps]

endfunction
