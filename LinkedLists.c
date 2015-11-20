/********************************************************************
* Victoria Weaver
* vew4644@rit.edu
*
* Homework 3, Program to implement a linked list abstract data type 
* as a C module. Practice the use of pointers and memory 
* allocation. Compare the time efficiency of linked lists against 
* dynamic arrays.
********************************************************************/

#include "LinkedLists.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/******************************************************************************
* Initialize the linked list data structure (empty list)
******************************************************************************/
void InitLinkedList(LinkedLists *ListPtr){
	/* Initialize the size to 0 (empty) */
	ListPtr->NumElements = 0;

	/* Null head */
	ListPtr->FrontPtr = NULL;
	
	/* Null tail */
	ListPtr->BackPtr = NULL;

}

/******************************************************************************
* Adds a node to the front of the list.
******************************************************************************/
void AddToFrontOfLinkedList(LinkedLists *ListPtr, ElementStructs *DataPtr){
	/* Put the element in a new node */
	LinkedListNodes *Head, *Temp;


	/* Allocate memory for the new node */
	Head = malloc(sizeof(ElementStructs));
	Temp = malloc(sizeof(ElementStructs));
	
	
	if (0 == Head || 0 == Temp){
		printf("ERROR: Failed malloc add to front\n");
	}
	
	/* Assign the properties of the new node */
	Head->ElementPtr = DataPtr;
	Head->Next = NULL;
	Head->Previous = NULL;

	/* Check if the list is empty */
	if(0 == ListPtr->NumElements){
		/* Add the first element */
		ListPtr->FrontPtr = Head;
		ListPtr->BackPtr = Head;

		free(Temp);

	}

	else{
		/* Establish a temporary node */
		Temp = ListPtr->FrontPtr;

		/* Head becomes previous of former front node */
		Temp->Previous = Head;
		
		/* Former front becomes next of head */
		Head->Next = Temp;

		/* Head becomes the new front */
		ListPtr->FrontPtr = Head;

	}

	/* Increase the size of the list every time */
	ListPtr->NumElements++;

}

/******************************************************************************
* Adds a node to the back of the list.
******************************************************************************/
void AddToBackOfLinkedList(LinkedLists *ListPtr, ElementStructs *DataPtr){
	/* Put the element in a new node */
	LinkedListNodes *Tail, *Temp;

	/* Allocate memory for the new node */
	Tail = malloc(sizeof(ElementStructs));
	Temp = malloc(sizeof(ElementStructs));

	if (0 == Tail || 0 == Temp){
		printf("ERROR: Failed malloc add to back\n");
	}
	
	/* Assign the properties of the new node */
	Tail->ElementPtr = DataPtr;
	Tail->Next = NULL;
	Tail->Previous = NULL;

	/* Check if the list is empty */
	if(0 == ListPtr->NumElements){
		/* Add the first element */
		ListPtr->FrontPtr = Tail;
		ListPtr->BackPtr = Tail;

		free(Temp);
	}

	else{
		/* New node becomes the new back */
		Temp = ListPtr->BackPtr;
		Temp->Next = Tail;	

		/* Back becomes previous of new node */
		Tail->Previous = Temp;

		/* Tail becomes the new back */
		ListPtr->BackPtr = Tail;
	}

	
	/* Increase the size of the list every time */
	ListPtr->NumElements++;
}

/******************************************************************************
* Removes a node from the front of the list and returns a pointer to the node
* removed. On empty lists should return a NULL pointer.
******************************************************************************/
ElementStructs *RemoveFromFrontOfLinkedList(LinkedLists *ListPtr){
	/* Create a temporary node and a null element */
	LinkedListNodes *Temp;
	ElementStructs *Element;
	
	/* Check if the list is empty */
	if(0 == ListPtr->NumElements){
		return NULL;
	}

	Temp = malloc(sizeof(ElementStructs));

	if(0 == Temp){
		printf("ERROR: Failed malloc remove front\n");
	}

	if(1 == ListPtr->NumElements){
		/* Update the element */
		Temp = ListPtr->FrontPtr;
		Element = Temp->ElementPtr;


		/* Free the memory from the front */
		free(Temp);

		/* The list is now empty */
		ListPtr->FrontPtr = NULL;
		ListPtr->BackPtr = NULL;

	}

	else{
		
		Temp = ListPtr->FrontPtr;
		Element = Temp->ElementPtr;

		Temp->Next->Previous = NULL;

		ListPtr->FrontPtr = Temp->Next;

		free(Temp);
	}
	

	/* Decrement the size of the list */
	ListPtr->NumElements--;
	return Element;
}


/******************************************************************************
* Removes a node from the back of the list and returns a pointer to the node
* removed. On empty lists should return a NULL pointer.
******************************************************************************/
ElementStructs *RemoveFromBackOfLinkedList(LinkedLists *ListPtr){
	/* Create a temporary node and a null element */
	LinkedListNodes *Temp;
	ElementStructs *Element;
	
	/* Check if the list is empty */
	if(0 == ListPtr->NumElements){
		return NULL;
	}

	Temp = malloc(sizeof(ElementStructs));
	if(0 == Temp){
		printf("ERROR: Failed malloc remove back\n");
	}

	if(1 == ListPtr->NumElements){
		/* Update the element */
		Temp = ListPtr->BackPtr;
		Element = Temp->ElementPtr;


		/* Free the memory from the front */
		free(Temp);

		/* The list is now empty */
		ListPtr->FrontPtr = NULL;
		ListPtr->BackPtr = NULL;

	}

	else{
		/* Update the element */
		Temp = ListPtr->BackPtr;
		Element = Temp->ElementPtr;

		/* Update the next of the new back to null */
		Temp->Previous->Next = NULL;

		/* Update the new back */
		ListPtr->BackPtr = Temp->Previous;

		free(Temp);
	}
	

	/* Decrement the size of the list */
	ListPtr->NumElements--;
	return Element;
}

/******************************************************************************
* De-allocates the linked list and resets the struct fields (in the header) 
* to indicate that the list is empty.
******************************************************************************/
void DestroyLinkedList(LinkedLists *ListPtr){
	
	LinkedListNodes *Current, *Temp;
	Current = ListPtr->FrontPtr;
	
	Temp = malloc(sizeof(ElementStructs));
	if(0 == Temp){
		printf("ERROR: Failed malloc destroy\n");
	}

	/* Free the memory */
	while(NULL != Current){
		/*Store the next node*/
		Temp = Current->Next;
		free(Current);
		Current = Temp;
	}

	free(Temp);

	/* Set the front and back to NULL */
	ListPtr->FrontPtr = NULL;
	ListPtr->BackPtr = NULL;
	
	/* Set the size to 0 */
	ListPtr->NumElements = 0;

}


/******************************************************************************
* Searches a linked list for a string and returns the location of the string
* (returns -1 if string is not found)
******************************************************************************/
int SearchList(LinkedLists *ListPtr, ElementStructs *Search){
	/* Temporary variables */
	LinkedListNodes *Current;


	Current = ListPtr->FrontPtr;

	while(Current != NULL){
		/* Check if the strings are equal */
		if(0 == strcmp(Current->ElementPtr->String, Search->String)){
			printf("%s FOUND\n", Search->String);
			return 1;
		}

		/* Move on to the next node */
		Current = Current->Next;
	}


	printf("%s LOST\n", Search->String);
	return 1;
}









