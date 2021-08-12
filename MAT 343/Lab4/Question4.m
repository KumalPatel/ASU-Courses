clf
S =[0,1,1,0,0;0,0,1,1,0];
D1 = 9/8*eye(2);
theta = pi/8;
p = plot(S(1,:),S(2,:));
axis equal, axis([-8,8,-8,8]); grid on
hold on
Q = [cos(theta),-sin(theta);sin(theta),cos(theta)];
for i = 1:16
    S = Q*S; 
    set(p,'xdata',S(1,:),'ydata',S(2,:));
    S = D1*S;
    set(p,'xdata',S(1,:),'ydata',S(2,:));
    pause(0.1)
end
D2 = 8/9*eye(2);
QC = [cos(theta),sin(theta);-sin(theta),cos(theta)];
for i = 1:16
    S = QC*S; 
    set(p,'xdata',S(1,:),'ydata',S(2,:));
    S = D2*S;
    set(p,'xdata',S(1,:),'ydata',S(2,:));
    pause (0.1)
end
hold off