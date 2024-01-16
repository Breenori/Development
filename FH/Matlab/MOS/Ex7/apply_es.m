function [alpha, beta, quality] = apply_es(curve, N, mu, generations, include_parents, delta, lambda, h)
    % init according to the given parameters
    if nargin == 0
        fprintf("Usage: apply_es(mu, generations, include_parents, delta, lambda, duration). Mu and generations are required.\n")
        return;
    end
    if nargin < 3
        mu = 10;
    end
    if nargin < 4
        generations = 10;
    end 
    if nargin < 5
        include_parents = 0;
    end
    if nargin < 6
        delta = 1;
    end
    if nargin < 8
        lambda = mu*2;
    end
    if nargin < 9
        h = 0.001;
    end

    duration = size(curve, 2);
    
    pop = cell(mu,1);
    for i=1:mu
        s = init();
        s = eval_solution(s, N, curve, h);
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
            c = eval_solution(c, N, curve, h);
    
            % TODO: compare c to p! & count successes (per generation)
            offspring{l} = c;
            if c.quality < p.quality
                count = count + 1;
            end
        end
        success_ratio = count/lambda;
    
        if success_ratio >= 1/5
            delta = delta / 0.82;
        else
            delta = delta * 0.82;
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
        fprintf("%f %f %f\n",pop{1}.alpha, pop{1}.beta, pop{1}.quality)
        fprintf('[%s]\n', join(string(curve), ','));
        fprintf('[%s]\n', join(string(pop{1}.curve), ','));
    end

    % initialize the return values using the best configuration (always on first index)
    alpha = pop{1}.alpha;
    beta = pop{1}.beta;
    quality = pop{1}.quality;

    x = 1:1:duration;
    plot(x, [curve; pop{1}.curve]);
    legend(["Truth", "ES"]);
    xlabel("Time in days");
    ylabel("Number of people");
    title("Model Identification");
end