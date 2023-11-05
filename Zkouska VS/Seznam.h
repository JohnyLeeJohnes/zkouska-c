#pragma once

typedef struct prvek{
	int number;
	struct prvek * next;
}prvek;

typedef struct spojseznam {
	struct prvek * start;
}spojseznam;

struct spojseznam* initSeznam(void);
void insertPrvek(int number, spojseznam * s);
void writeSeznam(spojseznam * s);
void freeMemorySeznam(spojseznam * s);
int isInSeznam(int number, spojseznam * s);
