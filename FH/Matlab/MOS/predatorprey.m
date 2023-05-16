function predatorprey(alpha1, alpha2, alpha3, alpha4, alpha5, alpha6, b0, r0, tStep, tMax)
    %PREDATORPREY Summary of this function goes here
    %   Detailed explanation goes here
    if nargin==0
        alpha1 = 1;
        alpha2= 1;
        alpha3=1.5;
        alpha4=0.2;
        alpha5=0.1;
        alpha6=1;
        b0=0.5;
        r0=0.2;
        tStep=0.001;
        tMax=500;
    
    b = b0;
    r= r0;
    bProgress = zeros(tMax/tStep,1);
    rProgress = zeros(tMax/tStep,1);
    i=1;
    for t=0:tStep:tMax
        if t==110
            b=b+0.5;
        end
        b_ = b*(alpha1*(1-b/alpha2) - alpha3*r/(b+alpha4));
        r_ = r * alpha5*(1-alpha6*r/b);
        b = b+b_*tStep;
        r = r+r_*tStep;
        bProgress(i) = b;
        rProgress(i) = r;
        i = i+1;
    end
    
    plot(0:tStep:tMax, [bProgress, rProgress]);
end 

