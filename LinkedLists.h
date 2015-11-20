#ifndef _LINKED_LISTS_H_
#define _LINKED_LISTS_H_
/******************************************************************************
* Linked Lists Module public interface - LinkedLists.n
* Revised: 2/27/2015
******************************************************************************/

/******************************************************************************
* Modify structure ElementStructs to suit your application
******************************************************************************/

typedef struct 
  {
   /* Position in the file */
   int Position;
   /* Word in the file */
   char String[256];
  } ElementStructs;

/**************  Nothing else in the module needs to be modified *************/

/******************************************************************************
* struct for linked list nodes, contains user information and link pointers.
* The "ElementStructs" typemark must be defined based on specific needs of the
* application.
******************************************************************************/
typedef struct LinkedListNodes
  {
   /* The user information field */
   ElementStructs *ElementPtr;
   /* Link pointers */
   struct LinkedListNodes *Next;
   struct LinkedListNodes *Previous;
  } LinkedListNodes;

/*********************************************************************************
* struct for linked list "header", keeps a counter of the size of the linked list
**********************************************************************************/
typedef struct LinkedLists
  {
   /* Number of elements in the list */
   int NumElements;
   /* Pointer to the front of the list of elements, possibly NULL */
   struct LinkedListNodes *FrontPtr;
   /* Pointer to the end of the list of elements, possibly NULL */
   struct LinkedListNodes *BackPtr;
  } LinkedLists;

/******************************************************************************
* Initialize the linked list data structure
******************************************************************************/
void InitLinkedList(LinkedLists *ListPtr);

/******************************************************************************
* Adds a node to the front of the list.
******************************************************************************/
void AddToFrontOfLinkedList(LinkedLists *ListPtr, ElementStructs *DataPtr);

/******************************************************************************
* Adds a node to the back of the list.
******************************************************************************/
void AddToBackOfLinkedList(LinkedLists *ListPtr, ElementStructs *DataPtr);

/******************************************************************************
* Removes a node from the front of the list and returns a pointer to the node
* removed. On empty lists should return a NULL pointer.
******************************************************************************/
ElementStructs *RemoveFromFrontOfLinkedList(LinkedLists *ListPtr);


/******************************************************************************
* Removes a node from the back of the list and returns a pointer to the node
* removed. On empty lists should return a NULL pointer.
******************************************************************************/
ElementStructs *RemoveFromBackOfLinkedList(LinkedLists *ListPtr);

/******************************************************************************
* De-allocates the linked list and resets the struct fields (in the header) 
* to indicate that the list is empty.
******************************************************************************/
void DestroyLinkedList(LinkedLists *ListPtr);

/******************************************************************************
* Searches the linked list for the element string
******************************************************************************/
int SearchList(LinkedLists *ListPtr, ElementStructs *Search);


#endif /* _LINKED_LISTS_H_ */
