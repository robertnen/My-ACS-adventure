function [X, y] = load_dataset(path)

    % verific daca exista fisierul
    if ~isfile(path)
      disp('Fisierul nu a putut fi deschis...');
      return;
    endif

    load(path);

endfunction
