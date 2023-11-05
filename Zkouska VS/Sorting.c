#include <stdio.h>
#include "Sorting.h"
#include "Seznam.h"
#include "HashMap.h"

//Get biggest element of hashtable -> biggest value
hashtableCell * biggestNumber(hashtableList * list, hashtableCell * after, spojseznam * seznam) 
{
	hashtableCell * tmp;
	hashtableCell * tmpbig = 0;

	for (tmp = list->mother; tmp != 0; tmp = tmp->next) {
		if (tmpbig == 0) {
			if (after) {
				if (tmp->code == after->code) continue;
			} 
			tmpbig = tmp;
		}

		if (!after) {
			if ((tmp->value >= tmpbig->value) && (tmp->code != tmpbig->code)) {
				tmpbig = tmp;
			}
		}
		else {
			if ((tmp->value >= tmpbig->value && tmp->value <= after->value)){
				if (!isInSeznam(tmp->code, seznam)) {
						tmpbig = tmp;
				}
			}
		}
	}

	return tmpbig;
}

//Get n elements of hashtable -> with biggest value
void occurrenceBiggest(hashtableList * list, int n)
{
	hashtableCell * cell = 0;
	spojseznam * seznam = initSeznam();
	int i;

	if (n > list->cellCount-1) {
		printf("Too many occurrences required!");
		exit(1);
	}

	for (i = 0; i < n; i++)
	{
		if (i == 0) {
			cell = biggestNumber(list, 0, 0);
			insertPrvek(cell->code, seznam);
		}
		else{
			cell = biggestNumber(list, cell, seznam);
			insertPrvek(cell->code, seznam);
		}
		printf("%s - %d\n", cell->key, cell->value);
	}

	freeMemorySeznam(seznam);
}
