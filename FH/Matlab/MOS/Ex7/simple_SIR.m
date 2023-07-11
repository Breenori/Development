function res = simple_SIR(N, alpha, beta, h, max)
    % default parameters according to the requirements
    if nargin == 0
        N = 9640742; % population size of tokyo
        h = 0.1;
        beta = 1/10;
        alpha = 7.5 * beta; % r0 * beta
        max = 100;
    end

    % Initialize values
    % Simple variant: recovered is not required (only I relevant)
    S = N - 1;
    I = 1;
    %R = 0;
    
    % Iterate in stepsizes
    res = zeros(2, max);
    index = 1;
    for t=0:1:max/h
        % calculate using Euler
        S_ = -alpha * S * I / N;
        I_ = alpha * S * I / N - beta * I;
        %R_ = beta * I;
        S = S + S_ * h;
        I = I + I_ * h;
        %R = R + R_ * h;

        % Save results to matrix
        if mod(t, 1/h) == 0
            res(1, index) = round(S);
            res(2, index) = round(I);
            %res(3, index) = R;
            index = index + 1;
        end
    end

end