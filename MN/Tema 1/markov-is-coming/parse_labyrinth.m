function [Labyrinth] = parse_labyrinth(file_path)

    % verific daca exista fisierul
    [fid, errMes] = fopen(file_path, 'r');
    if fid == -1
        disp(errMes);
        exit;
    endif

    % citesc fisierul si bag elementele intr-un vector cu size = [m * n + 2, 1]
    Labyrinth = textread(file_path, '%d', 'delimiter', ' ');

    % citirea face ca numarul de coloane sa fie primul element
    n = Labyrinth(1);

    % numarul de linii
    m = Labyrinth(2);

    % formez matricea
    Labyrinth = reshape(Labyrinth(3 : m * n + 2, 1), m, n)';
    fclose(file_path);

endfunction
