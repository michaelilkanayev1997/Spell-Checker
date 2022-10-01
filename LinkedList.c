#include "LinkedList.h"

LinkedList* BuildNode(char* str){//A function that builds a new node
    LinkedList* newnode = (LinkedList*)malloc(sizeof(LinkedList));
    if (newnode == NULL) {
        printf("malloc failed\n");
        exit(-1);
    }
    newnode->data = str;//Saving the value in the node
    return newnode;
}

void PrintList(LinkedList* list) {//A function that prints the list data
        LinkedList* temp = list;
        //iterate the entire linked list and print the data
        while (temp != NULL){
            printf(" %s \n", temp->data);
            temp = temp->next;
        }
}

LinkedList* addToStart(LinkedList* list, char* str){//A function that adds the string to the start of the list
        //create a new node
        LinkedList* newnode=BuildNode(str); //building a node with the string

        newnode->next = list;
        list = newnode;

        return list;//returning the list 
}

LinkedList* FreeList(LinkedList* list) {//A function that releases the list
    if (list == NULL)
        return;
    free(list); ////deleting the list
    list = NULL;
    return NULL;
}

LinkedList* DeleteElement(LinkedList* list, char* str){//A function that deletes an element in the list

    // Store head node
    LinkedList* temp = list, * prev=NULL;

    // If head node itself holds the key to be deleted
    if (temp != NULL && temp->data == str) {
        list = temp->next; // Changed head
        free(temp); // free old head
        return list;
    }

    // Search for the key to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while (temp != NULL && temp->data != str) {
        prev = temp;
        temp = temp->next;
    }

    // If key was not present in linked list
    if (temp == NULL)
        return list;

    // Unlink the node from linked list
    prev->next = temp->next;

    free(temp); // Free memory

    return list;//returning list
}

int isInList(LinkedList* list, char* str){//A function that checks if the word is in the list 
    LinkedList* temp = list;

    while (temp != NULL) {

        if (temp->data == str) //if the word is in the list return 1
            return 1;
        temp = temp->next;
    }
    return 0;//if the word is NOT in the list return 0
}

LinkedList* addToEND(LinkedList* list, char* str){//A function that adds the string to the end of the list
    //create a new node
    LinkedList* newnode = BuildNode(str);
    newnode->next = NULL;
    //if head is NULL, it is an empty list
    if (list == NULL)
        newnode->next = list;
    //Otherwise, find the last node and add the newNode
    else{
        LinkedList* lastnode = list;

        //last node's next address will be NULL.
        while (lastnode->next != NULL) {
            lastnode = lastnode->next;
        }
        //add the newNode at the end of the linked list
        lastnode->next = newnode;
        return list;
    }
    // return list 
    return newnode;
}
