#include "HashTable.h"

int asciiStringHashFunction(char* str){//A function that returns the ASCII value of the first letter

    return str[0];
}
int accumulateStringHashFunction(char* str) {//A function Which returns the sum of the characters of the string (in their ASCII representation)
    int sum = 0;
    if (str==NULL) {
        return 0;
    }
    for (int i = 0; i < strlen(str); i++) {//runs until the end of the string
        sum += str[i];

    }
    return sum;//returns the sum
}

int improvedHashFunction(char* str) {//A function that returns a value calculated according to a formula
    int sum = 0;
    if (str == NULL) {
        return 0;
    }
    for (int i = 0; i < strlen(str); i++) {  //runs until the end of the string
        sum+=str[i] * (int)pow(31,(strlen(str) - 1 - i));
    }
    return sum;//returns the sum
}

int hash(char* str, HashTable* ht){//A function that calculates and returns an index where we store the string in he Hash table
    int key;

    if (ht->hashFunction == 1) {

       key = asciiStringHashFunction(str);//calculates the index with ascii String Hash Function
    }
    else if (ht->hashFunction == 2) {
        key = accumulateStringHashFunction(str);//calculates the index with accumulate String Hash Function
    }
    else {
        key = improvedHashFunction(str);//calculates the index with improved Hash Function
    }

    if (key < 0) {
        key = key * -1;
    }
    int index = key % ht->tableSize;
    return index;
}

int search(HashTable* ht, char* str){//A function that receives a string and a table and checks whether the string exists in the table
    int index = hash(str,ht);
   
    if (isInList(ht->hashTable[index].chain, str) == 1)//if the word is in the list return 1
        return 1;
    else 
        return 0;      //else return 0
}

HashTable* initTable(int tableSize, int hashFunction){ //A function that Initialize the table with tableSize and the number of hashFunction 
    // Dynamic creation of HashTable 
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (table == NULL) {
        printf("malloc failed\n");
        exit(-1);
    }
    // Dynamic creation of HashTableElement in tableSize 
    table->hashTable = (HashTableElement*)malloc(tableSize*sizeof(HashTableElement)); 
    if (table->hashTable == NULL) {
        printf("malloc failed\n");
        exit(-1);
    }
    //initialization of hashTable with NULL and 0
    for (int i = 0; i < tableSize; i++) { 
        table->hashTable[i].key = 0;
        table->hashTable[i].chain = NULL;
    }

    table->tableSize = tableSize;
    table->hashFunction = hashFunction;

    return table;//returns the table
}

int insert(HashTable* ht, char* str){ // A function that receives a table and a string, and inserts the string into the table
    int index ;
    
    if ((search(ht,str) == 0) && str != NULL) {//Check if the word already exists in the chain

        index=hash(str,ht); //check for index

        ht->hashTable[index].chain = addToEND(ht->hashTable[index].chain, str); //adds the word to the end of the chain and return 1
        return 1;
    }
    else
        return 0; //else return 0
}

int deleteElement(HashTable* ht, char* str){//A function that receives a string and a table and deletes the string from the table
    int index;
    if (search(ht, str) == 1) {//Check if the word already exists in the chain

        index = hash(str, ht);//check for index
        ht->hashTable[index].chain = DeleteElement(ht->hashTable[index].chain, str);//delete the word from the chain and return 1
        return 1; 
    }
    else
        return 0; //else return 0
}

HashTable* Freetable(HashTable* table) { //A function that releases the table 
    if (table == NULL)
        return;
    FreeList(table->hashTable->chain);
    free(table); ////deleting the list
    table = NULL;
    return table; //return NULL
}

