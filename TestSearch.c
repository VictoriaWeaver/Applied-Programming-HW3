/********************************************************************
* Victoria Weaver
* vew4644@rit.edu
*
* Homework 3, Program to test a linked list abstract data type 
* as a C module. Practice the use of pointers and memory 
* allocation. Compare the time efficiency of linked lists against 
* dynamic arrays.
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "LinkedLists.h"
#include <string.h> 


void ReadData(FILE *InputFile, LinkedLists *ListPtr)
/******************************************************************************
*  Read the data file (assumed to be open) one word at a time placing each
* word into the data structure.
******************************************************************************/
{
   int lcv = 1;				/* loop control variable        */
   char String[256];		/* temp variable to hold string */

	while (EOF != fscanf(InputFile, "%s", String)){
   		ElementStructs *Data;		/* temp variable to hold data   */
		
		Data = malloc(sizeof(ElementStructs));
		if(0 == Data){
			printf("ERROR: Failed malloc read back\n");
		}
		
		Data->Position = lcv++;
		
		strcpy(Data->String, String);
		
		AddToFrontOfLinkedList(ListPtr, Data);

		

	} /* while() */
		

		

} /* ReadData() */



int main(int argc, char *argv[]){
/* declare local variables */
	int ErrorCode = 0;								/* Application error code - 0 is OK 			*/
	LinkedLists *List;								/* Linked list for Data 						*/
	LinkedLists *MyList;							/* List of words to search for 					*/
	FILE *DataFile, *MyFile;						/* Pointer to Data file name (from cmd line)	*/
	int lcv;										/* Loop Control Variable 						*/
	ElementStructs *Element;						/* Temporary element 							*/
	int TotalElements;
	
	List = malloc(sizeof(struct LinkedLists));
	MyList = malloc(sizeof(struct LinkedLists));

	if (0 == List || 0 == MyList){
		printf("ERROR: Failed malloc init list\n");
	}


	if (3 == argc){
		/* Try to open the Data file for input (read mode)     */
   		DataFile = fopen(argv[1], "r"); /* argv[1] is a string */

		/* Verify that file was opened correctly */
		if (NULL != DataFile){
			/* Initialize the linked list */
			InitLinkedList(List);

			ReadData(DataFile, List);

			/* Close the Data file */
			fclose(DataFile);

			/* Print the first 6 entries */
			printf("Total Number of Words: %d\n", List->NumElements);

			/* Print the first 6 entries */
			printf("First 6 words in dictionary:\n");

			for(lcv = 0; lcv < 6 ;lcv++){
				Element = RemoveFromBackOfLinkedList(List);
				printf("%s, %d\n", Element->String, Element->Position);
				free(Element);
			}
			DestroyLinkedList(List);
		}
		/* Try to open the Data file for input (read mode)     */
   		DataFile = fopen(argv[1], "r"); /* argv[1] is a string */

		/* Verify that file was opened correctly */
		if (NULL != DataFile){
			/* Initialize the linked list */
			InitLinkedList(List);

			ReadData(DataFile, List);

			/* Close the Data file */
			fclose(DataFile);

			/* Print the first 6 entries */
			printf("Last 6 words in dictionary:\n");

			for(lcv = 0; lcv < 6 ;lcv++){
				Element = RemoveFromFrontOfLinkedList(List);
				printf("%s, %d\n", Element->String, Element->Position);
				free(Element);
			}
			DestroyLinkedList(List);
		}   	
		/* Try to open the Data file for input (read mode)     */
   		DataFile = fopen(argv[1], "r"); /* argv[1] is a string */

		/* Verify that file was opened correctly */
		if (NULL != DataFile){
			/* Initialize the linked list */
			InitLinkedList(List);


			ReadData(DataFile, List);

			/* Close the Data file */
			fclose(DataFile);

			MyFile = fopen(argv[2], "r");

			/* Verify that file was opened correctly */
			if (NULL != MyFile){
				/* Initialize the linked list */
				InitLinkedList(MyList);

				ReadData(MyFile, MyList);

				/* Close the Data file */
				fclose(MyFile);

				TotalElements = MyList->NumElements;

				printf("\nSearching for words:\n");

				for(lcv = 0; lcv < TotalElements; lcv++){
					Element = RemoveFromFrontOfLinkedList(MyList);
					SearchList(List, Element);
					free(Element);
				}
				

				DestroyLinkedList(MyList);

			}
			DestroyLinkedList(List);
		}

		else{
			/* Print usage information */
			fprintf(stderr, "DataFile not opened!\n");
			fflush(stderr);
			ErrorCode = 2;
		}
	}
	else{
		/* Print usage information */
		fprintf(stderr, "Incorrect Number of arguments!\n");
		fflush(stderr);
		ErrorCode = 1;
	} /* if...else() */

	return ErrorCode;
} /* main */
