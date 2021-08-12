%% MAT343 LAB3
%%
% Question 1
    clf
    S = [0,1,1,0,0;0,0,1,1,0];
    plot(S(1,:),S(2,:),'linewidth',2)
    hold on
    T = [1,0;1,1];
    TS = T*S;
    plot(TS(1,:),TS(2,:),'-r','linewidth',2);
    title('Vertical Shear')
    legend('Original Square','Sheared Square','location','southeast')
    axis equal, axis([-1,3,-1,3]); grid on
    hold off
%%
% Question 2
   clf
   S = [0,1,1,0,0;0,0,1,1,0];
   plot(S(1,:),S(2,:),'linewidth',2)
   hold on
   T = [1,3;0,1];
   Q = [cos(pi/6),-sin(pi/6);sin(pi/6),cos(pi/6)];
   QTS = Q*T*S;
   plot(QTS(1,:),QTS(2,:),'-r','linewidth',2);
   title('Horizontal Shear With Rotation')
   legend('Original Square','Modified Square','location','northeast')
   axis equal, axis([-2,4,-2,4]); grid on
   hold off
   % The order matters, as you can see. In Example5, it rotated and then
   % sheared the original square. Whereas, we are trying to shear and then
   % rotate the square. The result looks identical to a reflected vertical
   % shear. So we can say that order does matter.
%% 
% Question 3
    type('Question3.m')
%%
% Question 4
    type('Question4.m')
%%
% Question 5
    clf
    M = [1,0,3;0,1,-3;0,0,1];
    S = [0,1,1,0,0;0,0,1,1,0;1,1,1,1,1];
    MS = M*S;
    plot(MS(1,:),MS(2,:),'-k','linewidth',2);
    hold on
    R = [0,1,0;1,0,0;0,0,1];
    RS = R*MS;
    plot(RS(1,:),RS(2,:),'-r','linewidth',2);
    plot([-4,5],[-4,5]);
    legend('Translated Square','Reflected Square','Line y = x','location','east')
    axis([-4,5,-4,5]); grid on
    hold off
%%
% Question 6
    type('Question6.m')
%%
% Question 7
    type('Question7.m')