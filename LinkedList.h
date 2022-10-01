#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinkedList LinkedList;

struct LinkedList {//Struct of LinkedList
	char* data;
	LinkedList *next;
};

//Statements of the functions:
void PrintList(LinkedList *);
LinkedList* BuildNode(char*);
LinkedList* addToStart(LinkedList *, char*);
LinkedList* FreeList(LinkedList *);
LinkedList* DeleteElement(LinkedList *, char*);
int isInList(LinkedList*, char*);
LinkedList* addToEND(LinkedList*, char*);

