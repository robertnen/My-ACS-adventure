function [FeatureMatrix] = prepare_for_regression(InitialMatrix)

  [n, m] = size(InitialMatrix);

  for i = 1 : n
    % iau fiecare linie si o modific
    aux = InitialMatrix(i, 1 : m);

    % inlocuiesc stringurile cu alte stringuri
    aux = strrep(aux, 'yes', '1');
    aux = strrep(aux, 'no', '0');
    aux = strrep(aux, 'semi-furnished', '1 0');
    aux = strrep(aux, 'unfurnished', '0 1');
    aux = strrep(aux, 'furnished', '0 0');

    % prealoc
    tmp = 0;

    for j = 1 : m
      if ~isnan(str2double(aux(j))) % verific daca stringul e un numar
        tmp = [tmp str2double(aux(j))];
      else % daca nu e, inseamna ca am ceva de forma '%d %d' si adaug
        tmp = [tmp str2double(aux{j}(1)) str2double(aux{j}(3))];
      endif
    endfor

    % scot ce am pus la inceput
    tmp(1) = [];

    if i == 1 % nu am initializat matricea pana acum
      FeatureMatrix = tmp;
    else % adaug o linie noua
      FeatureMatrix = [FeatureMatrix; tmp];
    endif
  endfor
endfunction