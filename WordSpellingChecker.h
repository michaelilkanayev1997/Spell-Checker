#include "HashTable.h"

typedef struct SpellingSuggestion SpellingSuggestion;

struct SpellingSuggestion {  //Struct of SpellingSuggestion
	char* originalWord;
	LinkedList  * suggestions;
	SpellingSuggestion* next;
};
//Statements of the functions:
int isWordInDictionary(HashTable* dictionaryTable, char* word);
LinkedList* addSpaceCheck(HashTable* dictionaryTable, char* word);
LinkedList* replaceCharacterCheck(HashTable* dictionaryTable, char* word);
LinkedList* deleteCharacterCheck(HashTable* dictionaryTable, char* word);
LinkedList* addCharacterCheck(HashTable* dictionaryTable, char* word);
LinkedList* switchAdjacentCharacterCheck(HashTable* dictionaryTable, char* word);
LinkedList* getWordSuggestions(HashTable* dictionaryTable, char* word);

//New function:
LinkedList* Check_for_Duplicates(LinkedList* list);
int Check_IF_equal(LinkedList* list, char* str);
LinkedList* Connect_two_lists(LinkedList* list1, LinkedList* list2);