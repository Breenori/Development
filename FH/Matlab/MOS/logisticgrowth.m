function logisticgrowth(alpha, beta, x0, tStep, tEnd)
    if nargin==0
        alpha   = 1/5;
        beta    = 1/5175;
        x0      = 10;
        tStep   = 0.01;
        tEnd    = 100;
    end
    
    % Initialize values and array
    xProgress = zeros(tEnd/tStep+1,1);
    x = x0;
    idx = 1;
    
    % Simulate using euler
    for t=0:tStep:tEnd
        x_ = alpha * x - beta * x * x;
        x = x + x_ * tStep;
        xProgress(idx) = x;
        idx = idx+1;
    end

    % Get maximum value and 99 percentile value
    max = xProgress(idx-1);
    indices = find(xProgress>max*0.99);
    idx99 = indices(1) / (1 / tStep);

    % Print necessary values
    fprintf("Population size after 12 days: %d\n", round(xProgress(12 * 1 / tStep)));
    fprintf("Population size after saturation: %d\n", round(max))
    fprintf("99 percent of population reached after day %d\n", round(idx99))

    % plot everything
    plot(0:tStep:tEnd, xProgress);
    xlim([0 idx99])
    title("Population size of fruit flies")
    xlabel("t in days")
    ylabel("Population size")
end