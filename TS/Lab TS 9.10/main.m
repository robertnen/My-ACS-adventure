function F = mono_alocare(A, B, L)
    if rank(ctrb(A, B)) <  size(A, 1)
        error("(A, B) nu e controlabila")
    end

    R = ctrb(A, B);

    en = zeros(1, size(A, 1));
    en(end) = 1;

    q = en * inv(R);

    v = (A - L(1) * eye(size(A, 1))) * (A - L(2) * eye(size(A, 1))) * (A - L(3) * eye(size(A, 1)));

    F = -q * v;
end

function F = alocare(A, B, L)
    if rank(ctrb(A, B)) <  size(A, 1)
        error("(A, B) nu e controlabila")
    end

    n = size(A, 1);
    m = size(B, 2);

    flag = false;

    while ~flag
        g = randn(m, 1);
        f0 = randn(m, n);

        As = A + B * f0;
        bs = B * g;

        R = ctrb(As, bs);

        if rank(R) == n
            flag = true;
        end
    end

    qT = inv(R);
    qT = qT(end, :);

    v = (As - L(1) * eye(size(A, 1))) * (As - L(2) * eye(size(A, 1))) * (As - L(3) * eye(size(A, 1)));

    fT = -qT * v;

    F = f0 + g * fT;
end

function [Ac, Bc, Fc, Gc] = CDS(A, B, C, Ld, Le)
    if rank(ctrb(A, B)) < size(A, 1)
        error("(A, B) nu e controlabila")
    end

    if rank(obsv(A, C)) < size(A, 1)
        error("(A, C) nu e observabil")
    end

    n = size(A, 1);
    m = size(B, 2);

    flag = false;

    while ~flag
        g = randn(m, 1);
        f0 = randn(m, n);

        As = A + B * f0;
        bs = B * g;

        R = ctrb(As, bs);

        if rank(R) == n
            flag = true;
        end
    end

    qT = inv(R);
    qT = qT(end, :);

    v = (As - Ld(1) * eye(size(A, 1))) * (As - Ld(2) * eye(size(A, 1))) * (As - Ld(3) * eye(size(A, 1)));

    fT = -qT * v;

    F = f0 + g * fT;

    Aa = A';
    Bb = C';

    Ff = mono_alocare(Aa, Bb, Le); %!

    L = Ff';

    J = A + L * C;
    K = -L;
    H = B;
    M = eye(n);
    N = zeros(n, size(C, 1));

    Ac = J + H * F * M;
    Bc = K + H * F * N;
    Fc = F * M;
    Gc = F * N;
end

A = [0 0 0; 1 0 -1; 0 1 2];
B = [0 -1; 1 0; 0 1];
C = [1 0 1];

Ld = [-1 -1 -1];
Le = [-2 -2 -2];

% F = alocare(A, B, Ld);

% disp(eig(A + B * F));

% F = alocare(A, B, Le);

% disp(eig(A + B * F));

[Ac, Bc, Fc, Gc] = CDS(A, B, C, Ld, Le);


disp(Ac);
disp(Bc);
disp(Fc);
disp(Gc);


M = 2;
m = 0.1;
g = 9.81;
l = 0.5;

syms th(t) ta(t);

y = [th; ta];
x = [th; diff(th, t); ta; diff(ta, t)];

Am = [0 1 0 0; (M + m) * g / (M * l) 0 0 0; 0 0 0 1; (m * g) / M 0 0 0];
Bm = [0; -1 / (M * l); 0; 1 / M];
Cm = [1 0 0 0; 0 0 1 0];
Dm = [0; 0];