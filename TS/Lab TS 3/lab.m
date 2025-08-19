A = [-1 0 0; -1 -2 -101; 1 1 0];
b = [0; 1; 0];
c = [1 0 101];
D = 0;
x0 = [1; 0; -1];

syms s t;

I = eye(size(A));

% phi(t)
phi_s = inv(s * I - A);
phi_t = ilaplace(phi_s, t);

% disp("phi(t):");
% disp(phi_t);

% in regim liber
xl_t = phi_t * x0;
yl_t = c * xl_t;

disp("xl(t):");
disp(xl_t);

% disp("yl(t):");
% disp(yl_t);

% functia de transfer
H_s = c * inv(s * I - A) * b;

disp("H(s):");
disp(H_s);

[sim_num , sim_den] = numden(H_s);
num_coeffs = coeffs(sim_num, 'All');
num_den = coeffs(sim_den, 'All');

disp(num_coeffs);
disp(num_den);

% regim fortat
l_t = heaviside(t);
u_t = -2 * l_t;

Yf_s = H_s * laplace(u_t, t, s);
yf_t = ilaplace(Yf_s, s, t);

disp("yf(t):");
disp(yf_t);

figure;
plot(out.simout1 + 1, 'b'); hold on;
plot(out.simout2 + 2, 'g');
plot(out.simout3, 'r');
grid on;

legend('1', '2', '3');