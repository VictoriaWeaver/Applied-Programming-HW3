/******************************************************************************
 * TestDarray_hw.c - skeleton of code to test DynamicArray module
 *
 * Program to test the DynamicArrays module.  Reads in a large list of words
 * and puts them into the data structure, then prints out the first and last 
 * five elements in the data structure as well as the total number of words.
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include "DynamicArrays.h"
#include "Timers.h"

/* Initial Size of Dynamic Array */
#define INITIAL_SIZE (1000)

 void ReadData(FILE *InputFile, DArray *DynamicArrayPtr)
/******************************************************************************
*  Read the data file (assumed to be open) one word at a time placing each
* word into the data structure.
******************************************************************************/
{
   Data TempData;             /* temp variable to hold data   */
   int lcv = 1;               /* loop control variable        */
   char String[256];          /* temp variable to hold string */

 while (EOF != fscanf(InputFile, "%s", String))
 {
  TempData.Num = lcv++;
  strcpy(TempData.String, String);
  PushToDArray(DynamicArrayPtr, &TempData);
     } /* while() */
  } /* ReadData() */

  int main(int argc, char* argv[])
/******************************************************************************
*  Program to test the Data structure by reading the Data file provided on
* the command line into the structure, printing out the first and last five
* elements and total number of elements.
******************************************************************************/
{
  /* declare local variables */
   int ErrorCode = 0;               /* Application error code - 0 is OK */
   DArray TestDynamicArray, Searched;         /* Dynamic Array for Data */
   FILE *DataFile, *MyFile;         /* Pointer to Data file name (from cmd line) */
   int lcv;                         /* Loop Control Variable */
 int TotalEntries;

 DECLARE_TIMER(ReadTimer)
DECLARE_TIMER(SearchTimer)

   /* One command line argument is required: the file name     */
   if (3 == argc) /* note that argc 2 means one argument given */
 {
      /* Try to open the Data file for input (read mode)     */
      DataFile = fopen(argv[1], "r"); /* argv[1] is a string */

      /* Verify that file was opened correctly */
      if (NULL != DataFile){
         /* Initialize the dynamic array */
        CreateDArray(&TestDynamicArray, INITIAL_SIZE);

        BEGIN_REPEAT_TIMING(50);
         START_TIMER(ReadTimer);

         ReadData(DataFile, &TestDynamicArray);

        STOP_TIMER(ReadTimer);
        END_REPEAT_TIMING();
        PRINT_RTIMER(ReadTimer, 50);


         /* Close the Data file */
          fclose(DataFile);

         /* Print the first 6 entries */

          printf("First 6 words in dictionary:\n");

          for(lcv = 0; lcv < 6 ;lcv++){
              Data Temp = (&TestDynamicArray)->Payload[lcv];  
              printf("%s\n", Temp.String);
          }

          printf("Last 6 words in dictionary:\n");

	       /* Print the last 6 entries */
        for(lcv = 6; lcv > 0 ;lcv--){
            int index = (&TestDynamicArray)->EntriesUsed - lcv;
            Data Temp = (&TestDynamicArray)->Payload[index];
            printf("%s\n", Temp.String);
        }


         /* Print total number of words read */
        TotalEntries = (&TestDynamicArray)->EntriesUsed;
        printf("\nNumber of words:\n%d american-english-words\n", TotalEntries);

          BEGIN_REPEAT_TIMING(5);
         START_TIMER(SearchTimer);
          /* Try to open the Data file for input (read mode)     */
          MyFile = fopen(argv[2], "r"); /* argv[1] is a string */

          /* Verify that file was opened correctly */
        if (NULL != MyFile){
            /* Initialize the dynamic array */
           CreateDArray(&Searched, INITIAL_SIZE);

           ReadData(MyFile, &Searched);


            /* Close the Data file */
            fclose(MyFile);

            for(lcv = 0; lcv < Searched.EntriesUsed ;lcv++){
                  if(0 == SearchArray(&TestDynamicArray, Searched.Payload[lcv].String)){
                      printf("%s: found\n", Searched.Payload[lcv].String);
                  }
                  else{
                      printf("%s: lost\n", Searched.Payload[lcv].String); 
                  }
            }


            /* De-allocate the dynamic array */
            DestroyDArray(&TestDynamicArray);
            DestroyDArray(&Searched);


        } /* if() */
        
        else
        {
           /* Print error message */
          fprintf(stderr, "File not opened correctly!\n");
          fflush(stderr);
           ErrorCode = 2;
          } /* if...else() */


      } /* if() */
            STOP_TIMER(SearchTimer);
            END_REPEAT_TIMING();
            PRINT_RTIMER(SearchTimer, 5);
      }
 else
  {
      /* Print usage information */
          fprintf(stderr, "Incorrect Number of arguments!\n");
          fflush(stderr);
          ErrorCode = 1;
     } /* if...else() */

          return ErrorCode;
  } /* main() */
