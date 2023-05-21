function predatorprey(alpha, beta, gamma, delta, b0, r0, tStep, tEnd)
    if nargin==0
        alpha = 0.4;
        beta = 0.4/50;
        gamma = 0.3;
        delta = 0.3/300;
        b0 = 500;
        r0 = 5;
        tStep = 0.001;
        tEnd = 100;
    end
    
    % Initialize values and create arrays
    b = b0;
    r = r0;
    bProgress = zeros(tEnd/tStep,1);
    rProgress = zeros(tEnd/tStep,1);
    i=1;
    
    % Simulate using euler (small stepsize needed!)
    for t=0:tStep:tEnd
        b_ = alpha * b - beta * b * r;
        r_ = -gamma * r + delta * b * r;
        b = b + b_ * tStep;
        r = r + r_ * tStep;
        bProgress(i) = b;
        rProgress(i) = r;
        i = i+1;
    end
    
    % plot it
    plot(0:tStep:tEnd, [bProgress, rProgress]);
    title("Predator prey model")
    xlabel("Time t")
    ylabel("Population size")
    legend(["Prey", "Predators"])
end 

