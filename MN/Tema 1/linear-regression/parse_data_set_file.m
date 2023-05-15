function [Y, InitialMatrix] = parse_data_set_file(file_path)

    % verific daca exista fisierul
    [fid, errMes] = fopen(file_path, 'r');
    if fid == -1
        disp(errMes);
        exit;
    endif

    %citesc m si n
    A = textscan(fid, '%d', 2);

    aux = A{1, 1};
    m = aux(1, 1);
    n = aux(2, 1);

    %fac stringul de formatare
    format = '%d';

    % voi avea '%d %s %s %s ... %s' care e exact o linie din matrice
    for i = 1 : n
      format = [format ' %s'];
    endfor

    %citesc matricea
    A = textscan(fid, format);

    fclose(file_path);

    % Y primeste numerele de pe prima col, matricea initiala restul
    Y = A{1};

    % bag in InititalMatrix ce va contine, dar momentan nu e matrice m x n
    InitialMatrix = [{A{2 : (n + 1)}}];

    % l-am facut matrice
    InitialMatrix = cell2mat(InitialMatrix);

endfunction
