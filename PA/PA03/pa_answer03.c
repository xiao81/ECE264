#include <stdio.h>
#include <stdlib.h>
#include "pa_answer03.h"

/* check whether a value is sufficiently small */
/* to be considered 0 */

int Is_zero(double value)
{
   if (value < 0) {
      value = -value;
   }
   if (value < TOL) {
      return 1;
   } else {
      return 0;
   }
}

/* read a matrix from a file, return the matrix */
/* store the size of the matrix in *size        */

double **Read_matrix_from_file(char *filename, int *size)
{ 
  double **matrix;
  int row,cnt,n_read;
  
   FILE * fptr = fopen(filename,"rb");
   if (fptr == NULL)
     {
       fprintf(stderr,"cannot read file %s\n", filename);
       return NULL;
     }
   fread(size,sizeof(int),1,fptr);

   matrix = (double **)malloc((*size) * sizeof(double *));
   if (matrix == NULL)
     {
       free(matrix);
       fprintf(stderr, "memory allocation fail\n");
       return NULL;
     }
   
   for (row = 0;row < *size;row++)
     {
       matrix[row] = (double *)malloc((*size) * sizeof(double));
       n_read = fread(matrix[row], sizeof(double),(*size),fptr);
       if (matrix[row] == NULL)
       {
         cnt = row;
         for (row = 0;row <= cnt;row++)
           {
             free(matrix[row]);
           }
         free(matrix);
         fprintf(stderr, "memory allocation fail\n");
         return NULL;
       }
     }
 
   printf("%d successfully read from file\n", n_read);
   
   
   fclose(fptr);	
   return matrix;
}

/* write a matrix of a given size to a file, return 1 if the write is */
/* successful, otherwise, 0 */

int Write_matrix_to_file(char *filename, double **matrix, int size)
{
  FILE * fptr = fopen(filename,"wb");
  int row,n_write;
   if (fptr == NULL)
     {
       fprintf(stderr,"cannot write file %s\n", filename);
       return 0;
       }
    fwrite(&size,sizeof(int),1,fptr);
    for (row = 0;row < size;row++)
     {
        n_write = fwrite(matrix[row], sizeof(double),(size),fptr);
     }
   printf("%d successfully write into file\n", n_write);
   fclose(fptr);
   return 1;
}

/* invert a matrix of a given size */
/* if inversion is successful, return the inverse */
/* otherwise, return NULL */

double **Invert_matrix(double **matrix, int size)
{
  int i,j,k,row,cnt;
  double temp,temp2,temp3;
  double **matrix_new;

   matrix_new = (double **)malloc((size) * sizeof(double *));
   if (matrix_new == NULL)
     {
       free(matrix_new);
       fprintf(stderr, "memory allocation fail\n");
       return NULL;
     }
   
   for (row = 0;row < size;row++)
     {
       matrix_new[row] = (double *)malloc((size) * 2 * sizeof(double));
      
       if (matrix_new[row] == NULL)
       {
         cnt = row;
         for (row = 0;row <= cnt;row++)
           {
             free(matrix_new[row]);
           }
         free(matrix_new);
         fprintf(stderr, "memory allocation fail\n");
         return NULL;
       }
     }

   
   for (i = 0; i <size; i++)
    {
      for(j = 0; j <size;j++)
        {
	  matrix_new[i][j] = matrix[i][j];
	}
    }

  for (i = 0; i <size; i++)
    {
      for(j = 0; j <size;j++)
        {
          if(j == i)
	    {
              matrix_new[i][j+size] = 1;
            }
          else
	    {
	      matrix_new[i][j+size] = 0;
	    }
          
	}
    }
  /*
  j=0;
  for (i=0;i<size;i++)
      {
	if(matrix_new[i][j] < 0.0 && matrix_new[i][j] != 0.0 )
       for (j=0;j<size*2;j++)
	 {
           if(matrix_new[i][j] != 0.0)
	     {
               matrix_new[i][j]*= -1.0;
             }
	 }
      }
    }	   */
for(k=0;k<size;k++)
  {
   j=0;
    for(i = 1; i < size ; i++)
    {

      if(matrix_new[i-1][k] < matrix_new[i][k])
	{
	  for(j = 0; j < size*2; j++)
	    {
	     temp = matrix_new[i][j];
              matrix_new[i][j] = matrix_new[i-1][j];
              matrix_new[i-1][j] = temp;
              
	    }
	}
	}
  }
    /* for(i= 0;i<size;i++)
    {
      if(matrix_new[i][i] == 0)
	{
          
	      for(j = 0; j < size*2; j++)
		{
		  temp = matrix_new[i][j];
		  matrix_new[i][j] = matrix_new[size-1][j];
		  matrix_new[size-1][j] = temp;
		}
	     
	      
        
	}
	}*/
   for(i = 0;i<size;i++)
    {
      if(Is_zero(matrix_new[i][i]) == 1)
        {
	  for (row = 0;row < size;row++)
	    {
	      free(matrix_new[row]);
	    }
	  free(matrix_new);

          return NULL;
        }
    }

  for(i = 0; i < size; i++)
    {
     for(j = 0; j < size; j++)
       {
         if(j!= i)
	   {
	     temp2 = matrix_new[j][i];
             for (k = i; k< size*2;k++)
	       {
                
		 matrix_new[j][k] -= temp2/matrix_new[i][i]*matrix_new[i][k];
              
               }
	   }
       
       }
    }
  
  for(i = 0; i<size;i++)
    {
      temp3=matrix_new[i][i];
      for(j= 0; j< size*2;j++)
        {
	matrix_new[i][j] = matrix_new[i][j]/temp3;
	}
    }

 
 for (i=0;i<size;i++)
      {
       for (j=0;j<size;j++)
         {
           matrix[i][j] = matrix_new[i][j+size];
         }
     
      }
  

    
   for (row = 0;row < size;row++)
     {
       free(matrix_new[row]);
     }
   free(matrix_new);

   return matrix;
}

/* multiply two matrices of the same size */
/* if the multiplication is successful, return the results */

double **Matrix_matrix_multiply(double **matrixa, double **matrixb, int size)
{
  int i,j,k,row,cnt;
   double ** matrix = (double **)malloc((size) * sizeof(double *));
   if (matrix== NULL)
     {
       free(matrix);
       fprintf(stderr, "memory allocation fail\n");
       return NULL;
     }
   
   for (row = 0;row < size;row++)
     {
       matrix[row] = (double *)malloc((size) * sizeof(double));
      
       if (matrix[row] == NULL)
       {
         cnt = row;
         for (row = 0;row <= cnt;row++)
           {
             free(matrix[row]);
           }
         free(matrix);
         fprintf(stderr, "memory allocation fail\n");
         return NULL;
       }
     }
   for(i=0;i < size;i++)
     {
       for(j=0;j < size;j++)
	 {
	   for(k=0;k<size;k++)
	     {
               matrix[i][j] += matrixa[i][k]*matrixb[k][j];
	     }
	 }
     }
   return matrix;
}

/* return the sum of the absolute differences between the */
/* entries of a matrix of a given size and the corresponding */
/* entries of an identity matrix of the same size */

double Deviation_from_identity(double **matrix, int size)
{
   int i,j,row,cnt;
   double sum=0;
   double ** matrix_i = (double **)malloc((size) * sizeof(double *));
   if (matrix_i== NULL)
     {
       free(matrix_i);
       fprintf(stderr, "memory allocation fail\n");
       return 0.0;
     }
   
   for (row = 0;row < size;row++)
     {
       matrix_i[row] = (double *)malloc((size) * sizeof(double));
      
       if (matrix_i[row] == NULL)
       {
         cnt = row;
         for (row = 0;row <= cnt;row++)
           {
             free(matrix_i[row]);
           }
         free(matrix_i);
         fprintf(stderr, "memory allocation fail\n");
         return 0.0;
       }
     }
   for (i = 0; i <size; i++)
    {
      for(j = 0; j <size;j++)
        {
          if(j == i)
	    {
              matrix_i[i][j] = 1.0;
            }
          else
            {
              matrix_i[i][j] =0.0;
	    }
	}
    }
  for (i = 0; i <size; i++)
    {
      for(j = 0; j <size;j++)
        {
          if(matrix_i[i][j] - matrix[i][j] > 0)
	    {
	       sum +=(matrix_i[i][j] - matrix[i][j]);
	    }
          if(matrix_i[i][j] - matrix[i][j] < 0)
	    {
	       sum -=(matrix_i[i][j] - matrix[i][j]);
	    }
	}
    } 
 for (row = 0;row < size;row++)
	    {
	      free(matrix_i[row]);
	    }
	  free(matrix_i);
   return sum;
}
