#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EndianMath.h"

//H E L P  M E T H O D S

//Swap values
void swap(char ** s1, char ** s2)
{
	char * tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

//Reverse values
void reverse(char * str) 
{
	int i;
	char tmp;
	for (i = 0; i < strlen(str); i++)
	{
		int index = strlen(str) - i - 1;
		if (i >= index) break;
		tmp = str[i];
		str[i] = str[index];
		str[index] = tmp;
	}
}

//Insert source chars to target
void insertToString(char * source, char * target) 
{
	int i;
	for (i = 0; i <= strlen(source); i++) {
		target[i] = source[i];
	}
}

//Multiply endian number with single digit number
char * multiplyNumbersOneDigit(char * s1, char s2)
{
	char * tmps1 = (char*)malloc(sizeof(char)*(strlen(s1) + 2));

	insertToString(s1, tmps1);
	reverse(tmps1);

	int len1 = strlen(tmps1);
	char * str = (char*)malloc(sizeof(char)*(len1 + 2));

	int i;
	int carry = 0;
	int lenght = 0;

	for (i = 0; i < len1; i++)
	{
		int sum = (((tmps1[i] - '0') * (s2 - '0')) + carry);
		str[lenght] = (char)(sum % 10 + '0');
		carry = sum / 10;
		lenght++;
	}

	if (carry)
	{
		str[lenght] = (char)(carry + '0');
		lenght++;
		carry = 0;
	}

	str[lenght] = '\0';
	reverse(str);

	free(tmps1);

	return str;
}

//Return number of numbers after spliter
int countAfterSplit(char * str, char ch)
{
	int lenght = 0;
	int isReal = 0;
	int i;

	for (i = 0; i < strlen(str); i++)
	{
		if (isReal)
			lenght++;
		else
			if (str[i] == ch || str[i] == ch)
				isReal = 1;
	}

	return lenght;
}

//Insert comma to string on position
void insertSplit(char * str, char spliter, int position)
{
	reverse(str);

	char ch = spliter;
	int i;

	for (i = position; i < strlen(str); i++)
	{
		if (i == position)
		{
			ch = str[i];
			str[i] = spliter;
		}
		else
		{
			char tmp = str[i];
			str[i] = ch;
			ch = tmp;
		}
	}
	int lenght = strlen(str);

	str[lenght++] = ch;
	str[lenght++] = '\0';

	reverse(str);
}

//Remove char from string
void removeChar(char * str, char spliter)
{
	int shift = 0;
	int i;

	for (i = 0; i < strlen(str); i++)
	{
		if (shift)
			str[i - 1] = str[i];
		else
			if (str[i] == spliter || str[i] == spliter)
				shift = 1;
	}

	if(shift)
		str[strlen(str) - 1] = '\0';
}

//If left number is smaller
int isLeftSmaller(char * str1, char * str2) 
{
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	int i;

	if (len1 < len2)
		return 1;
	if (len1 == len2)
	{
		for (i = 0; i < len1; i++)
		{
			if (str1[i] > str2[i])
				return 0;
			if (str1[i] < str2[i])
				return 1;
		}
	}

	return 0;
}

// M A I N  M E T H O D S

//Sum two endian numbers
char * sumNumbers(char * s1, char * s2)
{
	//Allocate memory
	char * tmps1 = (char*)malloc(sizeof(char)*(strlen(s1) + 2));
	char * tmps2 = (char*)malloc(sizeof(char)*(strlen(s2) + 2));
	int addNegation = 0;
	int negative = 0;

	//Copy string to memory
	insertToString(s1, tmps1);
	insertToString(s2, tmps2);

	//If negative number -> later adding negation
	if ((tmps1[0] == '-' && tmps2[0] != '-'))
		negative = 1;
	if ((tmps1[0] != '-' && tmps2[0] == '-'))
		negative = 2;
	if (tmps1[0] == '-' && tmps2[0] == '-')
		addNegation = 1;

	//Remove negation -> if exists
	removeChar(tmps1, '-');
	removeChar(tmps2, '-');

	//Swaping for better counting
	if (!negative)
	{
		if (strlen(tmps1) > strlen(tmps2))
			swap(&tmps1, &tmps2);
	}
	else
	{
		if (!isLeftSmaller(tmps1, tmps2)) 
		{
			if (negative == 1)
				addNegation = 1;
			swap(&tmps1, &tmps2);
		}
		else
		{
			if (negative == 2)
				addNegation = 1;
		}
	}

	//Reverse strings to help calculating
	reverse(tmps1);
	reverse(tmps2);

	//Init calculating variables
	int len1 = strlen(tmps1);
	int len2 = strlen(tmps2);
	char * str = (char*)malloc(sizeof(char)*(len1 + len2 + 2));
	int carry = 0;
	int lenght = 0;
	int i;

	//If negative -> subtraction
	if (negative)
	{
		//Differencing first part
		for (i = 0; i < len1; i++)
		{
			int value = ((tmps2[i] - '0') - (tmps1[i] - '0') - carry);
			carry = 0;
			if (value < 0)
			{
				value += 10;
				carry = 1;
			}
			str[lenght++] = (char)(value + '0');
		}
		//Adding rest of number
		for (i = len1; i < len2; i++)
		{
			int value = ((tmps2[i] - '0') - carry);
			carry = 0;
			if (value < 0)
			{
				value += 10;
				carry = 1;
			}
			str[lenght++] = (char)(value + '0');
		}
	}
	else
	{
		//Summing first part
		for (i = 0; i < len1; i++)
		{
			int sum = ((tmps1[i] - '0') + (tmps2[i] - '0') + carry);
			str[lenght] = (char)(sum % 10 + '0');
			carry = sum / 10;
			lenght++;
		}
		//Adding part of longer number + carry
		for (i = len1; i < len2; i++)
		{
			int sum = ((tmps2[i] - '0') + carry);
			str[lenght] = (char)(sum % 10 + '0');
			carry = sum / 10;
			lenght++;
		}
		//Adding carry
		if (carry) 
		{
			str[lenght] = (char)(carry + '0');
			lenght++;
		}
	}

	//Insert end -> reverse
	str[lenght] = '\0';
	reverse(str);

	//Remove zeros at the start
	for (i = 0; i < strlen(str); i++)
	{
		if (str[0] == '0')
			removeChar(str, '0');
		else
			break;
	}

	//Insert minus if negative sum
	if (addNegation)
		insertSplit(str, '-', strlen(str));

	free(tmps1);
	free(tmps2);

	return str;
}

//Sum two real endian numbers
char * sumRealNumbers(char * s1, char * s2)
{
	//Allocate memory for strings
	char * tmps1 = (char *)malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 2));
	char * tmps2 = (char *)malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 2));

	//Insert data to memory
	insertToString(s1, tmps1);
	insertToString(s2, tmps2);

	//Swap tmps for better counting
	if (countAfterSplit(tmps1, ',') > countAfterSplit(tmps2, ','))
		swap(&tmps1, &tmps2);

	//Count number of skipped number before spliter	
	int minRealLenght = countAfterSplit(tmps1, ',');
	int maxRealLenght = countAfterSplit(tmps2, ',');

	//Add remaining zeros after split
	int lenght = strlen(tmps1);
	for (int i = minRealLenght; i < maxRealLenght; i++)
		tmps1[lenght++] = '0';
	tmps1[lenght] = '\0';

	//Remove split from strings
	removeChar(tmps1, ',');
	removeChar(tmps2, ',');

	//Multiply both numbers
	char * output = sumNumbers(tmps1, tmps2);

	//Insert comma
	insertSplit(output, ',', maxRealLenght);

	//Insert zero in special cases
	if (output[0] == ',')
		insertSplit(output, '0', strlen(output));
	if (output[0] == '-' && output[1] == ',')
		insertSplit(output, '0', strlen(output)-1);


	return output;
}

//Multiply two endian numbers
char * multiplyNumbers(char * s1, char * s2) 
{
	//Allocate memory for strings
	char * tmps1 = (char*)malloc(sizeof(char)*(strlen(s1) + 2));
	char * tmps2 = (char*)malloc(sizeof(char)*(strlen(s2) + 2));
	int negative = 0;

	//Insert to memory
	insertToString(s1, tmps1);
	insertToString(s2, tmps2);

	//Swap position if tmps1 > tmps2
	if (strlen(tmps1) > strlen(tmps2))
		swap(&tmps1, &tmps2);

	//Remove negation -> if exists
	if ((tmps1[0] == '-' && tmps2[0] != '-') || (tmps1[0] != '-' && tmps2[0] == '-'))
		negative = 1;

	//Remove negation -> if exists
	removeChar(tmps1, '-');
	removeChar(tmps2, '-');

	//Init variables before multiply loop
	int len1 = strlen(tmps1);
	int len2 = strlen(tmps2);
	int i;
	char * output = (char*)malloc(sizeof(char)*(len1 + len2 + 2));
	char * str = 0; //Alokuje se v onedigit

	//Loop -> insert multiplying for each digit into output -> then sum them
	for (i = 0; i < len1; i++)
	{
		if (str != 0) 
			free(str);
		str = multiplyNumbersOneDigit(tmps2, tmps1[i]);

		if (i == 0) 
		{
			insertToString(str, output);

			if ((i + 1) == len1)
				output[strlen(str)] = '\0';
			else {
				output[strlen(str)] = '0';
				output[strlen(str) + 1] = '\0';
			}
		}
		else
		{
			char * tmp = sumNumbers(str, output);
			insertToString(tmp, output);

			if ((i + 1) == len1) 
				output[strlen(tmp)] = '\0';
			else {
				output[strlen(tmp)] = '0';
				output[strlen(tmp) + 1] = '\0';
			}
			
			free(tmp);
		}
	}

	//Insert minus to the start
	if (negative)
		insertSplit(output,'-',strlen(output));

	return output;
}

//Multiply two real endian numbers
char * multiplyRealNumbers(char * s1, char * s2) 
{
	//Allocate memory for strings
	char * tmps1 = (char *)malloc(sizeof(char) * (strlen(s1) + 2));
	char * tmps2 = (char *)malloc(sizeof(char) * (strlen(s2) + 2));
	int realLenght = 0;

	//Insert data to memory
	insertToString(s1, tmps1);
	insertToString(s2, tmps2);

	//Calculate number of real numbers after split
	realLenght += countAfterSplit(tmps1, ',');
	realLenght += countAfterSplit(tmps2, ',');

	//Remove split from strings
	removeChar(tmps1, ',');
	removeChar(tmps2, ',');

	//Multiply both numbers
	char * output = multiplyNumbers(tmps1, tmps2);

	//Insert comma
	insertSplit(output, ',', realLenght);

	//Insert zero in special cases
	if (output[0] == ',')
		insertSplit(output, '0', strlen(output));
	if (output[0] == '-' && output[1] == ',')
		insertSplit(output, '0', strlen(output) - 1);

	return output;
}
