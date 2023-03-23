A = -0.0513
B = 1
u = 1000
t = 13.4

syms tau
x0 = 100000

xt = expm(t*A)*x0 + int( expm( (t-tau)*A ) * B*u, tau, 0, t)

%

A = [0 3; 0 -0.1]
B = [0; 1]

SC = [B A*B]
rank(SC)

% ----

A = [3 0; 0 -0.1]
C = [ 1 0 ]
SO = [ C' A'*C' ]

% bzw.

C = [ -1 1 ]
SO = [ C' A'*C' ]

eig(A)
