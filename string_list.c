/*
  string_list.c

  SENG265 - Summer 2016
  Assignment 2

  This program implements a StringList data structure using a doubly
  linked list.

  Author - Mark Worrall - 06/19/16
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "string_list.h"

int count = 0;

void StringList_Init(StringList* L){
	L->head = NULL;
	L->tail = NULL;
}

void StringList_Destroy(StringList* L){
	StringListNode* curr = L->head;
	while(curr != NULL) {
		StringList_RemoveNode(L, curr);
		curr = curr->next;
	}
}

int StringList_Size(StringList* L){
	return count;
}

/* StringList_AddFront(L, str)
   Create a new list node containing a copy of the string str and
   add the node to the front (head) of the list L.
   
   Note: The created node must not contain a pointer to the string
   str. Instead, it should contain a pointer to a new array containing
   a copy of str.
   
   Pre-conditions:
     L is a pointer to an initialized StringList struct.
	 str points to a valid null terminated C string.
   Post-conditions:
     A new node containing a copy of str has been attached
	 to the beginning of the list L.
   Return value:
     A pointer to the created node.
*/ 
StringListNode* StringList_AddFront(StringList* L, char* str){
	StringListNode* new_node = (StringListNode*)malloc( sizeof(StringListNode) );
	new_node->element = (char*)malloc((strlen(str) + 1)*sizeof(char));
	strcpy(new_node->element, str);
	if(L->head == NULL) {
		L->tail = new_node;
		L->head = new_node;
		new_node->next = NULL;
		new_node->previous = NULL;
	} else{
		new_node->next = L->head;
		new_node->previous = NULL;
		L->head->previous = new_node;
		L->head = new_node;
	}
	count++;
	return new_node;
}

/* StringList_AddBack(L, str)
   Create a new list node containing a copy of the string str and
   add the node to the back (tail) of the list L.
   
   Note: The created node must not contain a pointer to the string
   str. Instead, it should contain a pointer to a new array containing
   a copy of str.
   
   Pre-conditions:
     L is a pointer to an initialized StringList struct.
	 str points to a valid null terminated C string.
   Post-conditions:
     A new node containing a copy of str has been attached
	 to the end of the list L.
   Return value:
     A pointer to the created node.
*/ 
StringListNode* StringList_AddBack(StringList* L, char* str){
	StringListNode* new_node = (StringListNode*)malloc(sizeof(StringListNode));
	new_node->element = (char*)malloc((strlen(str) + 1)*sizeof(char));
	strcpy(new_node->element, str);
	if(L->tail == NULL) {
		L->tail = new_node;
		L->head = new_node;
		new_node->next = NULL;
		new_node->previous = NULL;
	} else{
		new_node->previous = L->tail;
		new_node->next = NULL;
		L->tail->next = new_node;
		L->tail = new_node;
	}
	count++;
	return new_node;
}

int StringList_Remove(StringList* L, char* str){
	StringListNode* delete = StringList_InList(L, str);
	int status = 0;
	if(delete != NULL) {
		StringList_RemoveNode(L, delete);
		status = 1;
	}
	return status;
}

/* StringList_RemoveNode(L, node)
   Remove the provided node from the list L.
   
   Note that the removal process should free all storage associated
   with the node and the string it contains.
   
   Pre-conditions:
     L is a pointer to an initialized StringList struct.
	 node points to a valid node in L.
   Post-conditions:
     node has been removed from L.
*/ 
void StringList_RemoveNode(StringList* L, StringListNode* node){
	//StringListNode* delete = node;
	if((node->previous == NULL) && (node->next == NULL)) {
		L->head = NULL;
		L->tail = NULL;
	} else if(node->previous == NULL) {
		L->head = node->next;
		node->next->previous = NULL;
	}else if(node->next == NULL) {
		L->tail = node->previous;
		node->previous->next = NULL;
	} else {
		node->next->previous = node->previous;
		node->previous->next = node->next;
		node->next = NULL;
		node->previous = NULL;
	}
	free(node->element);
	free(node);
	count--;

}

StringListNode* StringList_InList(StringList* L, char* str){
	StringListNode* curr = L->head;
	while((strcmp(curr->element,str)) && (curr != NULL)){
		curr = curr->next;	
	}
	return curr;
}

StringListNode* StringList_GetIndex(StringList* L, int i){
	if((i > (count-1)) || (i < 0)){
		return NULL;
	}
	StringListNode* curr = L->head;
	int j;
	for(j = 0; j < i; j++){
		curr = curr->next;	
	} 	
	return curr;
}

int main(){
	StringList S;
	StringList_Init(&S);
	char* str = "blue";
	char* str2 = "green";
	char* str3 = "yellow";
	StringListNode* first ;//= StringList_AddFront(&S, str);
	StringListNode* second = StringList_AddFront(&S, str2);
	StringListNode* third = StringList_AddBack(&S, str3);
	StringListNode* fourth = StringList_AddBack(&S, str);
	first = StringList_GetIndex(&S,6);
	if(first == NULL) printf("First out of bounds\n");
//	StringList_RemoveNode(&S, third);
	StringListNode* curr = S.head;
	while(curr){
		printf("%s\n", curr->element);
		curr = curr->next; 
	}
	printf("Count = %d\n", StringList_Size(&S) );
//	StringList_Destroy(&S);
	if(!S.head) printf("List dne\n");
	/*while(curr){

		printf("%s\n", curr->element);
		curr = curr->next; 
	}*/
	return 0;
}
