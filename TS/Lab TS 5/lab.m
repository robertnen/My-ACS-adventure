% ex 1
Ra = 1.6;
La = 1.96e-3;
J = 459e-7;
K = 0.065;

A = [-Ra/La -K/La; K/J 0];
B = [1/La  0; 0 -1/J];
C = [1 0; 0 1];
D = [0 0; 0 0];

h = 0.01;

syms t;
Ad = expm(A*h);
Bd = double(int( expm(A*t) *  B, t, 0, h));
Cd = C;
Dd = D;

display(Ad);
display(Bd);

% ex 2
[num1s, den1s] = ss2tf(A, B, C, D, 1);

num1s_1 = num1s(1, :);
num1s_2 = num1s(2, :);

H11s = tf(num1s_1, den1s);
H12s = tf(num1s_2, den1s);

H11z = c2d(H11s, h);
H12z = c2d(H12s, h);

[num1z, den1z] = tfdata(H11z, 'v');
[num2z, den2z] = tfdata(H12z, 'v');


[num2s, den2s] = ss2tf(A, B, C, D, 2);

num2s_1 = num2s(1, :);
num2s_2 = num2s(2, :);

H21s = tf(num2s_1, den2s);
H22s = tf(num2s_2, den2s);

H21z = c2d(H21s, h);
H22z = c2d(H22s, h);

[num12z, den12z] = tfdata(H21z, 'v');
[num22z, den22z] = tfdata(H22z, 'v');

display(H11z);