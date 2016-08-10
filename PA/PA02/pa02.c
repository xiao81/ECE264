#include <stdio.h>
#include <stdlib.h>
#include "pa_answer02.h"


int main(int argc, char * argv[])
{
  int c=0;
   
  if(argv[1][0] != '-' || (argv[1][1] != 'm' && argv[1][1] != 's'))
    {
  
      return EXIT_FAILURE;
    } 
  if(argv[1][1] == 's' )
    {
       printf("123\n");
      if(argv[2] != NULL && argv[3] != NULL && argv[4] != NULL)
        {
	  c = Simulate_mowing(argv[2],argv[3],argv[4]);
        }
      else
        {
          return EXIT_FAILURE;
        }
    }
   if(argv[1][1] == 'm' )
    {
     
      if(argv[2] != NULL && argv[3] != NULL)
        {

	  Get_mowing_directions(argv[2],argv[3]);
        }
      else
        {
	  
          return EXIT_FAILURE;
        }
    }
  
  return 0;
}
