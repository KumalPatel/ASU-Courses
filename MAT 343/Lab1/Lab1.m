%% MAT343 LAB1
%%
% Question 1
    A = [4,-5,4;4,0,1;5,-1,1]
    B = [0.1,1.4,-0.8;1.6,2.5,0.5;3.9,1.1,3.0]
    C = [0,0;-2,0;3,4]
% i)
    A+B
% ii)
    5*(A+B)
% iii)
    %C*A 
% iv)
    %A+C 
% v)
    1+C
% vi)
    A*B
% vii)
    5*A+5*B
% viii)
    B*A
% ix)
    A*C
% x)
    B*A
% a)
    % C*A and A+C were refused because the dimensions of the calculations
    % do not agree and is unable to compute.
% b)
    % Yes, A+B does equal B+A because in addition order does not matter.
% c)
    % 1+C adds one to each element in the C matrix.
% d)
    % Yes, 5*(A+B) = 5*A+5*B because it is a constant added by two
    % matricies thus order doesn't matter.
% e)
    % No, A*B does not equal B*A. Since it is multiplication order matters
    % in this case.
%%
% Question 2
    A = [12,9;-16,12]
    B = [-1,-2;2,4]
    C = [-2,6;1,-3]
% i)
    %(A*B)^2 = A^2*B^2 
    % False
% ii)
    % A*(B+C) = A*B+A*C 
    % True
% iii)
    % If BC = 0, then B = 0 or C = 0
    % False a 0 matrix multiplied by any other matrix will always be 0. But
    % doesn't mean that because B*C = 0, then C or C has to be a 0 matrix.
% iv)
    % If A^2 = 0, then A = 0
    % False again like i the previous question it is true but doesnt mean
    % that is why. If A^2 = 0, doesnt mean A = 0. It could be numerous of
    % possibilities.
% v)
    %(A+B)^2 = A^2+2*A*B+B^2 
    % False
% vi)
    %(A-B)*(A+B) = A^2-B^2 
    % False
% vii)
    % A*(B+C) = B*A+C*A 
    % False
%%
% Question 3
    A = [0,3;-6,3]
    B = [-4,2;2,5]
    C = [1,-1,0;5,-2,-3]
% i)
    B'*A'
% ii)
    C'*A
% iii)
    A'*B'
% iv)
    (A')'
% v)
    %A*C'
% vi)
    (A*B)'
% vii)
    B'
% a)
    % Yes, A*C' was refused because the dimmensions do not agree for matrix
    % multiplication.
% b)
    % No, (AB)' does not equal A'*B' because when you are transposing the
    % rows become the columns and if u multiply the matrices first before
    % doing that then the quantity would be different. Yes, (AB)' equals
    % B'*A' because you switched the rows with columns it ends up aligning
    % if you change the order of multiplication because you are using B's
    % columns and A's rows as you would in straight matrix multiplication.
% c)
    % B is not symmetric, B does not equal B'.
% d)
    % (A')' relationship to A is the same. It would result in the original
    % matrix when transposing twice.
%%
% Question 4
    R = round(10*rand(3)), S = round(10*rand(3))
% i)
    [R*S(:,1), R*S(:,2), R*S(:,3)]
% ii)
     [R(1,:)*S; R(2,:)*S; R(3,:)*S]
% iii)
    % They all end up being the result of R*S.
% iv)
    % In the first question matrix R is being multiplied by the first
    % column of matrix S as the first row. Next row is matrix R being
    % muliplied by the second row of matrix S, and etc. In the second
    % question it is the same thing but backwards. You use the first column
    % of matrix R and multiply it by matrix S, and continue to the last
    % column of matrix R.
%%
% Question 5
    M = 4*triu(ones(3))
    N = diag([7,8,9])
    P = 2*eye(3)
    Q = 6*ones(3,2)
%%
% Question 6
    G = [A,C,eye(2);eye(2),zeros(2,3),B]
%%
% Question 7`
% a)
    H = G(1:3,5:7)
% b)
    E = H;
    E(2,1) = 2
% c)
    F = H(1:3,2:3)
% d)
    % If you enter G(:,:), it returns all the rows and columns of matrix G.
    % And G(:), returns all the rows of matrix G, as a row vector matrix.
% e)
    % If you enter G(5,1), it will return the index value at row 5 and
    % column 1, but in matrix G, there is no existing element, and will
    % return an error as it as the index is out of bounds.
% f)
    % If you enter max(G), it will return the maximum value per column as a
    % single column vector matrix. And sum(G) does the same but it will
    % take the sum on the column this time.
% g)
    % If you enter G(G>2), it will return every value greater than 2 as a
    % row vector, and if you set G(G>2)=300, then it will return the
    % original G matrix, but in place of the values greater than 2, it will
    % be replaced with 300. G(G>2) is a conditonal statement so MATLAB
    % searches the rows for those values and returns the value when the
    % statement is true in a row vector.
%%
% Question 8
    A = [2,2,5;-6,-9,-11;8,-1,37]
    format rat
    A = [(1/2)*A(1,:);A(2,:);A(3,:)]
    A = [A(1,:);A(2,:)+6*A(1,:);A(3,:)]
    A = [A(1,:);A(2,:);A(3,:)-8*A(1,:)]
    A = [A(1,:);(-1/3)*A(2,:);A(3,:)]
    A = [A(1,:);A(2,:);A(3,:)+9*A(2,:)]
    A = [A(1,:);A(2,:);(1/5)*A(3,:)]