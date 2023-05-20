function [start1, end1, start2, end2, quality] = apply_es(mu, generations, include_parents, delta, lambda, duration)
    % init according to the given parameters
    if nargin < 2
        fprintf("Usage: apply_es(mu, generations, include_parents, delta, lambda, duration). Mu and generations are required.\n")
        return;
    end
    if nargin < 3
        include_parents = 1;
    end
    if nargin < 4
        delta = 1;
    end
    if nargin < 5
        lambda = mu*2;
    end
    if nargin < 6
        duration = 100;
    end
    
    pop = cell(mu,1);
    simparams = simget('Mars_Rover_Params');
    for i=1:mu
        s = init(duration-1);
        s = eval_solution(s, duration, simparams);
        % s is a struct
        pop{i} = s; % { } = cell array
    end
    
    fprintf("initialized.\n")
    
    % main loop:
    for g = 1:generations
        if include_parents == 1
            offspring = cell(mu+lambda,1);
        else
            offspring = cell(lambda,1);
        end
    
        count = 0;
        for l = 1:lambda
            r = randi(mu); % random index
            p = pop{r};
            c = mutate(p, delta);
            c = eval_solution(c, duration, simparams);
    
            % TODO: compare c to p! & count successes (per generation)
            offspring{l} = c;
            if c.quality < p.quality
                count = count + 1;
            end
        end
        success_ratio = count/lambda;
    
        if success_ratio >= 1/5
            delta = delta * 10;
        else
            delta = delta / 10;
        end
    
        fprintf("Created offspring for generation %d. Success ratio: %f\n", g, success_ratio)
    
    
        if include_parents == 1
            for i = 1:mu
                offspring{lambda+i} = pop{i};
            end
        end
    
        % nicht vektor sortieren, sondern nur indizes (qualities und indizes abspeichern als 2 spalten) --> sortRows(A)
        qual_matrix = {cellfun(@get_quality, offspring) transpose(1:length(offspring))};
        qual_matrix = sortrows(cell2mat(qual_matrix));
    
        pop = cell(mu,1);
        for i=1:mu
            % fill next pop
            idx = qual_matrix(i, 2);
            solution = offspring{idx};
            pop{i} = solution;
        end
        fprintf("%f %f %f %f %f\n",pop{1}.start1, pop{1}.end1, pop{1}.start2, pop{1}.end2, pop{1}.quality)
    end

    % initialize the return values using the best configuration (always on first index)
    start1 = pop{1}.start1;
    end1 = pop{1}.end1;
    start2 = pop{1}.start2;
    end2 = pop{1}.end2;
    quality = pop{1}.quality;
end