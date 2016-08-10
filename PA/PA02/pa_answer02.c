#include <stdio.h>
#include <stdlib.h>
#include "pa_answer02.h"


int Find_opening_location(FILE *fptr)
{  
   
   int col=0;
   char ch;
   
   fseek(fptr, 0, SEEK_SET);
   while ((ch = fgetc(fptr)) != EOF)
    {
       if(ch == CORN)
        {
          col+=1;
	}
	else
	{
          return col;
	}

     }
  return 0;
}

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
 
   return maze;
}

int Write_maze_to_2Dfile(FILE *nptr, char **maze, int nrow, int ncol) 
{
   int cnt = 0;
   int c;
   int i,j;
   
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
   

   return cnt;
}
void get_dir(char ** maze, FILE * outptr,int nrow,int ncol,int i,int j)
{
  if (i < nrow - 1 && maze[i+1][j] == GRASS)
    {
      
      fputc('S',outptr);
      maze[i+1][j] = MOWED;
      get_dir(maze,outptr,nrow,ncol,i+1,j);
      
      fputc('N',outptr);
      
    }
 if (j < ncol - 1 && maze[i][j+1] == GRASS)
    {
   
      fputc('E',outptr);
      maze[i][j+1] = MOWED;
      get_dir(maze,outptr,nrow,ncol,i,j+1);
     
      fputc('W',outptr);
      
    }
 if ( i > 0 && maze[i-1][j] == GRASS)
    {
    
      fputc('N',outptr);
      maze[i-1][j] = MOWED;
      get_dir(maze,outptr,nrow,ncol,i-1,j);
     
      fputc('S',outptr);
      
    }
 if (j > 0 && maze[i][j-1] == GRASS)
    {
    
      fputc('W',outptr);
      maze[i][j-1] = MOWED;
      get_dir(maze,outptr,nrow,ncol,i,j-1);
     
      fputc('E',outptr);
           
    }
 return;

}

void Get_mowing_directions(char *mazefile, char *directionfile)
{
  int nrow,ncol,open;
  int i=0;
  int j=0;
  char ** maze;
  FILE * inptr = fopen(mazefile,"r");
  FILE * outptr = fopen(directionfile,"w");
  
  if(inptr == NULL)
    {
      return;
    }
  
  if(outptr == NULL)
    {
      return;
    }
  
  open = Find_opening_location(inptr);
  maze = Read_maze_from_2Dfile(inptr,&nrow,&ncol);

  j = open;
  rewind(outptr);
  get_dir(maze,outptr,nrow,ncol,i,j);
  fclose(inptr);
  fclose(outptr);

 
  
  Deallocate_maze_space(maze,nrow);
  return;
  
}

int Simulate_mowing(char *mazefile, char *directionfile, char *mowedfile)
{
 int nrow,ncol,open;
  int i=0;
  int j=0;
  char ch;
  int c,cnt;

  char ** maze;
  FILE * inptr1 = fopen(mazefile,"r");
  FILE * inptr2 = fopen(directionfile,"r");
  FILE * outptr = fopen(mowedfile,"w");

  if(inptr1 == NULL)
    {
      return -1;
    }
  
  if(inptr2 == NULL)
    {
      return -1;
    }
  
  open = Find_opening_location(inptr1);
  maze = Read_maze_from_2Dfile(inptr1,&nrow,&ncol);

  j = open;
  rewind(inptr2);
  rewind(outptr);
  maze[0][open] = MOWED;
  cnt = 1;
  while((ch = fgetc(inptr2)) != EOF)
    {
      if(ch == 'N')
        {
	  if(i-1 < 0)
            {
              for(i=0;i<nrow;i++)
                {
                   for(j=0;j<ncol;j++)
		     {
                       printf("%c",maze[i][j]);
                     }
                   printf("\n");
                }
              return -1;
            }
          if(maze[i-1][j] ==CORN)
            {
             for(i=0;i<nrow;i++)
                {
                   for(j=0;j<ncol;j++)
		     {
                       printf("%c",maze[i][j]);
                     }
                   printf("\n");
                }
	      return -1;
            }
          maze[i][j] = MOWED;
          i-=1;
          cnt++;
        
        }
    else if(ch == 'S')
        {
	  if(i+1 > nrow - 1)
            {
             for(i=0;i<nrow;i++)
                {
                   for(j=0;j<ncol;j++)
		     {
                       printf("%c",maze[i][j]);
                     }
                   printf("\n");
                }
              return -1;
            }
          if(maze[i+1][j] ==CORN)
            {
             for(i=0;i<nrow;i++)
                {
                   for(j=0;j<ncol;j++)
		     {
                       printf("%c",maze[i][j]);
                     }
                   printf("\n");
                }
	      return -1;
            }
          maze[i][j] = MOWED;
          i+=1;
          cnt++;
        }
    else if(ch == 'W')
        {
	  if(j-1 < 0)
            {
             for(i=0;i<nrow;i++)
                {
                   for(j=0;j<ncol;j++)
		     {
                       printf("%c",maze[i][j]);
                     }
                   printf("\n");
                }
              return -1;
            }
          if(maze[i][j-1] ==CORN)
            {
             for(i=0;i<nrow;i++)
                {
                   for(j=0;j<ncol;j++)
		     {
                       printf("%c",maze[i][j]);
                     }
                   printf("\n");
                }
	      return -1;
            }
          maze[i][j] = MOWED;
          j-=1;
         cnt++;
        }
    else if(ch == 'E')
        {
	  if(j+1 > ncol - 1)
            {
             for(i=0;i<nrow;i++)
                {
                   for(j=0;j<ncol;j++)
		     {
                       printf("%c",maze[i][j]);
                     }
                   printf("\n");
                }
              return -1;
            }
          if(maze[i][j+1] ==CORN)
            {
             for(i=0;i<nrow;i++)
                {
                   for(j=0;j<ncol;j++)
		     {
                       printf("%c",maze[i][j]);
                     }
                   printf("\n");
                }
	      return -1;
            }
          maze[i][j] = MOWED;
          j+=1;
        cnt++;
        }
    else
      {
             for(i=0;i<nrow;i++)
                {
                   for(j=0;j<ncol;j++)
		     {
                       printf("%c",maze[i][j]);
                     }
                   printf("\n");
                }
	return -1;
      }

    }
  maze[i][j] = MOWED;
  cnt++;
  if(i != 0 || j != open)
    {
      c = Write_maze_to_2Dfile(outptr,maze,nrow,ncol); 
      return -1;
    }
 
  c = Write_maze_to_2Dfile(outptr,maze,nrow,ncol); 



  fclose(inptr1);
  fclose(inptr2);
  fclose(outptr);
  
  Deallocate_maze_space(maze,nrow);
  return cnt;



}
