% Driverless Car Machine Learning Code
clear ; close all; clc

%% Setup the parameters
input_layer_size  = 400;  % 20x20 Input Images of Digits
num_labels = 3;          % 3 labels, from 1 to 3   
                          % (note that we have mapped "0" to label 3)

%% =========== Part 1: Loading and Visualizing Data =============
%

% Load Training Data
fprintf('Loading and Visualizing Data ...\n')

X = load('C:/ml_pgms/wipro_ml/trainingSetMatrix/wiproXData.txt');
m = size(X, 1);

y1 = load('C:/ml_pgms/wipro_ml/trainingSetMatrix/wiproY1Data.txt');
y2 = load('C:/ml_pgms/wipro_ml/trainingSetMatrix/wiproY2Data.txt');
y3 = load('C:/ml_pgms/wipro_ml/trainingSetMatrix/wiproY3Data.txt');

y = [y1;y2;y3];

printf('Sizes of X and y are:');
size(X)
size(y)


% Randomly select 100 data points to display
rand_indices = randperm(m);
sel = X(rand_indices(1:100), :);

displayData(sel);

fprintf('Program paused. Press enter to continue.\n');
pause;

%% ============ Part 2: Vectorized Logistic Regression ============
%

fprintf('\nTraining One-vs-All Logistic Regression...\n')

lambda = 25;
[all_theta] = oneVsAll(X, y, num_labels, lambda);

printf('The optimal theta values for all the 3 classes had been obtained ie. all_theta has been obtained. Its size is: ')
size(all_theta)


fprintf('Program paused. Press enter to continue.\n');
pause;


%% ================ Part 3: Prediction for One-Vs-All ================
%
pred = predictOneVsAll(all_theta, X);

fprintf('\nTraining Set Accuracy: %f\n', mean(double(pred == y)) * 100);


%% ================ Part 4: Guess for any other given input ================

%{
	% Here we want to find to which class the given example image belongs
	% To do so, we find h for the image such that the image is multiplied with 
	% each class' trained theta (got from all_theta), and the class which outputs
	% the highest h, is the class towhich it belongs
	
	hvec = zeros(num_labels, 1);
	
	%in = load('C:/ml_pgms/wipro_ml/trainingSetMatrix/wiproIn1Data.txt');
	in = load('C:/ml_pgms/wipro_ml/trainingSetMatrix/wiproRealTest2X.txt');
	printf('Size of the input loaded: ')
	size(in)
	
	
	%Pick any one of the external inputs loaded
	input = in(5,:);
	%input = X(96,:);
	input = [1 input]; % need to add the column of 1 !!
	
		
	for i = 1:num_labels
		hvec(i) = sigmoid( input * all_theta(i,:)' );
	end
	
	hvec
	class = find( hvec==max(hvec) );
	
	printf('The class which has the highest probability is: ')
	class 
	%printf('The corresponding y value is given to be: ')
	%y(96)
	printf('\n');
	
	
	
	fprintf('\n...Writing all_theta to a text file...\n')
	dlmwrite('all_theta.txt', all_theta);
	
	%A = all_theta;
	%fileID = fopen('all_theta.txt','w'); % insert path at PATH and w is to set it to write mode
	%fprintf(fileID,'%6s %12s\n','x','exp(x)'); % gives the columns a title
	%fprintf(fileID,'%6.2f\n %6.2f\n',A);
	%fclose(fileID);
	all_theta
%}	
	
%% =================	END		======================

