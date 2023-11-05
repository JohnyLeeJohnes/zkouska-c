//System includes
#include <stdio.h>
#include <stdlib.h>

//Mine includes
#include "FileImport.h"
#include "Seznam.h"
#include "HashMap.h"
#include "Sorting.h"
#include "EndianMath.h"
#include "EulerMath.h"

#define FilePath "C:\\Users\\Johny\\Desktop\\bible.txt"

void useEuler(int argc, char ** argv);
void useEndianMethod(int argc, char ** argv, char * (*function)(char *, char *));
void useOccurrenceSearch(int argc, char ** argv);

//Program starting point
int main(int argc, char ** argv)
{
	setbuf(stdout, NULL);

	//useEuler(argc, argv);
	//useOccurrenceSearch(argc, argv);
	//useEndianMethod(argc, argv, *multiplyRealNumbers);

	return 0;
}

//Use method -> calculation of euler number to precision
void useEuler(int argc, char ** argv) 
{
	if (argc == 2 && atoi(argv[1]) >= 1)
	{
		char * e = calculateEuler(atoi(argv[1]));
		printf("%s", e);
		free(e);
	}
	else
		printf("%s", "Too many, too few or invalid arguments!");
}

//Use method -> EndianMath
void useEndianMethod(int argc, char ** argv, char * (*function)(char *, char *)) 
{
	int i;
	char * string = 0;
	for (i = 1; i < argc - 1; i++)
	{
		if (i == 1)
			string = function(argv[i], argv[i + 1]);
		else
			string = function(string, argv[i + 1]);
	}

	if (string != 0)
	{
		printf("%s\n", string);
		free(string);
	}
}

//Use most occurred words in text method -> input how many words
void useOccurrenceSearch(int argc, char ** argv) {
	hashtableList * hashtable = initTable();
	fillArrayFromPath(FilePath, hashtable);

	if (argc > 1)
		occurrenceBiggest(hashtable, atoi(argv[1]));
	else
		occurrenceBiggest(hashtable, 1);

	freeHashTable(hashtable);
}
