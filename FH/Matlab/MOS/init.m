function s = init(range)
    s = struct;
    s.start1 = rand * range;
    s.end1 = s.start1 + rand * (range - s.start1);
    s.start2 = rand * range;
    s.end2 = s.start2 + rand * (range - s.start2);
    s.h_progress = [];
    s.v_progress = [];
    s.quality = [];
end
