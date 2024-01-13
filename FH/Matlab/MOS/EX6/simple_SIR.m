function simple_SIR(N, alpha, beta, h, max)
    % default parameters according to the requirements
    if nargin == 0
        r0 = 7.5;
        N = 9640742; % population size of tokyo
        h = 0.1;
        beta = 1/10;
        alpha = r0 * beta;
        max = 100;
    end

    % Initialize values
    S = N - 1;
    I = 1;
    R = 0;
    
    % Iterate in stepsizes
    res = zeros(3, max/h);
    for t=0:1:max/h
        % calculate using Euler
        S_ = -alpha * S * I / N;
        I_ = alpha * S * I / N - beta * I;
        R_ = beta * I;
        S = S + S_ * h;
        I = I + I_ * h;
        R = R + R_ * h;

        % Save results to matrix
        res(1, t+1) = S;
        res(2, t+1) = I;
        res(3, t+1) = R;
    end
    
    % Plot it
    x = 0:h:max;
    plot(x, res);
    legend(["Susceptible" "Infected" "Recovered"]);
    xlabel("Time in days");
    ylabel("Number of people");
    title("SIR Model in Epidemiology");
end