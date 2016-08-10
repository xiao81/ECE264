#include <stdio.h>
#include <stdlib.h>
#include "answer06.h"

int main(int argc, char * argv[])
{
  char **maze;
  char **maze_row;
  char **maze_col;
  int nrow,ncol;
  int rrow,rcol,crow,ccol;
  int cnt;
  
  char *filename1 = argv[2];
  char *filename2 = argv[3];
  FILE *fptr = fopen(argv[1],"r");
  
  maze = Read_maze_from_2Dfile(fptr,&nrow,&ncol);
  fclose(fptr);  

  maze_row = Expand_maze_row(maze,nrow,ncol,&rrow,&rcol);
  maze_col = Expand_maze_row(maze,nrow,ncol,&crow,&ccol);

  cnt = Write_maze_to_2Dfile(filename1,maze_row,rrow,rcol);
  cnt = Write_maze_to_2Dfile(filename2,maze_col,crow,ccol);
  
  Deallocate_maze_space(maze_col,crow); 
  Deallocate_maze_space(maze_row,rrow);  
  Deallocate_maze_space(maze,nrow);
  
  return 0;
}
