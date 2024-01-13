function s = mutate(s, delta)
    %fprintf("%d --- %d ------------ %d \n", s.alpha, s.beta, delta);
    s.alpha = s.alpha + normrnd(0, delta);
    s.beta = s.beta + normrnd(0, delta);
end

