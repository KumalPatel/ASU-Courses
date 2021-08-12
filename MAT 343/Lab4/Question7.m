clf 
S = [0,1,1,0,0;0,0,1,1,0;1,1,1,1,1]; 
M1 = [1,0,0.1;0,1,0;0,0,1];
M2 = inv(M1);
theta = pi/8;  
Q = [cos(theta),-sin(theta),0;sin(theta),cos(theta),0;0,0,1]; 
QP = [1,0,5;0,1,0;0,0,1]*Q'*[1,0,-5;0,1,0;0,0,1]; 
QP2 = [1,0,1;0,1,0;0,0,1]*Q*[1,0,-1;0,1,0;0,0,1];
p = plot(S(1,:),S(2,:)); 
axis([-0.5,7,-2,5]), grid on;
axis equal;
figure(gcf) 
for i = 1:40
    S = M1*S; 
    set(p,'xdata',S(1,:),'ydata',S(2,:));  
    pause(0.1) 
end 
for i = 1:4
    S = QP*S; 
    set(p,'xdata',S(1,:),'ydata',S(2,:));
    pause(0.1) 
end
for i = 1:40
    S = M2*S; 
    set(p,'xdata',S(1,:),'ydata',S(2,:));  
    pause(0.1) 
end
for i = 1:4
    S = QP2*S; 
    set(p,'xdata',S(1,:),'ydata',S(2,:));
    pause(0.1) 
end
