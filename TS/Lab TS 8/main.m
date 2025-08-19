M = 2;
m = 0.1;
g = 9.81;
l = 0.5;

A = [0 1 0 0; (M + m) * g / (M * l) 0 0 0; 0 0 0 1; m * g / M 0 0 0];
B = [0; -1 / (M * l); 0; 1 / M];
C = [1 0 0 0; 0 0 1 0];
D = [0; 0];

function [H,delta] = hurwitz(p)
    n = numel(p)-1;
    p1 = p(2:2:end);
    p2 = p(1:2:end);

    if isnumeric(p)
        H = zeros(n,n);
        delta = zeros(n,1);
    else
        H = sym(zeros(n,n));
        delta = sym(zeros(n,1));
    end

    i = 0;

    for k = 1:n
        if mod(k,2)
            H(k,i+[1:numel(p1)]) = p1;
        else
            H(k,i+[1:numel(p2)]) = p2;
            i = i + 1;
        end
    end

    for k = 1:n
        delta(k) = det(H(1:k,1:k));
    end
end

disp(eig(A));

if all(real(eig(A)) < 0)
    disp("Sistem intern stabil");
elseif any(real(eig(A)) == 0)
    disp("Sistem la limita de stabilitate intern");
else
    disp("Sistem instabil intern");
end

syms s

disp("Polin caracterstic:");
disp(det(s * eye(size(A)) - A));

coeffs = sym2poly(det(s * eye(size(A)) - A));

if any(coeffs <= 0) || length(coeffs) < 4
    disp("Nu se poate folosi criteriul");
else
    H = hurwitz(coeffs);
    display(H);
    display(diag(H));

    if any(diag(H) > 0)
        disp("Sistem intern stabil");
    elseif any(diag(H) == 0)
        disp("Sistem la limita intern");
    else
        disp("Sistem instabil intern");
    end
end

[num, den] = ss2tf(A, B, C, D, 1);

all_den = den;
p = den(1, :);

for i = 2:size(all_den, 1)
    p = conv(p, all_den(i, :));
end

c = roots(p);

disp("Polii:");
disp(c);

if all(real(c) < 0)
    disp("Sistemul este extern stabil");
elseif any(real(c) < 0)
    disp("Sistemul este la limita extern");
else
    disp("Sistem extern instabil");
end

if any(p <= 0)
    disp("Nu se poate folosi criteriul");
else
    H_ext = hurwitz(p);
    disp(H_ext);
    disp(diag(H_ext));

    if all(diag(H_ext) > 0)
        disp("Sistem extern stabil");
    elseif any(diag(H_ext) == 0)
        disp("Sistem la limita de stabilitate extern");
    else
        disp("Sistem instabil extern");
    end
end

T = [1 / ((s + 1) * (s + 3)) (s - 2) / ((s + 1) * (s + 2))];

cmmmc = conv([1 1 0], [0 1 2]);

if any(cmmmc <= 0)
    disp("Nu se poate folosi criteriul");
else
    H_T = hurwitz(cmmmc);

    disp("Matricea:");
    disp(H_T);
    disp("Minorii:");
    disp(diag(H_T));

    if all(diag(H_T) > 0)
        disp("T e extern stabil.");
    elseif any(diag(H_T) == 0)
        disp("T la limita de stabilitate.");
    else
        disp("T e extern instabil.");
    end
end
