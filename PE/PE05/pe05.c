#include <stdio.h>
#include <stdlib.h>
#include "answer05.h"

int main(int argc, char * argv[])
{
  int nrow =0;
  int ncol =0;
  int col = 0;
  int cnt_g = 0;
  char re_c;
  char *filename = argv[2];
  int re =0;
  //int i;
  //int j; 

  FILE * fptr = fopen(argv[1], "r");
  Find_maze_dimensions(fptr,&nrow,&ncol);
  printf("nrow = %d\n",nrow);
  printf("ncol = %d\n",ncol);

  fseek(fptr, 0, SEEK_SET);
  col = Find_opening_location(fptr);
  printf("col = %d\n",col);

  fseek(fptr, 0, SEEK_SET);
  cnt_g = Count_grass_locations(fptr);
  printf("cnt_g = %d\n",cnt_g);

  fseek(fptr, 0, SEEK_SET);

 /* for(i=0;i < (nrow-1);i+=1)
  {
    for(j=0;j <(ncol-1);j+=1)
      {
        re_c = Get_location_type(fptr,i,j);
        printf("%c",re_c);
      }
  }*/
  re_c = Get_location_type(fptr,5,0);
  printf("re_cec = %c\n",re_c);

  fseek(fptr, 0, SEEK_SET);
  re = Represent_maze_in_one_line(filename, fptr);
  printf("re = %d\n",re);

  fclose(fptr);

  return 0;
}
