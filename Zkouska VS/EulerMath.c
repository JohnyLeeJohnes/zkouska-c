#include <stdio.h>
#include <stdlib.h>
#include "EulerMath.h"
#include "EndianMath.h"
//H E L P  M E T H O D S

//Divide two small number
char ** smallDivision(char * n1, char * n2)
{
	char * tmps2 = (char *)malloc(sizeof(char) * (strlen(n2) + 2));
	char * tmpSum = (char *)malloc(sizeof(char) * (strlen(n2) + 2));
	char * value = (char *)malloc(sizeof(char) * (strlen(n1) + 2));
	char * tmp = (char *)malloc(sizeof(char) * (strlen(n1) + 2));
	char * itterations = (char *)malloc(sizeof(char) * (strlen(n1) + 2));
	char * tmpitt = 0;

	insertToString(n1, value); //Bigger
	insertToString(n2, tmps2); //Smaller
	insertToString(n2, tmpSum); // Just of while
	insertToString("0", itterations); //Init itterations to zero
	insertSplit(tmps2, '-', strlen(n2)); //Add negation

	while (!isLeftSmaller(value, tmpSum))
	{
		//In loop -> minus number
		tmp = sumNumbers(value, tmps2);
		insertToString(tmp, value);
		free(tmp);

		//Count itteration
		tmpitt = sumNumbers(itterations, "1");
		insertToString(tmpitt, itterations);
		free(tmpitt);
	}

	free(tmps2);
	free(tmpSum);

	//Create output
	char ** output = (char **)malloc(sizeof(char*) * 2);
	output[0] = itterations;
	output[1] = value;

	return output;
}

//Divison of two large number -> part division
char * partDivision(char * n1, char * n2) 
{
	char * tmps1 = (char *)malloc(sizeof(char) * (strlen(n1) + 2));
	char * tmps2 = (char *)malloc(sizeof(char) * (strlen(n2) + 2));
	char * output = (char *)malloc(sizeof(char) * (strlen(n1) + 2));
	char * tmpOutput = (char *)malloc(sizeof(char) * (strlen(n1) + 2));
	char ** div = 0;

	insertToString(n1, tmps1); //Larger
	insertToString(n2, tmps2); //Smaller
	insertToString("0", tmpOutput);

	int lenOutput = 0;
	int lenTmp = 0;
	int lenght = 0;
	int firstStart = 1;

	while (lenTmp < strlen(tmps1))
	{
		//Create number for division
		while (isLeftSmaller(tmpOutput, tmps2))
		{
			//Remove zeros from start
			if (tmpOutput[0] == '0') {
				tmpOutput[0] = '\0';
				lenght = 0;
			}
			//Creating the number -> joining
			tmpOutput[lenght++] = tmps1[lenTmp++];
			tmpOutput[lenght] = '\0';

			if (!firstStart && isLeftSmaller(tmpOutput, tmps2))
				output[lenOutput++] = '0';

			//If there are zeros -> add them to the final number
			if (tmpOutput[0] == '0')
			{
				if (lenTmp >= strlen(tmps1))
					break;
				else 
					continue;
			}
		}

		//Stop loop if adding zeros at the end
		if (lenTmp >= strlen(tmps1) && tmpOutput[0] == '0') 
			break;

		//Load values from small division method
		div = smallDivision(tmpOutput, tmps2);

		//Insert values into local variables
		output[lenOutput++] = div[0][0];
		insertToString(div[1], tmpOutput);
		lenght = strlen(tmpOutput);

		//Set itteration check to 1
		firstStart = 0;

		free(div[0]);
		free(div[1]);
		free(div);
	}

	output[lenOutput++] = '\0';

	free(tmps1);
	free(tmps2);
	free(tmpOutput);

	return output;
}

//Calculate factorial of number in param
char * calculateFactorial(char * number)
{
	char * factorial = (char *)malloc(sizeof(char)*(strlen(number) + 2));
	char * num = (char *)malloc(sizeof(char)*(strlen(number) + 2));
	char * tmpFact = 0;
	char * tmp = 0;

	//If factiorial of zero
	if (number == "0") 
	{
		insertToString("1", factorial);
		return factorial;
	}

	//Doing the first itteration with number constant
	insertToString(number, factorial);
	tmp = sumNumbers(number, "-1");
	insertToString(tmp, num);
	free(tmp);

	while (num[0] != '\0')
	{
		//Calculate factorial
		tmpFact = multiplyNumbers(num, factorial);
		free(factorial);
		factorial = (char *)malloc(sizeof(char)*(strlen(tmpFact) + 2));
		insertToString(tmpFact, factorial);
		free(tmpFact);

		//Number - 1
		tmp = sumNumbers(num, "-1");
		insertToString(tmp, num);
		free(tmp);
	}
	free(num);

	return factorial;
}

//Calculate division as real number -> on n (precision) numbers
char * calculateRealDivision(char * upper, char * lower, int precision)
{
	//Alocate memory for strings
	char * output = (char *)malloc(sizeof(char) * (precision + 4)); //Zero, comma and end of string
	char * strUp = (char *)malloc(sizeof(char) * (strlen(upper) + 2));
	char * tmpUp = (char *)malloc(sizeof(char) * (strlen(upper) + 2));
	char * strDown = (char *)malloc(sizeof(char) * (strlen(lower) + 2));
	char * tmpDown = (char *)malloc(sizeof(char) * (strlen(lower) + 2));
	int lenght = 0;
	int wasZero = 0;
	int i, itterations, len;

	//Init allocated memory
	insertToString(upper, strUp);
	insertToString(lower, strDown);
	insertToString(lower, tmpDown);
	insertSplit(tmpDown, '-', strlen(tmpDown));

	//Init output of euler
	output[lenght++] = '2';
	output[lenght++] = ',';

	//Cycle for each precision
	for (i = 0; i < precision; i++)
	{
		itterations = 0; 

		//Insert zero for dividing
		if (wasZero) {
			len = strlen(tmpUp);
			tmpUp[len++] = '0';
			tmpUp[len++] = '\0';
			wasZero = 0;
		}
		else
		{
			insertToString(strUp, tmpUp);
			len = strlen(strUp);
			tmpUp[len++] = '0';
			tmpUp[len++] = '\0';
		}


		while (!isLeftSmaller(tmpUp,strDown))
		{
			//Calculate minus
			free(strUp);
			strUp = sumNumbers(tmpUp, tmpDown);
			insertToString(strUp, tmpUp);

			itterations++;
		}

		//Insert number of itterations
		output[lenght++] = itterations + '0';

		if (itterations == 0)
			wasZero = 1;
	}

	output[lenght++] = '\0';

	free(strUp);
	free(strDown);
	free(tmpUp);
	free(tmpDown);

	return output;
}

//Calculate euler number on n-precision
char * calculateEuler(int precision) 
{
	char ** zlomky = (char**)malloc(sizeof(char *) * (precision + 3));
	char * eulerNumber = 0; //Final number
	char * maxUp = 0; //Upper part of number -> for division
	char * maxDown = 0; //Lower part of number -> for division
	char * tmp = 0;
	char * tmpSum = 0;
	char itteration[100];
	int i;

	//Init list of factorials
	for (i = 0; i < precision; i++)
	{
		if (i == 0) 
		{
			zlomky[i] = calculateFactorial("2");
			zlomky[i+1] = calculateFactorial("3");
			zlomky[i+2] = calculateFactorial("4");
		}
		else
		{
			sprintf(itteration, "%d", i + 4);
			zlomky[i+2] = calculateFactorial(itteration);
		}
	}

	//Allocate memory for up and init down
	maxDown = zlomky[precision + 1];
	maxUp = (char *)malloc(sizeof(char) * strlen(maxDown) + 2);
	
	for (i = 0; i <= precision; i++) 
	{
		//Division of factorials
		tmp = partDivision(maxDown, zlomky[i]);
		free(zlomky[i]);
		//Sum divisions
		if (!tmpSum)
			tmpSum = sumNumbers("0", tmp);
		else
			tmpSum = sumNumbers(maxUp, tmp);

		//Copy sum
		insertToString(tmpSum, maxUp);

		free(tmpSum);
		free(tmp);
	}

	//Add last one to max up
	tmpSum = sumNumbers("1", maxUp);
	insertToString(tmpSum, maxUp);

	//Calculate euler number on precision
	eulerNumber = calculateRealDivision(maxUp, maxDown, precision);

	free(maxUp);
	free(maxDown);
	free(zlomky);
	free(tmpSum);

	return eulerNumber;
}
