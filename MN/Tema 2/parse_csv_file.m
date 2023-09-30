function [Y, InitialMatrix] = parse_csv_file(file_path)

    % verific daca exista fisierul
    [fid, errMes] = fopen(file_path, 'r');
    if fid == -1
        disp(errMes);
        exit;
    endif

    % citesc textul
    Aux = textread(file_path, '%s', 'delimiter', ',');

    % scap de numele coloanelor
    Aux(1 : 13) = [];

    [n, ~] = size(Aux);

    % adaug primul numar ca sa maresc vectorul
    Y = str2double(Aux{1, 1});

    % formez vectorul Y
    for i = 14 : 13 : n % din 13 in 13 elemente se gasesc
      Y = [Y str2double(Aux{i, 1})];
    endfor

    Y = Y'; % il fac vector coloana
    Aux(1 : 13 : n) = []; % scot Y din Aux

    % formez matricea
    [n, ~] = size(Aux);
    InitialMatrix = reshape(Aux, 12, n / 12);
    InitialMatrix = InitialMatrix'; % am citit-o transpuns

endfunction
