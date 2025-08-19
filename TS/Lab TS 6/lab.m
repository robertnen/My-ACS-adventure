Ra = 1.6;     % rezistenta rotorului
La = 1.96e-3; % inductanta rotorului
J  = 459e-7;  % inertia rotorului
K  = 0.065;   % constanta motorului

A = [-Ra/La, -K/La; K/J,    0];
B = [1/La,  0; 0, -1/J];
C = [1, 0; 0, 1];
D = [0, 0; 0, 0];

ts = 0.001;

syms t;
Ad = double(expm(A*ts));
Bd = double(int(expm(A*t) * B, t, 0, ts));
Cd = C;
Dd = D;

sys_disc = ss(Ad, Bd, Cd, Dd, ts);

[num, den] = tfdata(sys_disc);

for i = 1:numel(num)
    Hz = tf(num{i}, den{i}, ts);
end

t = 0:ts:1;
u = [ones(size(t)); ones(size(t))];

y = lsim(sys_disc, u, t);

figure;
plot(t, y(:,1), 'r', 'LineWidth', 2); hold on;
plot(t, y(:,2), 'b', 'LineWidth', 2);
xlabel('Timp [s]');
ylabel('Răspunsul sistemului');
legend('Curent [A]', 'Viteză [rad/s]');
title('Răspunsul forțat al motorului de curent continuu discretizat');
grid on;
