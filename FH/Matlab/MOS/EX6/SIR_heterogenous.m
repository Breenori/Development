function SIR_heterogenous(Ns, alphas, betas, m, h, max, bygroup)
    % default parameters according to the requirements
    if nargin == 0
        Ns = [1000 100 500];
        alphas = [2/7 * 0.15 10/7 * 0.15 4/7 * 0.15];
        betas = [1/14 1/14 1/(7*1.5)];
        m = [
            0.9 0.05 0.05; 
            0.1 0.7 0.2; 
            0.05 0.1 0.85
            ];
        h = 0.1;
        max = 200;
        bygroup = 1;
    end

    % Initialize values
    S = Ns - 1;
    I = [0 0 5];
    R = zeros(length(Ns), 1);
    
    % Iterate in stepsizes
    res = zeros(length(Ns), 3, max/h);
    for t=0:1:max/h
        % calculate using Euler
        change_rates = zeros(length(Ns), 3);
        for i=1:1:length(Ns)
            coefficient = 0;
            for j=1:1:length(Ns)
                coefficient = coefficient + m(i, j) * I(j) / Ns(j);
            end
            change_rates(i, 1) = -alphas(i) * coefficient * S(i);
            change_rates(i, 2) = alphas(i) * coefficient * S(i) - betas(i) * I(i);
            change_rates(i, 3) = betas(i) * I(i);
        end

        for i=1:1:length(Ns)
            S(i) = S(i) + change_rates(i, 1) * h;
            I(i) = I(i) + change_rates(i, 2) * h;
            R(i) = R(i) + change_rates(i, 3) * h;

            % Save results to matrix
            if bygroup==1
                res(i, 1, t+1) = S(i);
                res(i, 2, t+1) = I(i);
                res(i, 3, t+1) = R(i);
            else 
                res(1, i, t+1) = S(i);
                res(2, i, t+1) = I(i);
                res(3, i, t+1) = R(i);
            end
        end
    end
    
    % Plot it
    x = 0:h:max;
    tiledlayout(3,1);

    categories = ["Susceptible" "Infected" "Recovered"];
    groups = ["Group 1" "Group 2" "Group 3"];
    if bygroup == 0
        groups = [groups "Sum"];
    end

    for group=1:1:length(Ns)
        nexttile
        part_res = res(group, :, :);
        part_res = reshape(part_res, 3, size(part_res, 3));
        if bygroup == 0
            part_res = [part_res; sum(part_res)];
        end
        
        plot(x, part_res);
        if bygroup == 1
            legend(categories);
            title(sprintf("SIR - Group %d", group));
        else
            legend(groups);
            title(sprintf("%s", categories(group)));
        end
        xlabel("Time in days");
        ylabel("Number of people");

    end
end