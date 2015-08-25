function none = testMultiWrong(type)
%Lists the images of the test set that are being predicted wrong.

%% =======	Essentials of wiproTrain	==============


	input_layer_size  = 400;  	% 20x20 Input Images of Digits
	num_labels = 3;          	% 10 labels, from 1 to 10   
								% (note that we have mapped "0" to label 10)

		%% =========== Part 1: Loading and Visualizing Data =============
		%

			% Load Training Data
			fprintf('Loading and NOT Visualizing Data ...\n')

			X = load('C:/ml_pgms/wipro_ml/trainingSetMatrix/wiproXData.txt');
			m = size(X, 1);

			y1 = load('C:/ml_pgms/wipro_ml/trainingSetMatrix/wiproY1Data.txt');
			y2 = load('C:/ml_pgms/wipro_ml/trainingSetMatrix/wiproY2Data.txt');
			y3 = load('C:/ml_pgms/wipro_ml/trainingSetMatrix/wiproY3Data.txt');

			y = [y1;y2;y3];

			printf('Sizes of X and y are:');
			size(X)
			size(y)


			fprintf('Program NOT paused. Press enter to continue.\n');
			%pause;

		%% ============ Part 2: Vectorize Logistic Regression ============
		%

			fprintf('\nTraining One-vs-All Logistic Regression...\n')

			lambda = 25; % originally it was kept at 0.1
			[all_theta] = oneVsAll(X, y, num_labels, lambda);

			printf('The optimal theta values for all the 3 classes had been obtained ie. all_theta has been obtained. Its size is: ')
			size(all_theta)


			fprintf('Program NOT paused. Press enter to continue.\n');
			%pause;


		%% ================ Part 3: Predict for One-Vs-All ================

			pred = predictOneVsAll(all_theta, X);

			fprintf('\nTraining Set Accuracy: %f\n', mean(double(pred == y)) * 100);
			
			train = 0; % to allow it to enter the next block of code
				
	%% ================ Part 4: Guess for any other given input ================

		% Here we want to find to which class the given example image belongs
		% To do so, we find h for the image such that the image is multiplied with 
		% each class' trained theta (got from all_theta), and the class which outputs
		% the highest h, is the class to which it belongs
		
		hvec = zeros(num_labels, 1);
		
		
		printf('\n ... Loading Test Set ... \n')
		inputX = load('C:/ml_pgms/wipro_ml/testset1/mltestX.txt');
		inputY = load('C:/ml_pgms/wipro_ml/testset1/mltestY.txt');
				
		size(inputX)
		size(inputY)
		pause;
		
		inputX = [ones(size(inputX, 1),1) inputX]; % need to add the column of 1 !!
		
		all_predict = size(inputX, 1); %size = no. of input training eg
			%stores the class no to which each test ex has been predicted to 
		
		for i = 1:size(inputX,1) %cycle through all training egs
			
			for num = 1:num_labels %generate the probab for the ith class to occur in any of the 1,2 or 3  class
				
				hvec(num) = sigmoid( inputX(i,:) * all_theta(num,:)' );
				%ith example multipled by the optimal theta for each of the classes
			end
			
			class = find( hvec==max(hvec) );
			all_predict(i) = class;
		end
	
	
	
	noWrong = -1;
	if (type == 1)
		wrongCnt =0;
		index = [-1 -1 -1];
		for j = 1:length(all_predict)
			if (all_predict(j) ~= inputY(j))
				index = [index; [j-1, all_predict(j), inputY(j)] ]; % store the index, predicted o/p and expected o/p
				% The j-1 stores the image nos...0 to n-1
				wrongCnt=wrongCnt+1;
			end
		end

	fprintf('\n Number of wrong predictions are: %d \n', wrongCnt)
	fprintf('\n The wrongly predicted images are: \n')
	index
	noWrong = length(index);
	end
	

	if (type == 2)
		index = [-1 -1 -1];
		for j = 1:length(all_predict)
			
			% displayed for all egs
			index = [index; [j-1, all_predict(j), inputY(j),] ]; %predicted o/p, expected o/p
				%The j-1 stores the image nos ... 0 to n-1
		end

	fprintf('\n predicted \t expected \n')
	index
	noWrong = length(index);
	end

	
	printf('Test Set Accuracy is: ');
	100 - (noWrong/length(inputY))*100
	printf('\n');
	
	
%% =================	END		======================
end