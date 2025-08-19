%* primul exercitiu
function fin = read_io_data(file_path)
    if exist(file_path, 'file') == 2
        fin = readtable(file_path);
    else
        error('File %s doesn''t exist!', file_path);
    end
end

function [t, v_in, m, om, ia] = get_columns(fin)
    if ~istable(fin)
        error("Corrupted table")
    end

    t = fin.timp;
    v_in = fin.v_in;
    m = fin.m;
    om = fin.omega;
    ia = fin.ia;
end

%* al doilea exercitiu
function [u0, us, y0, ys, tu0, ty0, ty63] = get_1st_order_elements(u, y, t)
    u0 = u(1);
    us = u(end);

    y0 = y(1);
    ys = y(end);

    tu0 = t(find(u ~= 0, 1, 'first'));
    ty0 = t(find(diff(y) ~= 0, 1, 'first'));

    y63 = 0.63 * ys;
    [~, idx] = min(abs(y - y63));

    ty63 = t(idx);
end

%* al treilea exercitiu
function [K, T, Td] = get_experimental_model(u0, us, y0, ys, tu0, ty0, ty63)
    K = (ys - y0) / (us - u0);
    T = ty63 - ty0;
    Td = ty0 - tu0;
end

%? al patrulea exercitiu
fin = read_io_data('date_identificare.xlsx');
[t, u, ~, y, ~] = get_columns(fin);

[u0, us, y0, ys, tu0, ty0, ty63] = get_1st_order_elements(u, y, t);
[K, T, Td] = get_experimental_model(u0, us, y0, ys, tu0, ty0, ty63);

s = tf('s');
H = K * exp(-Td*s) / (T*s + 1);

tsim = linspace(t(1), t(end), length(t));
u_sim = us * ones(size(tsim));

[y_estimat, t_estimat] = lsim(H, u_sim, tsim);

figure;
plot(t_estimat, y_estimat, 'LineWidth', 2);
hold on;
plot(t, y, 'o');
hold off;
legend('Estimat', 'Masurat');
xlabel('Timp (s)');
ylabel('Raspuns');
title('Raspunsul Sistemului Masurat vs. Estimat');