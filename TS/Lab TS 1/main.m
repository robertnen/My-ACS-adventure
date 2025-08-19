function y = generate_voltage(t, f, phi)
    y = 230 * sqrt(2) * sin(2 * pi * f * t + phi);
end

function [y, t] = voltage_scenario(t_start, t_end, n, f, phi)
    t = linspace(t_start, t_end, n);
    y = generate_voltage(t, f, phi);
end

function plot_signal(t, y, description)
    figure;
    plot(t, y, 'b', 'LineWidth', 1.5);
    grid on;
    title(description);
    xlabel('Timp [s]');
    ylabel('Tensiune [V]');
    legend('Tensiune de alimentare');
end

function simulate_voltage()
    [y, t] = voltage_scenario(0, 0.04, 100, 50, 0);
    plot_signal(t, y, "o descriere");
end

simulate_voltage();

% final exercitiu 2


function v = generate_sim_voltage()
    syms t;
    v = 230 * sqrt(2) * sin(2 * pi * 50 * t);
end

function p = generate_sim_power(R)
    v = generate_sim_voltage();
    p = v ^ 2 / R;
end

function E = calculate_energy(R, T)
    p = generate_sim_power(R);
    E = double(int(p, 0, T));
end

calculate_energy(10, 0.02)

% final exercitiu 3


function [V, t] = generate_voltage_matrix(t_start, t_stop, n)
    t = linspace(t_start, t_stop, n);
    V = [generate_voltage(t, 50, [0; -2 * pi / 3; -4 * pi / 3])];
end

function analyze_voltage_matrix(V)
    [m, n] = size(V);
    fprintf('m x n: %d x %d\n', m, n);
    for i = 1:3
        max_a = max(abs(V(i, :)));
        mean_v = mean(V(i, :));
        fprintf('Faza %d - Amplitudine max: %.2f V, Medie: %.2f V\n', i, max_a, mean_v);
    end
end

[V, t] = generate_voltage_matrix(0, 0.1, 100);
analyze_voltage_matrix(V);

% final exercitiu 4


function plot_voltage_matrix(t_start, t_stop, n)
    [V, t] = generate_voltage_matrix(t_start, t_stop, n);

    plot_signal(t,  V(1, :), "1");
    plot_signal(t,  V(2, :), "2");
    plot_signal(t,  V(3, :), "3");

    figure;
    plot(t, V(1, :), 'r', 'LineWidth', 1.5); hold on;
    plot(t, V(2, :), 'g', 'LineWidth', 1.5);
    plot(t, V(3, :), 'b', 'LineWidth', 1.5);
    grid on;
    title('Tensiuni trifazate');
    xlabel('Timp [s]');
    ylabel('Tensiune [V]');
    legend('1', '2', '3');
end

plot_voltage_matrix(0, 0.1, 100);

% final exercitiu 5
