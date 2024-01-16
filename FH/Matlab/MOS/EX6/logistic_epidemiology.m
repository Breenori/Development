function logistic_epidemiology(N, ks, h, max)
    % default parameters for this example
    if nargin == 0
        N = 10000;
        ks = [10 20 30 50];
        h = 0.01;
        max = 2;
    end

    tEnd = max/h;
    res = zeros(length(ks), tEnd);
    % simulate all k's
    for idx=1:1:size(res, 1)
        % reinitialize I for every new k
        I = 1;
        k = ks(idx);
        % simulation using eulers method
        for t=0:1:tEnd
            I_ = k * I * (N - I)/N;
            I = I + I_ * h;
            res(idx, t+1) = I;
        end
    end

    % plot it
    x = 0:h:max;
    plot(x, res);
    xlabel("Time in days");
    ylabel("Infected")
    title("Logistic Model in Epidemiology");
    legend(["k=10", "k=20", "k=30", "k=50"]);
end