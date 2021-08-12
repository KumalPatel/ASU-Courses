%% MAT343 LAB2
%%
% Question 1
%
% (a)
    A = floor(25*rand(700));
    z = ones(700,1);
    b = A*z;
% i)
    tic, x = A\b; toc  % faster method
    tic, y = inv(A)*b; toc 
% ii)
    sum(abs(x-z)) % more accurate
    sum(abs(y-z))
% (b)
    A = floor(25*rand(1400));
    z = ones(1400,1);
    b = A*z;
    
    tic, x = A\b; toc  % faster method
    tic, y = inv(A)*b; toc
    
    sum(abs(x-z)) % more accurate
    sum(abs(y-z))
    
    A = floor(25*rand(2800));
    z = ones(2800,1);
    b = A*z;
    
    tic, x = A\b; toc  % faster method
    tic, y = inv(A)*b; toc
    
    sum(abs(x-z)) % more accurate
    sum(abs(y-z))
% (c)
    % Becuase it is in the form Ax = b, which represents the form of a 
    % system and z represnts the solutions of the matrix.
%%
% Question 2
    n = 70 ;
    B = eye(n) - triu(ones(n),1);
    A = B'*B;
    z = ones(n,1);
    b = A*z;
    
    x = A\b;
    y = inv(A)*b;
    
    sum(abs(x - z)) % more accurate
    sum(abs(y - z))
%%
% Question 3
    A = floor(10*rand(8));
    b = floor(20*rand(8,1))-10;
% (a)
    x = A\b
% (b)
    U = rref([A, b])
% (c)
    U(:,9) - x
% (d)
    A(:,6) = 6*A(:,3)+4*A(:,2); % There will be only one solution
% (e)
    y = floor(20*rand(8,1)) - 10;
    c = A*y; % The matrix was created to have at least one solution.
% (f)
    U = rref([A,c]) % since one column has two nonzero numbers, there is two solutions.
%% 
% Question 4
    A = rand(3,6)
    x = rand(6,1)
    myrowproduct(A,x)
    A*x
    
    A = rand(5,5)
    x = rand(5,1)
    myrowproduct(A,x)
    A*x
 
    A = rand(5,5)
    x = rand(1,5)
    myrowproduct(A,x)
    % A*x
%% 
% Question 5
%
% (a)
    A = rand(2,2)
    B = rand(2,5)
    columnproduct(A,B)
    A*B
    
    A = rand(4,4)
    B = rand(4,3)
    columnproduct(A,B)
    A*B
    
    A = rand(4,4)
    B = rand(3,4)
    columnproduct(A,B)
    % A*B    
% (b)
    A = rand(2,2)
    B = rand(2,5)
    rowproduct(A,B)
    A*B
    
    A = rand(4,4)
    B = rand(4,3)
    rowproduct(A,B)
    A*B
    
    A = rand(4,4)
    B = rand(3,4)
    rowproduct(A,B)
    % A*B
%%
% Functions
function product = myrowproduct(A,x)
[a b] = size(A);
[c d] = size(x);
product = [];

if b~=c
    disp('Dimensions do not match');
    return;
end
    for index = 1:a
        product = [product;A(index,:)*x];
    end
end

function result = columnproduct(A,B)
[a b] = size(A);
[c d] = size(B);
result = [];

if c~=b
    disp('Dimensions do not match');
    return;
end
    for index = 1:d
        result(:,index) = A*B(:,index);
    end
end

function answer = rowproduct(A,B)
[a b] = size(A);
[c d] = size(B);
answer = [];

if b~=c
    disp('Dimensions do not match');
    return;
end
    for index = 1:a
        answer = [answer;A(index,:)*B];
    end
end 