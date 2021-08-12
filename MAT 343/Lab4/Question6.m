clf
S = [0,1,1,0,0;0,0,1,1,0;1,1,1,1,1];
M1 = [1,0,0.1;0,1,0;0,0,1]; 
M2 = [1,0,0;0,1,0.1;0,0,1];
M3 = inv(M2);
M4 = inv(M1);
p = plot(S(1,:),S(2,:)); 
axis([-1,6,-1,6]), grid on;
axis square
figure (gcf)
for i = 1:40
    S = M1*S; 
    set (p,'xdata',S(1,:),'ydata',S(2,:)); 
    pause(0.1)
end
for i = 1:40
    S = M2*S ; 
    set (p,'xdata',S(1,:),'ydata',S(2,:)); 
    pause(0.1)
end
for i = 1:40
    S = M3*S ; 
    set (p,'xdata',S(1,:),'ydata',S(2,:)); 
    pause(0.1)
end
for i = 1:40
    S = M4*S ; 
    set (p,'xdata',S(1,:),'ydata',S(2,:)); 
    pause(0.1)
end