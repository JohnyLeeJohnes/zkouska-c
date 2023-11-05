#include "HashMap.h"
#include "Seznam.h"
#include <stdlib.h>
#include <stdio.h>

//Generate hash code from primary number calculus
int genHashCode(char * word){
	long hashcode = 31;
	int i = 0;

	while(word[i]){
		hashcode *= 53 * (int)(word[i]);
		hashcode += 17;
		hashcode *= 31;
		i++;
	}

	return hashcode;
}

//Init mother structure of table
hashtableList * initTable(){
	hashtableList * table = (hashtableList *)(malloc(sizeof(hashtableList *)));
	table->mother = 0;
	table->cellCount = 0;

	return table;
}

//Insert word to list of hashwords -> generate hashtable
void insertElementToHash(hashtableList * table, char * word){
	hashtableCell * cell = (hashtableCell *)(malloc(sizeof(hashtableCell)));
	cell->key = word;
	cell->value = 1;
	cell->code = genHashCode(word);
	cell->next = 0;

	if(table->mother == 0){
		table->mother = cell;
	} else {
		hashtableCell * tmp;
		for(tmp = table->mother; tmp->next != 0; tmp = tmp->next)
		{
			if(tmp->code == cell->code){
				tmp->value++;
				free(cell->key);
				free(cell);
				return;
			}
		}
		tmp->next = cell;
	}
	table->cellCount++;
}

//Write hashtable to console -> debugging
void writeHash(hashtableList * s)
{
	hashtableCell * tmp;

	for(tmp = s->mother; tmp != 0; tmp = tmp->next)
	{
		printf("%s - %d", tmp->key, tmp->value);
		if(tmp->next != 0){
			printf("\n");
		}
	}
}


//--FREE MEMORY METHODS--

//Free memory of hash table elements
void freeHashTable(hashtableList * table)
{
	if(table->mother != 0)
	{
		hashtableCell * tmp;
		hashtableCell * now;
		for (tmp = table->mother; tmp != 0; 0)
		{
			now = tmp;
			tmp = tmp->next;
			free(now);
		}
	}
}
