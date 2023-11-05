#include "FileImport.h"
#include "HashMap.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//Read from file -> Insert each word into hashtable
void read_words (FILE * file, hashtableList * slova)
{
	char ch[2];
	char * tmp = (char*)(malloc(sizeof(char)*1024));
	char * word = 0;
	size_t n = 0;
	int inserted = 0;
	int i = 0;

	fseek(file, 0, SEEK_SET);
	fread(ch,1,1,file);

	while(!feof(file)){
		if(((char)ch[0]>='a' && (char)ch[0]<='z') || ((char)ch[0]>='A' && (char)ch[0]<='Z'))
		{
			tmp[n++] = (char) ch[0];
			inserted = 0;
		}
		else if(inserted == 0)
		{
			word = (char*)malloc(sizeof(char)*(n + 1));
			word[n] = '\0';
			for(i = 0; i < n; i++)
			{
				word[i] = tolower(tmp[i]);
				tmp[i] = '\0';
			}
			insertElementToHash(slova, word);
			n = 0;
			inserted = 1;
		}
		fread(ch,1,1,file);
	}
	if(inserted == 0 && tmp != '\0')
	{
		word = (char*)malloc(sizeof(char)*(n + 1));
		word[n] = '\0';
		for(i = 0; i < n; i++)
		{
			word[i] = tolower(tmp[i]);
			tmp[i] = '\0';
		}
		insertElementToHash(slova, word);
	}

	fclose(file);
	free(tmp);
}

//Init structure file from filepath
void fillArrayFromPath(char * path, hashtableList * slova)
{
	FILE * file = fopen(path,"r");

	if (file == NULL)
		return;

	read_words(file,slova);
}
