#pragma once
#include "Seznam.h"

typedef struct hashtableCell{
	char * key;
	int value;
	long code;
	struct hashtableCell * next;
}hashtableCell;

typedef struct hashtableList{
	struct hashtableCell * mother;
	int cellCount;
}hashtableList;

//Init methods
hashtableList * initTable();
void insertElementToHash(hashtableList * table, char * word);
void writeHash(hashtableList * s);

//Free memory method
void freeHashTable(hashtableList * table);
