clf
S =[0,1,1,0,0;0,0,1,1,0];
theta = pi/8;
p = plot(S(1,:),S(2,:));
axis equal, axis([-2,2,-2,2]), grid on;
hold on
Q = [cos(theta),-sin(theta);sin(theta),cos(theta)];
for i = 1:16
    S = Q*S; 
    set(p,'xdata',S(1,:),'ydata',S(2,:));
    pause(0.1)
end
QC = [cos(theta),sin(theta);-sin(theta),cos(theta)];
for i = 1:16
    S = QC*S; 
    set(p,'xdata',S(1,:),'ydata',S(2,:));
    pause (0.1)
end
hold off
