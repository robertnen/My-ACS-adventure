Ra = 1.6;
La = 1.96e-3;
J = 459e-7;
K = 0.065;

A = [-Ra/La -K/La; K/J 0];
B = [1/La  0; 0 -1/J];
C = [1 0; 0 1];
D = [0 0; 0 0];

mt = ss(A, B, C, D);
display(mt)

syms s t;

I = eye(size(A));

% phi(t)
phi_s = inv(s * I - A);
phi_t = ilaplace(phi_s, t);

[nums, dens] = ss2tf(A, B, C, D, 1);

Ts11 = tf(nums(1, :), dens);
Ts21 = tf(nums(2, :), dens);

[nums, dens] = ss2tf(A, B, C, D, 2);

Ts12 = tf(nums(1, :), dens);
Ts22 = tf(nums(2, :), dens);

Ts = [Ts11 Ts12; Ts21 Ts22];

[num11, den11] = tfdata(Ts11);
[num12, den12] = tfdata(Ts12);
[num21, den21] = tfdata(Ts21);
[num22, den22] = tfdata(Ts22);

num11 = cell2mat(num11);
num12 = cell2mat(num12);
num21 = cell2mat(num21);
num22 = cell2mat(num22);

den11 = cell2mat(den11);
den12 = cell2mat(den12);
den21 = cell2mat(den21);
den22 = cell2mat(den22);