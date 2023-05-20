function s = eval_solution(s, duration, simparams)
    params = [0 s.start1 s.end1 s.start2 s.end2];
    [~, ~, Y] = sim('Mars_Rover_Params', duration, simparams, params);
    s.h_progress = Y(:,1);
    s.v_progress = Y(:,2);
    if min(s.h_progress)<0
        idx = find(s.h_progress<0);
        impact_idx = idx(1);
        s.quality = -s.v_progress(impact_idx);
    else
        s.quality = min(s.h_progress);
    end
end

