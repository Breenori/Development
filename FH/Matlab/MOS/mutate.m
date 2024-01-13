function s = mutate(s, delta)
    s.start1 = s.start1 + normrnd(0, delta);
    s.end1 = s.end1 + normrnd(0, delta);
    if s.start1 > s.end1
        [s.start1, s.end1] = deal(s.end1, s.start1);
    end
    s.start2 = s.start2 + normrnd(0, delta);
    s.end2 = s.end2 + normrnd(0, delta);
    if s.start2 > s.end2
        [s.start2, s.end2] = deal(s.end2, s.start2);
    end
end

