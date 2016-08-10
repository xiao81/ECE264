#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "answer03.h"

// recursive implementation of the mind_guessing game
// part of the program already given
//
int mind_guessing_rec(int lb, int ub)
{
  // increment the counter for counting the number of recursive calls

  Increment_counter();

  // write down the terminating condition
  // when lb is the same as ub, you have guessed correctly
  if (lb == ub)
  {
    return lb;
  }

  char answer;    // this is for reading the input from the stdin
  int mid;        // this is for dividing the problem into two parts
                  // lb <= number in mind <= mid, i.e., [lb, mid] or
                  // mid < number in mind <= ub, i.e., [mid+1, ub].
                  // you want to use mid to divide the problem evenly.
                  // When you have odd number of integers from lb to ub,
                  // compute mid such that the part from lb to mid has one
                  // integer more than the part from mid+1 to ub
                  // Please note that lb and ub could be negative numbers.

  // compute mid

   
  if ((ub - lb + 1) % 2 == 0)
  {    
     mid = (ub + lb -1)/2;  // this is put in for compilation.  You would have to change it.
  }
  else
  { 
     mid = (ub + lb)/2;
  }
  
  // ask the question
  
  printf("Is the number greater than %d? (Y/N)\n", mid);

  // get the answer from stdin, don't change this

  answer = getchar();
  while (getchar() != '\n');

  // do the recursive call based on the answer
  // if answer == 'N' , do something, else do something else

  if (answer == 'N') { /* don't change this */
     /* add something here */
      return mind_guessing_rec(lb,mid);
  } else { /* don't change this */
     /* add something here */
      return mind_guessing_rec(mid + 1,ub);
    
  }
             // this is put in so that it would compile 
             //you should change it to something else
}

// iterative implementation of the mind_guessing game
// part of the program already given
//
int mind_guessing_itr(int lb, int ub)
{
  // increment the counter for counting the number of recursive calls
  Increment_counter();

  char answer;
  int mid; 

  // use the same method to calculate mid and partition
  // use the same method to get an input from stdin to the question
  // update lb and ub according to the answer

   while (lb < ub) {  // fill the right condition and remove comment
     // compute mid
     if ((ub - lb + 1) % 2 == 0)
       {
          mid = (ub + lb - 1)/2;
       }  // this is put in for compilation.  You would have to change it.
     else
	{
	  mid = (ub + lb)/2;
	}
     // ask the question
  
     printf("Is the number greater than %d? (Y/N)\n", mid);

     // get the answer from stdin, don't change this

     answer = getchar();
     while (getchar() != '\n');

     // update lb and ub based on the answer

     if (answer == 'N') { /* don't change this */
        /* add something here */
       ub = mid;
     } else { /* don't change this */
        /* add something here */
       lb = mid + 1;
     }

   } // end of while (....), remove comment
  return lb;  // this is put in for compilation.  You may have to change it
}

