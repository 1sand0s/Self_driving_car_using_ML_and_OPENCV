function [J, grad] = lrCostFunction(theta, X, y, lambda)
%LRCOSTFUNCTION Compute cost and gradient for logistic regression with 
%regularization
%   J = LRCOSTFUNCTION(theta, X, y, lambda) computes the cost of using
%   theta as the parameter for regularized logistic regression and the
%   gradient of the cost w.r.t. to the parameters. 

% Initialize some useful values
m = length(y); % number of training examples

% You need to return the following variables correctly 
J = 0;
grad = zeros(size(theta));

% ====================== YOUR CODE HERE ======================
%

%%% COST

prod = X * theta; % mx1

h = sigmoid(prod); % mx1
h1 = log(h);
h2 = log(1-h);


y1 = y;
y2 = 1-y;

J1 = y1 .* h1;
J2 = y2 .* h2;

% divide by minu 1/m and therefore add the two results

J = J1 + J2; % element-wise addition
			 % gives the cost for each training eg
			 
J = sum(J); % calculates the summation part
J = -(J/m); %calculates the final summation value w/ minus sign.
			  % ie. J = -(1/m)*J
			  
regMatrix = theta .* theta; % squaring the elements of theta
regMatrix(1) = 0; % to prevent the addition of thetaNot 			  
reg1 = (lambda/(2*m)) * (sum (regMatrix)); % a single number is got		  

J = J + reg1;

%%%GRAD

beta = h - y;

grad = X' * beta;
grad = grad/m;

regMatrix2 = theta;
regMatrix2(1) = 0;  % to prevent the addition of thetaNot 	
reg2 = (lambda/m) * regMatrix2; % is an nx1 matrix with first element = 0
grad = grad + reg2;


% =============================================================
J = J;
grad = grad(:);

end
