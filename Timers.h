/*************************************************************************
* Timers Instrumentation Macros Module
*
* The timing instrumentation macros can be globally enabled by setting 
* the variable EN_TIME (ENable TIMErs) in the compiler command line, e.g., 
* use "gcc -DEN_TIME...." to enable the timers when needed.
* A compiler warning will be issued when the timers are enabled.  
* Note: All timing output should be directed to stderr.
**************************************************************************/
#ifndef _TIMERS_H_
#define _TIMERS_H_

/* Write the timing macros here */

#if defined(EN_TIME)
	#include <stdio.h>
	#include <time.h>
	#if defined(WARNNIG_MSG)
		#warning Timers enabled! Execution could be adversly effected.
	#endif
#endif


/* Re-establish the starting point */
#if defined(EN_TIME)
	/****************************************************************************
	* Declare the timer. Initialize the timer (particularly the accumulated
	* elapsed time and the timer state).
	****************************************************************************/
	#define DECLARE_TIMER(A)													\
	struct {																	\
		clock_t Start;															\
		clock_t Stop;															\
		clock_t Elapsed;														\
																				\
		/* Timer state- set automatically: 0=stopped, 1=runnning */				\
		int State;																\
	} A = {																		\
		/* Start = */ 0,														\
		/* Stop = */ 0,															\
		/* Elapsed = */ 0,														\
		/* State = */ 0,														\
	}; /* Timer is declared and defined */

	

	/****************************************************************************
	* Start the timer. Print an error if it is already running, set the state 
	* to running, and then start the timer.
	****************************************************************************/
	#define START_TIMER(A)														\
	{																			\
		/* Check if already running */											\
		if(1 == A.State){														\
			fprintf(stderr, "Error, running timer "#A" started.\n");			\
		}																		\
																				\
		/* Set the state to running */											\
		A.State = 1;															\
																				\
		/* Start the timer last to maximize accuracy */							\
		A.Start = clock();														\
	} /* START_TIMER() */



	/****************************************************************************
	* Reset the timer. Clear the elapsed time.
	****************************************************************************/
	#define RESET_TIMER(A)														\
	{																			\
		A.Elapsed = 0;															\
	} /* RESET_TIMER() */



	/****************************************************************************
	* Stop the timer. Set the stop time, print an error message if the timer
	* is already stopped, otherwise accumulate the elapsed time and set the 
	* state to stopped.
	****************************************************************************/
	#define STOP_TIMER(A)														\
	{																			\
		A.Stop = clock();														\
		/* Check if already stopped */											\
		if(0 == A.State){														\
			fprintf(stderr, "Error, stopped timer " #A " stopped again.\n");	\
		}																		\
		else{																	\
			A.Elapsed += A.Stop - A.Start;										\
		}																		\
		/* Set the state to stopped */											\
		A.State = 0;															\
	} /* STOP_TIMER() */

	/****************************************************************************
	* Print the timer. Check the timer state and stop it if necessary.  Print
	* the elapsed time (in seconds).
	****************************************************************************/
	#define PRINT_TIMER(A)														\
	{																			\
		/* Check if already stopped */											\
		if(1 == A.State){														\
			STOP_TIMER(A);														\
		}																		\
		/* Print the elapsed time */											\
		printf("Elapsed CPU Time ("#A") = %g sec.\n", 							\
				(double)A.Elapsed / (double)CLOCKS_PER_SEC);					\
		} /* PRINT_TIMER() */



	/****************************************************************************
	* Print the correct timing info, that is, the time reported by 
	* PRINT_TIMER(A) divided by R
	****************************************************************************/
	#define PRINT_RTIMER(A,R)													\
	{																			\
		/* Check if already stopped */											\
		if(1 == A.State){														\
			STOP_TIMER(A);														\
		}																		\
		/* Print the elapsed time */											\
		printf("Average Elapsed CPU Time ("#A") = %g sec.\n", 			\
				((double) A.Elapsed/ (double) R) / (double) CLOCKS_PER_SEC);	\
	} /* PRINT_RTIMER() */




	/****************************************************************************
	* Beginning of for loop for the code being timed.
	****************************************************************************/
	#define BEGIN_REPEAT_TIMING(R)												\
		for(lcv = 0; lcv < R; lcv++){											\
	 /* BEGIN_REPEAT_TIMING() */




	/****************************************************************************
	* End of for loop for the code being timed.
	****************************************************************************/
	#define END_REPEAT_TIMING()													\
																				\
		}																		\
	 /* END_REPEAT_TIMING() */





#else /* Not defined EN_TIME */
	/* Declare null macros for error-free compilation */
	#define DECLARE_TIMER(A);
	#define START_TIMER(A);
	#define RESET_TIMER(A);
	#define STOP_TIMER(A);
	#define PRINT_TIMER(A);

	#define PRINT_RTIMER(A,R);
	#define BEGIN_REPEAT_TIMING(R);
	#define END_REPEAT_TIMING();

#endif /* EN_TIME */
#endif /* _TIMERS_H_ */
