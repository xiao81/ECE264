#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pa_answer03.h"

int main(int argc,char * argv[])
{
  int size1,size2,size3,row;
  if(strcmp(argv[1],"-i") == 0)
    {
      if(argv[2] != NULL && argv[3] != NULL)
	{
	  double **matrix1 = Read_matrix_from_file(argv[2],&size1);
	 matrix1 = Invert_matrix(matrix1,size1);
	  if(matrix1 == NULL)
	    {
	      for (row = 0;row < size1;row++)
	    {
	      free(matrix1[row]);
	    }
	  free(matrix1);
	      fprintf(stderr,"exit fail\n");
	      return EXIT_FAILURE;
	    }
	  Write_matrix_to_file(argv[3],matrix1,size1);
          for (row = 0;row < size1;row++)
	    {
	      free(matrix1[row]);
	    }
	  free(matrix1);
	
        
	}
      else
	{
          fprintf(stderr,"exit fail\n");
	  return EXIT_FAILURE;
	}
    } 
    else if(strcmp(argv[1],"-m") == 0)
      {
	if(argv[2] != NULL && argv[3] != NULL && argv[4] != NULL)
	  {
	    double **matrix2;
	    double **matrix2a = Read_matrix_from_file(argv[2],&size2);
	    double **matrix2b = Read_matrix_from_file(argv[3],&size2);
	    matrix2 = Matrix_matrix_multiply(matrix2a,matrix2b,size2);
	    if(matrix2a == NULL||matrix2b == NULL)
	      {
		for (row = 0;row < size2;row++)
	      {
		free(matrix2a[row]);
	      }
	    free(matrix2a);
	    for (row = 0;row < size2;row++)
	      {
		free(matrix2b[row]);
	      }
	    free(matrix2b);
		fprintf(stderr,"exit fail\n");
		return EXIT_FAILURE;
	      }
	    Write_matrix_to_file(argv[4],matrix2,size2);
	    for (row = 0;row < size2;row++)
	      {
		free(matrix2a[row]);
	      }
	    free(matrix2a);
	    for (row = 0;row < size2;row++)
	      {
		free(matrix2b[row]);
	      }
	    free(matrix2b);
	  }
	else
	  {
	    fprintf(stderr,"exit fail\n");
	    return EXIT_FAILURE;
	  }
      
      } 
   if(strcmp(argv[1],"-d") == 0)
    {
      if(argv[2] != NULL )
	{
	  double **matrix3 = Read_matrix_from_file(argv[2],&size3);
	  double result = Deviation_from_identity(matrix3,size3);
	  if( result == 0.0)
	    {
	       for (row = 0;row < size3;row++)
	    {
	      free(matrix3[row]);
	    }
	  free(matrix3);
	      fprintf(stderr,"exit fail\n");
	      return EXIT_FAILURE;
	    }
	  printf("%e\n", result); 
	  for (row = 0;row < size3;row++)
	    {
	      free(matrix3[row]);
	    }
	  free(matrix3);
	}
	else
	  {
	    fprintf(stderr,"exit fail\n");
	    return EXIT_FAILURE;
	  }
    } 



  return 0;
}
