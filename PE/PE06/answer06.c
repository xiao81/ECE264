#include <stdio.h>
#include <stdlib.h>
#include "answer06.h"

// if you want to declare and define new functions, put them here
// or at the end of the file


// do not remove #ifndef and #endif in this file, otherwise the evaluation
// would fail and you would definitely get 0
// any new functions you want to create and use in this file 
// should appear above these comments or at the end of this file

#ifndef NTEST_ALLOC

// allocate space for nrow x ncol maze, if allocation fails, return NULL
// if allocation fails, you are also responsible for freeing the memory
// allocated before the failure

char **Allocate_maze_space(int nrow, int ncol)
{
   char ** arr;
   int row;
   int cnt;
   arr = (char **)malloc(nrow * sizeof(char *));
   if (arr == 0)
     {
       free(arr);
       fprintf(stderr, "memory allocation fail\n");
       return NULL;
     }
   
   for (row = 0;row < nrow;row++)
     {
       arr[row] = (char *)malloc(ncol * sizeof(char));
       if (arr[row] == 0)
       {
         cnt = row;
         for (row = 0;row <= cnt;row++)
           {
             free(arr[row]);
           }
         free(arr);
         fprintf(stderr, "memory allocation fail\n");
         return NULL;
       }
     }
   
   return arr;
}

#endif /* NTEST_ALLOC */

#ifndef NTEST_DEALLOC

// free the memory used for the maze
// you may assume that maze is not NULL, and all memory addresses are valid

void Deallocate_maze_space(char **maze, int nrow) 
{
   int row;
   for (row = 0;row < nrow;row++)
     {
       free(maze[row]);
     }
   free(maze);
   return;
}

#endif /* NTEST_DEALLOC */

#ifndef NTEST_READ2D

/* Read maze in a multi-line file into a 2D array of characters */
/* you may assume that the maze has odd row and column counts */

char **Read_maze_from_2Dfile(FILE *fptr, int *nrow, int *ncol)
{
   char val;
   char ** maze;
   int i;
   int j;
   *nrow = *ncol = 0;
   fseek(fptr, 0, SEEK_SET);
   while ((val = fgetc(fptr)) != EOF)
     {
       if(val == '\n')
        {
          *nrow+=1;
        }
        else
        {
          *ncol+=1;
        }

     }

   *ncol = (*ncol)/(*nrow);
   maze = Allocate_maze_space(*nrow,*ncol);
 
   fseek(fptr, 0, SEEK_SET);
   for (i=0;i<*nrow;i++)
     {
       for (j=0;j<*ncol;j++)
         {
           val = fgetc(fptr);
           if (val == '\n')
             {
                
                val = fgetc(fptr);
             }
           maze[i][j] = val;
         }
     }
   //Deallocate_maze_space(maze,*nrow);
   return maze;
}

#endif /* NTEST_READ2D */

#ifndef NTEST_WRITE2D

/* Write maze in a 2D array of characters into a multi-line file */
/* you may assume that the maze has odd row and column counts */

int Write_maze_to_2Dfile(char *filename, char **maze, int nrow, int ncol) 
{
   int cnt = 0;
   int c;
   int i,j;
   FILE *nptr = fopen(filename,"w");
   fseek(nptr,0,SEEK_SET);
    for (i=0;i<nrow;i++)
     {
       if (i>0 && i<nrow)
         {
           c = fputc('\n',nptr);
           cnt++;
         }
       for (j=0;j<ncol;j++)
         {
           c = fputc(maze[i][j],nptr);
           cnt++;  
         }
     }
     c = fputc('\n',nptr);
     cnt++;
   fclose(nptr);

   return cnt;
}

#endif /* NTEST_WRITE2D */

#ifndef NTEST_EXPANDROW

/* Expand the maze from nrow x ncol to (2nrow - 1) x ncol */
/* the top half of the maze is the same as the original maze */
/* the bottom half of the maze is a reflection of the original maze */
/* *rrow and *rcol have to be updated with the new row and column counts */
/* You have to create a new maze */
/* if you can't expand the maze because of memory issue, NULL should be */
/* returned, and both *rrow and *rcol set to 0 */
/* the original maze has to stay intact */
/* you may assume that the original maze has odd row and column counts */

char **Expand_maze_row(char **maze, int nrow, int ncol, int *rrow, int *rcol)
{
   char** maze_row;
   int row;
   int cnt;
   int i,j;
   *rrow = *rcol = 0;
   *rrow = 2 * (nrow) - 1;
   *rcol = ncol;

   maze_row = (char **)malloc((*rrow) * sizeof(char *));
   if (maze_row == NULL)
    {
      free(maze_row);
      fprintf(stderr, "memory allocation fail\n");
      *rrow = *rcol = 0;
      return NULL;
    } 

   for (row = 0;row < *rrow;row++)
     {
       maze_row[row] = (char *)malloc((*rcol) * sizeof(char));
       if (maze_row[row] == NULL)
         {
           cnt = row;
           for (row = 0;row <= cnt;row++)
             {
               free(maze_row[row]);
             }
           free(maze_row);
           fprintf(stderr, "memory allocation fail\n");
           *rrow = *rcol =0;
           return NULL;
         } 
     }
    for (i=0;i<nrow;i++)
      {
       for (j=0;j<ncol;j++)
         {
           maze_row[i][j] = maze[i][j];
         }
      }
   
  
    for (i=1;i<nrow;i++)
       { 
         for (j=0;j<ncol;j++)
           {
             maze_row[i+nrow-1][j]=maze[nrow-i-1][j];
           }
       }
    
   
    


   return maze_row;
}

#endif /* NTEST_EXPANDROW */

#ifndef NTEST_EXPANDCOL 

/* Expand the maze from nrow x ncol to nrow x 2ncol - 1 */
/* the left half of the maze is the same as the original maze */
/* the right half of the maze is a reflection of the original maze */
/* moreover, you have to create an opening between the left and right halves */
/* the opening should be at the middle row of the maze */
/* the opening must also be accessible from one of the grass-paths in the */
/* new maze */
/* to do that, you have to convert some locations with corns to grass */
/* starting from the new opening to the left and to the right until you reach */
/* a location that is adjacent to a location that has grass */
/*                                                                       */
/* *crow and *ccol have to be updated with the new row and column counts */
/* You have to create a new maze */
/* if you can't expand the maze because of memory issue, NULL should be */
/* returned, and both *crow and *ccol set to 0 */
/* the original maze has to stay intact */
/* you may assume that the original maze has odd row and column counts */

char **Expand_maze_column(char **maze, int nrow, int ncol, int *crow, int *ccol)
{
   char** maze_col;
   int row;
   int cnt;
   //int i,j;
   *crow = *ccol = 0;
   *ccol = 2 * (ncol) - 1;
   *crow = nrow;

   maze_col = (char **)malloc((*crow) * sizeof(char *));
   if (maze_col == NULL)
    {
      free(maze_col);
      fprintf(stderr, "memory allocation fail\n");
      *crow = *ccol = 0;
      return NULL;
    } 

   for (row = 0;row < *crow;row++)
     {
       maze_col[row] = (char *)malloc((*ccol) * sizeof(char));
       if (maze_col[row] == NULL)
         {
           cnt = row;
           for (row = 0;row <= cnt;row++)
             {
               free(maze_col[row]);
             }
           free(maze_col);
           fprintf(stderr, "memory allocation fail\n");
           *crow = *ccol =0;
           return NULL;
         } 
     }
   return maze_col;
}

#endif /* NTEST_EXPANDCOL */

// if you want to declare and define new functions, put them here
// or at the beginning of the file
