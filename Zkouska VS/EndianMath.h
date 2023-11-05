#pragma once

//Main methods
char * sumNumbers(char * s1, char * s2);
char * sumRealNumbers(char * s1, char * s2);
char * multiplyNumbers(char * s1, char * s2);
char * multiplyRealNumbers(char * s1, char * s2);

//Help methods
void insertToString(char * source, char * target);
void swap(char ** s1, char ** s2);
int isLeftSmaller(char * str1, char * str2);
void insertSplit(char * str, char spliter, int position);
void removeChar(char * str, char spliter);