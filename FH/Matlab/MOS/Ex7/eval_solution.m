function s = eval_solution(s, N, curve, h)
    duration = size(curve, 2);
    curves = simple_SIR(N, s.alpha, s.beta, h, duration-1);
    s.curve = curves(2, :);

    sse = 0;
    for t=1:1:duration
        sse = sse + (curve(t) - s.curve(t))^2;
    end

    if (s.alpha > 0) && (s.beta > 0)
        s.quality = sse;
    else
        s.quality = inf;
    end
end

