% Symbolic and initial state
syms tau
x0 = [0; 0];

% Variables
R1 = 12;
R2 = 24;
C = 0.02;
L = 0.1;
U = 220;

% (A, B, C) form of system
A = [-R1/L -1/L; 1/C -1/(R2*C)];
B = [1/L; 0];
C = [0 1];

% Initialize matrix and x-axis
n = 50;
stepsize = 1;
X = zeros(2,n);
x = 0:stepsize:n;

% Run the simulation
for t = x
    X(1:2,t+1) = expm(t*A)*x0 + int( expm( (t-tau)*A ) * B*U, tau, 0, t);
end

% Plot the results
f = figure;
p = plot(x, X);
xlabel("t")
ylabel("X(t)")
legend('i(t)', 'y(t)');


%A = -0.0513
%B = 1
%u = 1000
%t = 13.4


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
