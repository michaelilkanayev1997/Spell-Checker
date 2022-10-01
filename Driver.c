/*Homework 4:
Michael ilkanayev, id : 318216678
Vladimir davidzon, id : 317648632
*/
#define _CRT_SECURE_NO_WARNINGS
#include "WordSpellingChecker.h"

void printSpellingSuggestions(SpellingSuggestion* spellingSuggestions) { //A function that prints the Spelling Suggestions
	int i = 0;
	while (spellingSuggestions[i].originalWord != NULL) { //Run on all the wrong words that were found in the text
		//printing the wrong words in the text:
		printf("\nThe word ' %s ' was misspelled.Did you mean :\n", spellingSuggestions[i].originalWord);

		if (spellingSuggestions[i].suggestions != NULL) { //Enter if there are suggestions and print them
			PrintList(spellingSuggestions[i].suggestions);
		}
		else {//No suggestions were found
			printf("\n No suggestions found for this word.\n"); 
		}
		i++;
	}
}

int parseWordsToTable(char* path, HashTable* ht) {//A function that puts all the words in the path inside the table
	FILE* fp = fopen(path, "r");
	if (fp == NULL) // check if fopen() is successful 
		return 0; 

	int Line=0;
	while(!feof(fp)) { //loop until end of file
		char* line = (char*)malloc(50); // allocate enough elements 
		if (line == NULL)
			exit("Not Enough Memory!");

		fgets(line, 50, fp); //get word from the path
		strtok(line,"\n"); //removing '\n'

		int result = insert(ht,line); //inserting the word inside the table

		if (result == 0) { //if the word exists in the table or if the word is NULL return 0
			printf("Error inserting word\n");
			return 0;
		}
		Line++;
	}
	fclose(fp); //close opened file 
	return 1; //return 1 if the word entered the table 
}

SpellingSuggestion* spellingCheck(char* text) { //A function that checks spelling and saves suggestions
	if (text == NULL || text == '\0') //checking if the text is good
		return NULL;

	HashTable* table = initTable(4,1); //creating table 
	
	parseWordsToTable("C:/Users/magic/OneDrive/Desktop/text/dictionary.txt",table); //parse all Words To Table
	int i = 0 ,flag=0;
	// Extract the first token
	char* token = strtok(text," ");
	// loop through the string to extract all other tokens
	SpellingSuggestion* Spelling = (SpellingSuggestion*)malloc(sizeof(SpellingSuggestion) *50);
	if (Spelling == NULL) {
		printf("malloc failed\n");
		exit(-1);
	}
	for (int j = 0; j < 50; j++) { //initialization 
		Spelling[j].suggestions = NULL;
		Spelling[j].originalWord = NULL;
	}
	
	while (token != NULL) {

		if (isWordInDictionary(table, token) == 0) { //checking if the word exists in the table dictionary
			flag = 1;

			Spelling[i].originalWord = token;
			Spelling[i].suggestions = getWordSuggestions(table,token); //saving all the suggestions 
			i++;
		}
		
		token = strtok(NULL," ");
	}
	if (flag == 0) //If there are no errors at all ,return an empty string
		return " ";

	Freetable(table); //free table 
	return Spelling; //return all the SpellingSuggestion
}

int main(){
	char text[] = "iam afraid youare about to become teh immexdiate pst president of teh eing alive club ha ha glados";
	SpellingSuggestion* spellingSuggestions = spellingCheck(text); //sending text to spellingCheck function
	printSpellingSuggestions(spellingSuggestions); //sending spellingSuggestions to print function

	free(spellingSuggestions); //free spellingSuggestions
	return 0;  //end
}


