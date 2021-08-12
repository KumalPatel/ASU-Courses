%% MAT343 LAB5
%%
% Question 1
    dat = load('gco2.dat');
    year = dat(:,1);
    conc = dat(:,2);
% a)
    format short e
    X = [ones(size(year)),year];
    z = X'*conc;
    S = X'*X;
    U = chol(S);
    w = U'\z;
    c = U\w
    plot(year,conc,'o','linewidth',2)
    q = 1960:1:2037;
    fit = c(1)+c(2)*q;
    hold on
    plot (q,fit,'-k');
    axis tight
    hold off
% b)
    format short e
    X = [ones(size(year)),year,year.*year];
    z = X'*conc;
    S = X'*X;
    U = chol(S);
    w = U'\z;
    c = U\w
    plot(year,conc,'o','linewidth',2)
    q = 1960:1:2037;
    fitQ = c(1)+c(2)*q+c(3)*q.*q;
    fitL = -3.0144e+03+1.6926e+00*q;
    hold on
    plot(q,fitL,'-k');
    plot(q,fitQ,'-r');
    axis tight
    legend('data points','linear fit','quadratic fit','location','northwest');
    hold off
%%
% Question 2
% a)
   t = [0;5;10;15;20;25];
   B = [8;8.7;10.7;12.5;14.7;17.2];
   Y = log(B);
   T = [ones(size(t)),t];
   z = T'*Y;
   s = T'*T;
   U = chol(s);
   w = U'\z;
   c = U\w
   plot(t,Y,'o','linewidth',2)
   q = 0:1:30;
   fit = c(1)+c(2)*q;
   hold on
   plot(q,fit,'r');
   hold off
% b)
   t = [0;5;10;15;20;25];
   B = [8;8.7;10.7;12.5;14.7;17.2];
   b = log(B);
   plot(t,B,'o','linewidth',2)
   x = exp(2.0484e+00);
   y = 3.1751e-02;
   fitE = x*exp(y*q);
   hold on
   plot(q,fitE,'r');
   hold off
% c)
    % t = x*e^(y*t) = 20
    % e ^(y*t) = 20/x
    % y*t = ln(20/x)
    % t = 1/y*(ln(20/x))
    %..solved t using algebra, and all values are scaled by 1000
%%
% Question 3
    m = [1;2;3;4;5;6;7;8;9;10;11;12];
    Y = [67.8;71.9;77.2;85.6;94.1;103.2;105.5;103.6;99.8;89.4;76.5;67.9];
    M = [ones(size(m)),m,m.^2,m.^3,m.^4];
% a)    
    z = M'*Y;
    s = M'*M;
    u = chol(s);
    w = u'\z;
    c = u\w
    plot(m,Y,'o','linewidth',2)
    q = 0:1:15;
    fit = c(1)+c(2)*q+c(3)*q.^2+c(4)*q.^3+c(5)*q.^4;
    hold on
    plot(q,fit,'r');
    hold off
% b)
    c = M\Y
    c = c([5:-1:1]);
    q = 1:0.1:15;
    z = polyval(c,q);
    figure
    plot(q,z,m,Y,'o','linewidth',2);
    axis tight
    
% The values are equivalent, identical graphs, part b has a smoother graph
% perhaps it is more a more accurate method of doing such a process.

