function adrenaline(alpha, a, b, x0, tStart, tEnd, tStep)
    if nargin == 0:
        alpha = 0.2;
        a = 0.1;
        b = 0.025;
        x0 = 1;
        tStart = 0;
        tEnd = 48;
        tStep=0.01;
    end

    % Initialize starting values and array
    xProgress = zeros((tEnd-tStart)/tStep+1,1);
    x = x0;
    idx = 1;

    % Simulate using euler
    for t=tStart:tStep:tEnd
        % Rate of change = f(t) - alpha * A(t)
        x_ = a + b * cos(pi * (t-8) / 12) - alpha * x;
        x = x + x_ * tStep;
        xProgress(idx) = x;
        idx = idx + 1;
    end

    % Plot it
    plot(tStart:tStep:tEnd, xProgress);
    title("Adrenaline concentration in blood");
    xlabel("t / time")
    ylabel("A(t) / concentration")
end

