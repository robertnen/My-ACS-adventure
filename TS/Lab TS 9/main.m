A = [0 0 0; 1 0 -1; 0 1 2];
B = [0 -1; 1 0; 0 1];
C = [1 0 1];
Ld = [-1 -1 -1];


if rank(ctrb(A, B)) < size(A, 1)
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

v = (As + eye(size(A, 1))) * (As + eye(size(A, 1))) * (As + eye(size(A, 1)));
disp(v);
disp('adasfasf');

fT = -qT * v;

F = f0 + g * fT;

disp(F);
disp(eig(A + B * F));