/*
  string_list.c

  SENG265 - Summer 2016
  Assignment 2

  This program implements a StringList data structure using a doubly
  linked list.

  Author - Mark Worrall - 06/19/16
*/
#include <string.h>
#include <stdlib.h>s
#include "string_list.h"

void StringList_init(StringList* L){
	L->head = NULL;
	L->tail = NULL;
}

void StringList_Destroy(StringList* L){
	/*StringListNode* curr;
	while(L->head != NULL) {
		curr = L->head;
		StringList_RemoveNode(L, curr);
	}*/
}

int StringList_Size(StringList* L){
	return 0;
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
	char* str_new = (char*)malloc(sizeof(str));
	return L;
}

StringListNode* StringList_AddBack(StringList* L, char* str){
	return L;
}

int StringList_Remove(StringList* L, char* str){
	return 0;
}

void StringList_RemoveNode(StringList* L, StringListNode* node){

}

StringListNode* StringList_InList(StringList* L, char* str){
	return L;
}

StringListNode* StringList_GetIndex(StringList* L, int i){
	return L;
}

