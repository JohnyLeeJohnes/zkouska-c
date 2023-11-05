#include <stdlib.h>
#include <stdio.h>
#include "Seznam.h"

//Init main structure of list
spojseznam* initSeznam(void)
{
	spojseznam * spojsezn = (spojseznam *)(malloc(sizeof(spojseznam)));
	spojsezn->start = 0;

	return spojsezn;
}

//Insert element into list
void insertPrvek(int number, spojseznam* s)
{
	prvek * p = (prvek *)(malloc(sizeof(prvek)));
	p->next = 0;
	p->number = number;

	if(s->start == 0){
		s->start = p;
	}
	else{
		prvek * tmp;
		for(tmp = s->start; tmp->next != 0; tmp = tmp->next){}
		tmp->next = p;
	}
}

//Write elements of list into console -> debugging
void writeSeznam(spojseznam* s)
{
	prvek *tmp;

	for(tmp = s->start; tmp != 0; tmp = tmp->next)
	{
		printf("%d", tmp->number);
		if(tmp->next != 0){
			printf("->");
		}
	}
}

//Return bool -> is number is seznam
int isInSeznam(int number, spojseznam * s) 
{
	prvek *tmp;

	for (tmp = s->start; tmp != 0; tmp = tmp->next) {
		if (tmp->number == number) {
			return 1;
		}
	}
	
	return 0;
}

//Recursive free of each element
void freeMemory(prvek* s)
{
	if(s->next != 0){
		freeMemory(s->next);
	}
	free(s);
}

//Free mother of list and free each element
void freeMemorySeznam(spojseznam* s)
{
	if(s->start != 0){
		freeMemory(s->start);
		free(s);
	}
}
