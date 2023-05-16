function logisticgrowth(alpha, beta, x0, tStep, tMax)
    if nargin==0
        alpha   = 10;
        beta    = 2;
        x0      = 0.001;
        tStep   = 0.01;
        tMax    = 2;
    end
    
    xProgress = zeros(tMax/tStep+1,1);
    x = x0;
    idx = 1;
    
    for t=0:tStep:tMax
        x_ = alpha * x - beta * x * x;
        % Euler:
        x = x + x_ * tStep;
        xProgress(idx) = x;
        idx = idx+1;
    end

    plot(0:tStep:tMax, xProgress);
end