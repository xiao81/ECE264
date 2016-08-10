#include <stdlib.h>
#include <stdio.h>
#include "bmp.h"
#include <string.h>

int main(int argc, char * argv[])
{
  if(argc < 3)
    {
      fprintf(stderr,"exit fail\n");
      return EXIT_FAILURE;
    }

  FILE *fptr1 = fopen(argv[1],"rb");

  if(fptr1 != NULL)
    {     
      FILE *fptr2;
      BMP_Image *bmp_image = Read_BMP_Image(fptr1);
      if(bmp_image == NULL)
	{
	  fclose(fptr1);
	  return EXIT_FAILURE;
	}
      if(bmp_image->header.bits == 16)
	{
	  BMP_Image *bmp_image_24 =Convert_16_to_24_BMP_Image(bmp_image);
	  fptr2 = fopen(argv[2],"wb");
	  Write_BMP_Image(fptr2, bmp_image_24); 
	  fclose(fptr1);
	  fclose(fptr2);
	  Free_BMP_Image(bmp_image_24);
	  Free_BMP_Image(bmp_image);
	}
      else if(bmp_image->header.bits == 24)
	{
	  BMP_Image *bmp_image_16 =Convert_24_to_16_BMP_Image(bmp_image);
	  fptr2 = fopen(argv[2],"wb");
	  Write_BMP_Image(fptr2, bmp_image_16); 
	  fclose(fptr1);
	  fclose(fptr2);
	  Free_BMP_Image(bmp_image_16);
	  Free_BMP_Image(bmp_image);
	}
    }
  else
    {
      //fclose(fptr1);
      fprintf(stderr, "Error reading input file\n");
      return EXIT_FAILURE;
    }
       
      
  
  return 0;
}
