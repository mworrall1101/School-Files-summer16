/* string_list_tester.c
  
   SENG 265 - Summer 2016
   Assignment 2
   
   Template for a tester for the StringList datatype.
   
   Do not change any of the function signatures or the contents
   of main() or your submission may be invalid.
  
   B. Bird - 05/26/2016
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_list.h"

#define TEST_FAILED 0
#define TEST_PASSED 1

/* Each of the test functions below should return TEST_FAILED if the test fails
   and TEST_PASSED if the test is passed.
*/

/* Additional Functions*/

int test_add(StringList* L, StringListNode* node, int i, char* str){
	if(str == node->element){
		printf("Error: The node->element should not point to the original string.\n");
		return TEST_FAILED;	
	}
	if(strcmp(str, node->element)) {
		printf("\nError: Element %d was not added to the list, or is not where expected.\n",i);	
		return TEST_FAILED;
	}
	if(StringList_Size(L) != i+1) {
		printf("\nError: StringList_Size did not update after adding element %d.\n", i);
		return TEST_FAILED;
	}
	return TEST_PASSED;
}

int init_check(StringList* T){
	if((T->head != NULL) || (T->tail != NULL)) {
		printf("\nError: StringList was not initialized.\n");
		return TEST_FAILED;
	}
	return TEST_PASSED;
}

/*Originial Template Functions Below This Point*/

int test1(){
	//First test case: Basic functionality I
	//Test only the StringList_Init, StringList_Size,
	//and StringList_AddFront functions.
	//(Note that since you cannot use StringList_Destroy, this function
	// will produce a memory leak. However, this is acceptable in a testing
	// context).
	char* test_strings[] = {"one", "two", "three", "four"};
	printf("\nBeginning Test 1...\n");
	StringList S;
	StringListNode* curr;
	printf("Initializing StringList...\n");
	StringList_Init(&S);
	if(!init_check(&S)) return TEST_FAILED;
	printf("Adding strings to list...\n");
	int i;
	for(i = 0; i < 4; i++) {
		StringList_AddFront(&S, test_strings[i]);
		curr = S.head;
		if(!test_add(&S, curr, i, test_strings[i])) return TEST_FAILED;
	}
	printf("Strings added and size is correct.\n");
	return TEST_PASSED;
}

int test2(){
	//Second test case: Basic functionality II
	//Test only the StringList_Init, StringList_Size,
	//StringList_AddFront and StringList_AddBack functions.
	char* test_strings[] = {"one", "two", "three", "four"};
	printf("\nBeginning Test 2...\n");
	StringList S;
	StringListNode* curr;
	printf("\nTesting StringList_AddFront()\nInitializing...\n");
	StringList_Init(&S);
	if(!init_check(&S)) return TEST_FAILED;
	printf("Adding strings to front of the list...\n");
	int i, flip = 1;
	for(i = 0; i < 4; i++) {
		StringList_AddFront(&S, test_strings[i]);
		curr = S.head;
		if(!test_add(&S, curr, i, test_strings[i])) return TEST_FAILED;
	}
	printf("Strings added and size is correct.\n");
	
	/*A second list is being used to test the StringList_AddBack function
	on an empty list*/
	printf("\nTesting StringList_AddBack().\nInitializing..\n");
	StringList T;
	StringList_Init(&T);
	if(!init_check(&T)) return TEST_FAILED;
	printf("Adding strings to the back of the list...\n");
	for(i = 0; i < 4;i++){
		StringList_AddBack(&T, test_strings[i]);
		curr = T.tail;
		if(!test_add(&T, curr, i, test_strings[i])) return TEST_FAILED;
	}
	printf("Strings added and size is correct.\n");
	printf("\nTesting both functions together.\nInitializing...\n");
	StringList U;
	StringList_Init(&U);
	if(!init_check(&U)) return TEST_FAILED;
	for(i = 0; i < 4; i++){
		if(flip){
			StringList_AddFront(&U,test_strings[i]);
			curr = U.head;
			flip = 0;
		} else {
			StringList_AddBack(&U,test_strings[i]);
			curr = U.tail;
			flip = 1;	
		}
		if(!test_add(&U, curr, i, test_strings[i])) return TEST_FAILED;
	}
	printf("Strings added and size is correct.\n");
	return TEST_PASSED;
}

int test3(){
	//Third test case: Basic functionality III
	//Test only the StringList_Init, StringList_Size,
	//StringList_AddFront and StringList_AddBack functions.
	//Use a different methodology for this test than test 2.
	char* test_strings[] = {"one", "two", "three", "four"};
	printf("\nBeginning Test 3...\n");
	StringList S;
	StringListNode* curr;
	printf("\nTesting StringList_AddFront() and StringList_AddBack() together\nInitializing...\n");
	StringList_Init(&S);
	if(!init_check(&S)) return TEST_FAILED;
	StringList_AddFront(&S, test_strings[0]);
	StringList_AddBack(&S, test_strings[1]);
	printf("Adding a node to the front and then back...\n");
	if(S.head->next != S.tail){
		printf("\nError: First node and tail do not point to the same node.\n");	
		return TEST_FAILED;
	}
	if(S.tail->previous != S.head){
		printf("\nError: Last node and head do not point to the same node.\n");	
		return TEST_FAILED;
	}
	printf("Adding another node to the front...\n");
	StringList_AddFront(&S, test_strings[2]);
	curr = S.head;
	if(curr->next->previous != curr){
		printf("\nError: First and second node do not reference eachother properly.\n");	
		return TEST_FAILED;
	}
	printf("Adding another node to the back...\n");
	StringList_AddBack(&S, test_strings[3]);
	curr = S.tail;
	if(curr->previous->next != curr) {
		printf("\nError: Last and second last node do not reference eachother properly.\n");	
		return TEST_FAILED;
	}
	if(StringList_Size(&S) != 4) return TEST_FAILED;
	
	printf("All adds successful, and size is correct.\n");
	
	return TEST_PASSED;
}

int test4(){
	//Fourth test case: List membership I
	//Test the StringList_GetIndex function, using any of the functions
	//tested in previous test cases if necessary.
	char* test_strings[] = {"one", "two", "three", "four"};
	int i;
	printf("\nBeginning Test 4...\n");
	StringList S;
	StringListNode* curr;
	StringList_Init(&S);
	printf("\nInitializing list...\n");
	if(!init_check(&S)) return TEST_FAILED;
	for(i = 0; i < 4; i++) {
		StringList_AddBack(&S, test_strings[i]);
		curr = S.tail;
		if(!test_add(&S, curr, i, test_strings[i])) return TEST_FAILED;
	}
	//test out of bounds
	printf("Testing StringList_Index() function...\n");
	if(StringList_GetIndex(&S,12) != NULL) {
		printf("\nError: Out of bounds index call did not return NULL.\n");
		return TEST_FAILED;
	}
	//test each index is correct
	for(i = 0; i < 4; i++){
		if(strcmp(StringList_GetIndex(&S, i)->element, test_strings[i])) {
			printf("\nError: Index %d contains %s, and should contain %s\n",i, StringList_GetIndex(&S, i)->element, test_strings[i]);
			return TEST_FAILED;
		}
	}
	

	return TEST_PASSED;
}

int test5(){
	//Fifth test case: List membership II
	//Test the StringList_InList function, using any of the functions
	//tested in previous test cases if necessary.
	char* test_strings[] = {"one", "two", "three", "four"};
	int i;
	printf("\nBeginning Test 5...\n");
	StringList S;
	StringListNode* curr;
	StringList_Init(&S);
	printf("\nInitializing list...\n");
	if(!init_check(&S)) return TEST_FAILED;
	for(i = 0; i < 4; i++) {
		StringList_AddBack(&S, test_strings[i]);
		curr = S.tail;
		if(!test_add(&S, curr, i, test_strings[i])) return TEST_FAILED;
	}
	StringListNode* test_node = StringList_GetIndex(&S, 2);
	printf("Testing StringList_InList() function...\nTesting Part 1...\n");
	if(StringList_InList(&S, test_strings[2]) != test_node) {
		printf("\nError: Node returned is not the expected node\n");
		return TEST_FAILED;
	}
	printf("Part 2...\n");
	if(StringList_InList(&S, "three") != test_node) {
		printf("\nError: Node returned is not the expected node\n");
		return TEST_FAILED;
	}
	char* missing_word = "twelve";
	printf("Part 3...\n");
	if(StringList_InList(&S, missing_word) != NULL) {
		printf("\nError: Return value for word not found should be NULL.\n");
		return TEST_FAILED;
	}
	printf("All parts of test 5 passed.\n");
	return TEST_PASSED;
}

int test6(){
	//Sixth test case: Deletion I
	//Test the StringList_Remove and StringList_RemoveNode functions,
	//using any of the functions tested in previous test cases if necessary.
	char* test_strings[] = {"one", "two", "three", "four"};
	int i;
	printf("\nBeginning Test 6...\n");
	StringList S;
	StringListNode* curr;
	StringList_Init(&S);
	printf("\nInitializing list...\n");
	if(!init_check(&S)) return TEST_FAILED;
	for(i = 0; i < 4; i++) {
		StringList_AddBack(&S, test_strings[i]);
		curr = S.tail;
		if(!test_add(&S, curr, i, test_strings[i])) return TEST_FAILED;
	}
	printf("Testing StringList_RemoveNode()...\n");
	StringList_RemoveNode(&S, StringList_GetIndex(&S, 2));
	if(StringList_InList(&S, "three") != NULL) {
		printf("\nError: Failed to remove node from index 2\n");
		return TEST_FAILED;
	}
	StringList_RemoveNode(&S, StringList_GetIndex(&S, 0));
	if(StringList_InList(&S, "one") != NULL) {
		printf("\nError: Failed to remove node from front of the list.\n");	
		return TEST_FAILED;
	}
	StringList_RemoveNode(&S, StringList_GetIndex(&S, 1));
	if(StringList_InList(&S, "four") != NULL) {
		printf("\nError: Failed to remove node from end of the list.\n");	
		return TEST_FAILED;
	}
	//Adding more nodes
	for(i = 0; i < 4; i++) {
		StringList_AddBack(&S, test_strings[i]);
	}
	printf("Testing StringList_Remove()...\n");
	if(!StringList_Remove(&S, "two")){
		printf("\nError: Failed to remove node containing specified string.\n");	
		return TEST_FAILED;
		
	}
	StringList_Remove(&S, "two");
	StringList_Remove(&S, "two");
	if(StringList_InList(&S, "two")){
		printf("\nError: String found in list after attempting to remove all occurences.\n");	
		return TEST_FAILED;
		
	}
	if(!StringList_Remove(&S,StringList_GetIndex(&S, 0)->element)) {
		printf("\nError: Failed to remove first node.\n");	
		return TEST_FAILED;
	}

	return TEST_PASSED;
}

int test7(){
	//Seventh test case: Deletion II
	//Test the StringList_Remove, StringList_RemoveNode and StringList_Destroy functions,
	//using any of the functions tested in previous test cases if necessary.
	//Use a different methodology for this test than test 6.
	char* test_strings[] = {"one", "two", "three", "four"};
	int i;
	printf("\nBeginning Test 7...\n");
	StringList S;
	StringList_Init(&S);
	printf("\nInitializing list...\n");
	if(!init_check(&S)) return TEST_FAILED;
	for(i = 0; i < 4; i++) {
		StringList_AddBack(&S, test_strings[i]);
	}
	printf("Testing StringList_RemoveNode()...\n");
	StringList_RemoveNode(&S,S.head);
	if(S.head->previous != NULL){
		printf("\nError: 'node.previous' of new first node not set to NULL after removal of first node.\n");	
		return TEST_FAILED;
	}
	while(S.head != NULL) {
		StringList_RemoveNode(&S, S.head);
	}
	if(S.tail != S.head) {
		printf("\nError: After removing all nodes, S.head and S.tail are not NULL.\n");	
		return TEST_FAILED;
		
	}
	for(i = 0; i < 4; i++) {
		StringList_AddBack(&S, test_strings[i]);
	}
	printf("Testing StringList_Destroy()...\n");
	StringList_Destroy(&S);
	if((S.head != NULL) || (S.tail != NULL)) {
		printf("\nError: After list destroy, S.head or S.tail are not NULL.\n");	
		return TEST_FAILED;
		
	}
	return TEST_PASSED;
}

int test8(){
	//Eighth test case: Stress Test
	//Test all of the methods of the StringList, in an attempt to simulate the
	//actual use of the data structure in practice. For logistical reasons, 
	//keep in mind that your test must complete within 30 seconds for the 
	//automated system, so some types of exhaustive testing are not practical
	//here.
	int i = 0, count, counter;
	printf("\nBeginning Test 8...\n");
	
	StringList HS;
	StringList_Init(&HS);
	printf("\nInitializing list...\n");
	if(!init_check(&HS)) return TEST_FAILED;
	while(i < 5){	
		count = 0;
		counter = 0;
		while(count < 10000000) {
			if(counter < 30){
					StringList_AddFront(&HS, "Hay");
				counter++;
			} else if(counter == 30){
				StringList_AddFront(&HS, "Needle");
				counter++;
			} else if(counter < 100) {
				StringList_AddBack(&HS, "Hay");
				counter++;	
			} else {
				StringList_AddBack(&HS, "Hay");
				counter = 0;
			}
			count++;
		}
		if(StringList_InList(&HS,"Needle") == NULL) {
			printf("\nError: Failed to find 'Needle' in HS.\n");
			return TEST_FAILED;	
		}
		if(StringList_Size(&HS) != 10000000) {
			printf("\nError: StringList_Size is not correct(%d).\n", StringList_Size(&HS));
			return TEST_FAILED;	
		}
		StringList_Destroy(&HS);
		if(StringList_Size(&HS) != 0) {
			printf("\nError: StringList_Size should return zero after list destroyed.\n");
			return TEST_FAILED;		
		}
		i++;
	}

	
	return TEST_PASSED;
}




/* Do not change any of the code below, to ensure consistency during all vs. all testing */

void show_usage(){
	fprintf(stderr,"Usage: ./string_list_tester <test_number>\n");
	fprintf(stderr,"Where <test_number> is an integer between 1 and 8.\n");
}

int main(int argc, char** argv){
	if (argc < 2){
		show_usage();
		return 0;
	}
	//The atoi function converts a string to an integer (and returns 0 if
	//the conversion fails).
	int test_number = atoi(argv[1]);
	
	if (test_number <= 0 || test_number > 8){
		show_usage();
		return 0;
	}
	
	int result = 1;
	switch(test_number){
		case 1:
			result = test1();
			break;
		case 2:
			result = test2();
			break;
		case 3:
			result = test3();
			break;
		case 4:
			result = test4();
			break;
		case 5:
			result = test5();
			break;
		case 6:
			result = test6();
			break;
		case 7:
			result = test7();
			break;
		case 8:
			result = test8();
			break;
	}
	
	if (result == TEST_PASSED){
		printf("\nTEST PASSED\n");
	}else{
		printf("\nTEST FAILED\n");
	}
	
	return 0;
}
