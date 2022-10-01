#define _CRT_SECURE_NO_WARNINGS
#include "WordSpellingChecker.h"

int isWordInDictionary(HashTable* dictionaryTable, char* word){//A function that checks if the word is in the dictionary
	int index;
	index = hash(word, dictionaryTable); //checks the index of the word inside the Hash table 
	LinkedList* temp = dictionaryTable->hashTable[index].chain;

	if (word != NULL) { //run until the end of the chain

		while (temp != NULL) {
			if ((strcmp(word,temp->data))==0) //checking if the word is qaual to the data in the dictionary
				return 1; //if yes return 1

			temp = temp->next;
		}
	}
	return 0; // if the word don't exists in the table return 0
}

LinkedList* addSpaceCheck(HashTable* dictionaryTable, char* word){//A function that splits the word and checks if they exsits in the dictionary
	char str1[30], str2[30],str3[30];
	int j = 0,k,t,r;
	LinkedList* sortedList = NULL;
	
	for (int i = 1; i < strlen(word); i++) {  //Saves each time the beginning of the word
		k = 0;
		t = i;
		for (j = 0; j < i; j++) {

			str1[j] = word[j];
		}
		str1[j] = '\0';

		for (j = i; j < strlen(word); j++) { //Saves each time the end of the word

			str2[k++] = word[t++];
		}
		str2[k] = '\0';

		//Checks if str1 and str2 (The split words) exist in the dictionary
		if ((isWordInDictionary(dictionaryTable, str1) == 1) && (isWordInDictionary(dictionaryTable, str2) == 1)) {
			//Connects the 2 split words together with a space between them:
			for (t = 0; t < strlen(str1); t++) { 
				str3[t] = str1[t];
			}
			str3[t++] =' ';
			for (r=0 ; r < strlen(str2); r++) {
				str3[t++] = str2[r];
			}
			str3[t] = '\0';
			//Dynamically creating arr to insert the word in the list
			char* arr = (char*)malloc(sizeof(char) * 15); 
			if (arr == NULL) {
				printf("malloc failed\n");
				exit(-1);
			}
			if (arr) {
				strcpy(arr, str3); // copy str3 to arr 
				sortedList = addToEND(sortedList, arr); //adding the word to the end of the list 
			}
		}
	}
	return sortedList; //returns the list 
}

LinkedList* replaceCharacterCheck(HashTable* dictionaryTable, char* word){ //A function that replaces each letter in a word from a to z and checks if it is in the dictionary
	char temp[30]= "";
	strcpy(temp, word);

	LinkedList* list = NULL;
	int j,i;
	for (i = 0; i < strlen(word); i++) { //run on all the letters in a word
		
		for (int letter=97; letter < 123; letter++) { //run on all the letters from: 'a' to 'z'
			
			temp[i] = letter;
			//checking if the word exists in the dictionary and that the word and the new word(temp) are not equal
			if (isWordInDictionary(dictionaryTable, temp) == 1 && strcmp(temp, word) != 0) {
				char* arr = (char*)malloc(sizeof(char)* 15);//Dynamically creating arr to insert the word in the list
				if (arr == NULL) {
					printf("malloc failed\n");
					exit(-1);
				}
				if (arr) {
					strcpy(arr, temp); //copy temp to arr
					list = addToEND(list, arr); //add arr to list 
				}
			}
		}
		strcpy(temp, word);
	}
	return list; //return list
}

LinkedList* deleteCharacterCheck(HashTable* dictionaryTable, char* word) {//Deletes letters from the word and checks if the new word is in the dictionary
	char temp[30] = "";
	strcpy(temp, word);
	LinkedList* list = NULL;

	int j, i,k;
	for (i = 0; i < strlen(word); i++) { //Deletes letters from the word 
		k = 0;
		for (j = 0; j < strlen(word); j++) {
			if (i != j) {
				temp[k++] = temp[j];
			}
		}
		temp[k] = '\0';

		if (isWordInDictionary(dictionaryTable, temp) == 1) { //checks if the new word is in the dictionary 
			char* arr = (char*)malloc(sizeof(char) * 15);//Dynamically creating arr to insert the word in the list
			if (arr == NULL) {
				printf("malloc failed\n");
				exit(-1);
			}
			if (arr) {
				strcpy(arr, temp);//copy temp to arr
				list = addToEND(list, arr);//add arr to list 
			}
		}
		strcpy(temp, word);
	}
	return list; //return list
}

LinkedList* switchAdjacentCharacterCheck(HashTable* dictionaryTable, char* word){//Swaps adjacent letters and checks if it is in the dictionary
	char temp[30] = "",x;
	strcpy(temp, word);
	LinkedList* list = NULL;

	for (int i = 0; i < strlen(word)-1; i++) { 
		//Swaps adjacent letters in the word
		x = temp[i]; 
		temp[i] = temp[i + 1];
		temp[i + 1] = x;
		//checking if the word exists in the dictionary and that the word and the new word(temp) are not equal
		if (isWordInDictionary(dictionaryTable, temp) == 1 && strcmp(temp, word) != 0) {
			char* arr = (char*)malloc(sizeof(char) * 15);//Dynamically creating arr to insert the word in the list
			if (arr == NULL) {
				printf("malloc failed\n");
				exit(-1);
			}
			if (arr) {
				strcpy(arr, temp);//copy temp to arr
				list = addToEND(list, arr);//add arr to list 
			}
		}
		strcpy(temp, word);
	}
	return list; //return list
}

LinkedList* addCharacterCheck(HashTable* dictionaryTable, char* word) {//Adds a letter in the spaces of the word and checks if the word exists in the dictionary
	char temp[30] = "";

	LinkedList* list = NULL;
	int j, i = 0, k;
	//Handles the part before the word:
	for (int letter = 97; letter < 123; letter++) { //runs on all the letters :from 'a' to 'z'
		temp[i] = letter;
		strcat(temp, word);
		//checking if the word exists in the dictionary and that the word and the new word(temp) are not equal
		if (isWordInDictionary(dictionaryTable, temp) == 1 && strcmp(temp, word) != 0) {
			char* arr = (char*)malloc(sizeof(char) * 15);//Dynamically creating arr to insert the word in the list
			if (arr == NULL) {
				printf("malloc failed\n");
				exit(-1);
			}
			if (arr) {
				strcpy(arr, temp);//copy temp to arr
				list = addToEND(list, arr);//add arr to list 
			}
		}
		strcpy(temp, " ");
	}
	//Handles the part after the first letter:
	for (int i = 0; i < strlen(word); i++) {
		k = 0;
		for (j = 0; j < i + 1; j++) {
			temp[j] = word[k++];
		}
		for (int letter = 97; letter < 123; letter++) {
			j = i + 1;
			k = j;
			temp[j++] = letter;

			for (j; j < strlen(word) + 1; j++) {

				temp[j] = word[k++];
			}
			temp[j] = '\0';
			char* arr2 = (char*)malloc(sizeof(char) * 15);//Dynamically creating arr to insert the word in the list
			if (arr2 == NULL) {
				printf("malloc failed\n");
				exit(-1);
			}
			//checking if the word exists in the dictionary and that the word and the new word(temp) are not equal
			if (isWordInDictionary(dictionaryTable, temp) == 1 && strcmp(temp, word) != 0) {
				char* arr2 = (char*)malloc(sizeof(char) * 15);//Dynamically creating arr to insert the word in the list
				if (arr2 == NULL) {
					printf("malloc failed\n");
					exit(-1);
				}
				if (arr2) {
					strcpy(arr2, temp);//copy temp to arr2
					list = addToEND(list, arr2);//add arr2 to list 
				}

			}

		}
	}
	
	return list;//return list 
}

LinkedList* Check_for_Duplicates(LinkedList* list) { //A function that checks for duplicates in a list 
	LinkedList* temp = NULL , *temp2= list;

	if (list == NULL)
		return list;

	while (temp2->next != NULL && temp2 != NULL) {
		temp = temp2;
		while (temp->next != NULL) { //run until the end of the list 

			if (strcmp(temp2->data,temp->next->data)==0) //Checks if the words are equal
				temp->next = temp->next->next; // if equal remove the next one
			else 
				temp = temp->next;
		}
		temp2 = temp2->next;
	}
	return list;//return list 
}


int Check_IF_equal(LinkedList* list,char* str) { //A functon that checks if a word exists in the list 
	while (list != NULL) {

		if (list->data == str)
			return 1; //if exist return 1

		list = list->next;
	}
	return 0;//if not on the list return 0
}

LinkedList* Connect_two_lists(LinkedList* list1, LinkedList* list2) { //A function that connects 2 lists 

	LinkedList* Connected_list = NULL;

	while (list2 != NULL) { //run until NULL
		
		if (Check_IF_equal(list1, list2->data) == 0) { 
			list1 = addToEND(list1, list2->data); //adding the word of list2 to list1
		}
		list2 = list2->next;
	}

	Connected_list = list1;
	return Connected_list; //returns the new connected list
}

LinkedList* getWordSuggestions(HashTable* dictionaryTable, char* word){//A function that receives a dictionary and a word and returns a list of spelling correction suggestions
	char temp[30] = "";
	strcpy(temp, word);
	LinkedList* Connected_list = NULL;

	LinkedList* list1 = addSpaceCheck(dictionaryTable, word); //returns list of addSpaceCheck
	LinkedList* list2 = replaceCharacterCheck(dictionaryTable, word);//returns list of replaceCharacterCheck
	LinkedList* list3 = deleteCharacterCheck(dictionaryTable, word);//returns list of deleteCharacterCheck
	LinkedList* list4 = addCharacterCheck(dictionaryTable, word);//returns list of addCharacterCheck
	LinkedList* list5 = switchAdjacentCharacterCheck(dictionaryTable, word);//returns list of switchAdjacentCharacterCheck
	//Connecting all the lists into one list 
	Connected_list = Connect_two_lists(list1, list2); 
	Connected_list = Connect_two_lists(Connected_list, list3);
	Connected_list = Connect_two_lists(Connected_list, list4);
	Connected_list = Connect_two_lists(Connected_list, list5);

	Connected_list = Check_for_Duplicates(Connected_list);// checking for Duplicates in the connected list and removing them

	return Connected_list; //returns the connected list
}




