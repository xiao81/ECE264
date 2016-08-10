#include <stdlib.h>
#include <stdio.h>
#include "bmp.h"
#include <string.h>

int main(int argc, char * argv[])
{
 
 
  if(strcmp(argv[1],"-t") == 0)
    {
       if(argv[2] != NULL && argv[3] != NULL)
	{
	  FILE *fptr1 = fopen(argv[2],"rb");
	  FILE *fptr2 = fopen(argv[3],"wb");
	  BMP_Image *bmp_image = Read_BMP_Image(fptr1);
	  BMP_Image *bmp_image_top =Top_Half_BMP_Image(bmp_image);
	  Write_BMP_Image(fptr2, bmp_image_top); 
	  fclose(fptr1);
	  fclose(fptr2);
	  Free_BMP_Image(bmp_image_top);
	  Free_BMP_Image(bmp_image);
	}
       else
	{
          fprintf(stderr,"exit fail\n");
	  return EXIT_FAILURE;
	}
       
      
    }
  
  if(strcmp(argv[1],"-l") == 0)
    {
       if(argv[2] != NULL && argv[3] != NULL)
	{
	  FILE *fptr3 = fopen(argv[2],"rb");
	  FILE *fptr4 = fopen(argv[3],"wb");
	  BMP_Image *bmp_image = Read_BMP_Image(fptr3);
	  BMP_Image *bmp_image_left =Left_Half_BMP_Image(bmp_image);
	  Write_BMP_Image(fptr4,bmp_image_left); 
	   fclose(fptr3);
	   fclose(fptr4);
	   Free_BMP_Image(bmp_image_left);
	   Free_BMP_Image(bmp_image);
	}
       else
	{
          fprintf(stderr,"exit fail\n");
	  return EXIT_FAILURE;
	}
      
      
    }
  
  return 0;
}
