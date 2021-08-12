%% MAT343 LAB3
%%
% Question 1
    E1 = eye(4);
    E1([2,3],:) = E1([3,2],:)
    
    E2 = eye(4);
    E2(3,3) = -3
    
    E3 = eye(4);
    E3(3,4) = 5
    
    A = floor(10*rand(4,3))
    E1*A 
    E2*A
    E3*A
    
    % E1*A swaps row 3 with row 2. This is true because the elementary
    % matrix has row 3 swapped with row 2.
    
    % E2*A muliplies row 3 with scalar of -3. This is true because the
    % elementary row 3 gets replaced by -3. And the scalar of the
    % multiplied by A would also multiply E2 by the same scalar to row 3.
    
    % E3*A multilies takes row 3 and adds 5 times row 4 into row 3. Using
    % muliplication you notice that since 5 is the last element in the row
    % you will use that value to multiply the last column in matrix A.
%%
% Question 2
    A = [2,3,2;-4,9,-9;-8,-24,-1]
% a)
    E1 = eye(3);
    E2 = eye(3);
    E3 = eye(3);
    
    E1(2,1) = 2
    E2(3,1) = 4
    
    E2*E1*A
    format rat
    E3(3,2) = 4/5
    U = E3*E2*E1*A
% b)
    L = inv(E1)*inv(E2)*inv(E3)
    
    format short
    A-L*U  % answer is close enough to zero to say its accurate
%% 
% Question 3
    p = [2,3,1,5,4];
    E = eye(length(p));
    E = E(p,:)
    
    A = floor(10*rand(5))
% a)
    E*A
    A*E
    % E*A, the permute matrix represents the row number. So since the first
    % index of the permute matrix is 2 and you are multiplying matrix A,
    % the first row of the result would be row 2. The permute matrix also
    % matches the elementary matrix with the corresponding indexes.
    
    % A*E, does the same as E*A, but now you look at the columns of E
    % instead of the rows and use that as the result.
% b)
    inv(E)
    E'
    % inv(E) and E' are the same matricies.
%%
% Question 4
    A = [-4,-9,-3,6;-1,3,5,4;-7,-1,-3,-5;-5,4,9,-7]
    b = [62,-47,70,-19]'
    x = [-5,-5,-5,-3]'
% a)
    [L,U,P] = lu(A)
    P*A-L*U
% b)
    x_lu = U\(L\(P*b))
% c)
    norm (x_lu - x)  
%%
% Question 5
    A = rand(600);
    x = ones(600,1);
    b = A*x;
% a)
    tic; R = rref([A,b]); x_rref = R(:,end); toc
% b)
    tic; [L,U,P] = lu(A); x_lu = U\(L\(P*b)); toc % faster
% c)
    norm(x_rref - x) % more accurate but slower
    norm(x_lu - x)