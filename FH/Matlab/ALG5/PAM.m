function PAM(N)

    if (nargin<1)
        N=60;
    end
    
    L = createLmatrix();
    n_ = 15720;
    pa = createProbabilities();
    epsilon = 0.00000000001;
    
    % todo: L should be fully filled
    for i = 1:20
        for j = (i+1):20
            L(i,j) = L(j,i);
        end
    end
    
    % todo: calculate p(a,b) = pab 
    for i = 1:20
        for j = 1:20
            if(i~=j)
                pab(i,j) = L(i,j) / (100*n_*pa(i));
                if pab(i,j) < epsilon
                    pab(i,j) = epsilon;
                end
                % TODO!
            end
        end
    end

    for i=1:20
        pab(i,i) = 1 - sum(pab(i,:));
    end
    pab20 = pab^20;
   
    % todo: calculate PAM1
    for i = 1:20
        for j = 1:20
            PAM1(i,j) = log10(pab(i,j) / pa(j))*10;
            PAM20(i,j) = log10(pab20(i,j) / pa(j))*10;
        end
    end
    % todo: calculate PAM20
    
end

function L = createLmatrix()
    L = [   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0;
           30   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0;
          109  17   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0;
          154   0 532   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0;
           33  10   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0;
           93 120  50  76   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0;
          266   0  94 831   0 422   0   0   0   0   0   0   0   0   0   0   0   0   0   0;
          579  10 156 162  10  30 112   0   0   0   0   0   0   0   0   0   0   0   0   0;
           21 103 226  43  10 243  23  10   0   0   0   0   0   0   0   0   0   0   0   0;
           66  30  36  13  17   8  35   0   3   0   0   0   0   0   0   0   0   0   0   0;
           95  17  37   0   0  75  15  17  40 253   0   0   0   0   0   0   0   0   0   0;
           57 477 322  85   0 147 104  60  23  43  39   0   0   0   0   0   0   0   0   0;
           29  17   0   0   0  20   7   7   0  57 207  90   0   0   0   0   0   0   0   0;
           20   7   7   0   0   0   0  17  20  90 167   0  17   0   0   0   0   0   0   0;
          345  67  27  10  10  93  40  49  50   7  43  43   4   7   0   0   0   0   0   0;
          772 137 432  98 117  47  86 450  26  20  32 168  20  40 269   0   0   0   0   0;
          590  20 169  57  10  37  31  50  14 129  52 200  28  10  73 696   0   0   0   0;
            0  27   3   0   0   0   0   0   3   0  13   0   0  10   0  17   0   0   0   0;
           20   3  36   0  30   0  10   0  40  13  23  10   0 260   0  22  23   6   0   0;
          365  20  13  17  33  27  37  97  30 661 303  17  77  10  50  43 186   0  17   0];
end

function p = createProbabilities() 
        % A ala  R arg  N asn  D asp  C cys  Q gln  E glu  G gly  H his  I ile
    p = [ 0.087; 0.041; 0.040; 0.047; 0.033; 0.038; 0.050; 0.089; 0.034; 0.037; ...
        % L leu  K lys  M met  F phe  P pro  S ser  T thr  W trp  Y tyr  V val
          0.085; 0.081; 0.015; 0.040; 0.051; 0.070; 0.058; 0.010; 0.030; 0.065 ] ;
end