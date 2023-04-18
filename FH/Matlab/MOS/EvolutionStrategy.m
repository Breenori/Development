% init
mu = 100;
lambda = mu*2;
generations = 1000;
delta = 1;

pop = [];
for i=1:mu
    s = init( ... );
    s = eval(s)
    % s is a struct
    pop{i} = s; % { } = cell array
end

% main loop:
for g = 1:generations
    for l = 1:lambda
        r = rand(mu); % random index
        p = pop{r}
        c = mutate(p, delta);
        c = eval(c);
        % TODO: compare c to p! & count successes (per generation)
        offspring{l} = c;
    end

    % nicht vektor sortieren, sondern nur indizes (solutions und indizes abspeichern als 2 spalten) --> sortRows(A)

    pop = [];
    for i=1:mu
        % fill next pop
    end
end