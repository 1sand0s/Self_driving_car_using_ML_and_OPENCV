function class = testSingleEx(photoNumber, trainAgain)
% Displays the prediction of the code for a particular image number being input.

printf('\n ===>>> Photo Number: %d \n', photoNumber-1);
%% =======	Essentials of wiproTrain	==============


	input_layer_size  = 400;  	% 20x20 Input Images of Digits
	num_labels = 3;          	% 10 labels, from 1 to 10   
								% (note that we have mapped "0" to label 10)


	train = trainAgain;
	if (train == 1)
		%% =========== Part 1: Loading and Visualizing Data =============
		%

			% Load Training Data
			fprintf('Loading and NOT Visualizing Data ...\n')

			%X = load('C:/ml_pgms/wipro_ml/trainingSetMatrix/wiproXData.txt');
			X = load('C:\ml_pgms\wipro_ml\trainingSetMatrixEdit1/wiproXData.txt');
			m = size(X, 1);

			y1 = load('C:\ml_pgms\wipro_ml\trainingSetMatrixEdit1/wiproY1Data.txt');
			y2 = load('C:\ml_pgms\wipro_ml\trainingSetMatrixEdit1/wiproY2Data.txt');
			
			%y1 = load('C:/ml_pgms/wipro_ml/trainingSetMatrix/wiproY1Data.txt');
			%y2 = load('C:/ml_pgms/wipro_ml/trainingSetMatrix/wiproY2Data.txt');
			%y3 = load('C:/ml_pgms/wipro_ml/trainingSetMatrix/wiproY3Data.txt');

			y = [y1;y2];%;y3];

			printf('Sizes of X and y are:');
			size(X)
			size(y)


			fprintf('Program NOT paused. Press enter to continue.\n');
			%pause;

		%% ============ Part 2: Vectorize Logistic Regression ============
		%

			fprintf('\nTraining One-vs-All Logistic Regression...\n')

			lambda = 3; % originally it was kept at 0.1
			[all_theta] = oneVsAll(X, y, num_labels, lambda);

			printf('The optimal theta values for all the 3 classes had been obtained ie. all_theta has been obtained. Its size is: ')
			size(all_theta)


			fprintf('Program NOT paused. Press enter to continue.\n');
			%pause;


		%% ================ Part 3: Predict for One-Vs-All ================

			pred = predictOneVsAll(all_theta, X);

			fprintf('\nTraining Set Accuracy: %f\n', mean(double(pred == y)) * 100);
			
			train = 0; % to allow it to enter the next block of code
	end

		
	if (train == 0)
				
		%% ================ Part 4: Guess for any other given input ================

			% Here we want to find to which class the given example image belongs
			% To do so, we find h for the image such that the image is multiplied with 
			% each class' trained theta (got from all_theta), and the class which outputs
			% the highest h, is the class to which it belongs
			
			hvec = zeros(num_labels, 1);
			
			printf('\n ... Loading Test Set ... \n')
			inX = load('C:/ml_pgms/wipro_ml/trainingSetMatrixEdit1/wiproRealTest1X.txt');
			inY = load('C:/ml_pgms/wipro_ml/trainingSetMatrixEdit1/wiproRealTest1Y.txt');
			
			printf('\n Size of the input loaded: ')
			size(inX)
			size(inY)
			
			%Pick any one of the external inputs loaded
			index = photoNumber;
			input = inX(index,:);
			%input = X(96,:);
			input = [1 input]; % need to add the column of 1 !!
			
							
			for i = 1:num_labels
				hvec(i) = sigmoid( input * all_theta(i,:)' );
			end
			
			%hvec 
			class = find( hvec==max(hvec) );
			
			printf('Predicted: %d \t', class)
			printf('Expected: %d', inY(index));
			%printf('The corresponding y value is given to be: ')
			%y(96)
			printf('\n');
	end
	
	if (train~=0 && train ~=1)
		printf('Enter 1 to train system again. 0 to use existent theta')
	end
%% =================	END		======================
end