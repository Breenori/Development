%A = -0.0513
%B = 1
%u = 1000
%t = 13.4

R1 = 10;
R2 = 5;
C = 20;
L = 5;
U = 5500;


A = [-R1/L -1/L; 1/C -1/(R2*C)];
B = [1/L; 0];
C = [0 1];

syms tau
x0 = [0; 0];
xt = x0;

n = 50;
stepsize = 1;
y = zeros(2,n);
x = 0:stepsize:n;

for t = x
    y(1:2,t+1) = expm(t*A)*x0 + int( expm( (t-tau)*A ) * B*U, tau, 0, t);
end

f = figure;
p = plot(x, y);


%

%A = [0 3; 0 -0.1]
%B = [0; 1]

%SC = [B A*B]
%rank(SC)

% ----

%A = [3 0; 0 -0.1]
%C = [ 1 0 ]
%SO = [ C' A'*C' ]

% bzw.

%C = [ -1 1 ]
%SO = [ C' A'*C' ]

%eig(A)
