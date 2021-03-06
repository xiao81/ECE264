#include <stdlib.h>
#include <stdio.h>

#include "bmp.h"

/* check whether a header is valid
 * assume that header has been read from fptr
 * the position of the indicator of fptr is not certain
 * could be at the beginning of the file, end of the file or 
 * anywhere in the file
 * note that the check is only for this exercise/assignment
 * in general, the format is more complicated
 */

int Is_BMP_Header_Valid(BMP_Header* header, FILE *fptr) {
  // Make sure this is a BMP file
  if (header->type != 0x4d42) {
     return FALSE;
  }
  // skip the two unused reserved fields

  // check the offset from beginning of file to image data
  // essentially the size of the BMP header
  // BMP_HEADER_SIZE for this exercise/assignment
  if (header->offset != BMP_HEADER_SIZE) {
     return FALSE;
  }
      
  // check the DIB header size == DIB_HEADER_SIZE
  // For this exercise/assignment
  if (header->DIB_header_size != DIB_HEADER_SIZE) {
     return FALSE;
  }

  // Make sure there is only one image plane
  if (header->planes != 1) {
    return FALSE;
  }
  // Make sure there is no compression
  if (header->compression != 0) {
    return FALSE;
  }

  // skip the test for xresolution, yresolution

  // ncolours and importantcolours should be 0
  if (header->ncolours != 0) {
    return FALSE;
  }
  if (header->importantcolours != 0) {
    return FALSE;
  }
  
  // Make sure we are getting 24 bits per pixel
  // or 16 bits per pixel
  // only for this assignment
  if (header->bits != 24 && header->bits != 16) {
    fprintf(stderr, "Image not in 16 bit format or 24 bit format.  Can't convert.\n");
    return FALSE;
  }

  // fill in extra to check for file size, image size
  // based on bits, width, and height
  int padding=0;
  if(header->width*(header->bits/8) % 4 !=0)
    {
      padding = 4 - header->width*(header->bits/8) % 4;
    }
  if(padding != 0)
    {
  if (header->imagesize != (header->width*(header->bits/8)+padding)*header->height){ 
    return FALSE;
    }
    }
  if (header->size != header->imagesize + BMP_HEADER_SIZE){
    return FALSE;
  }
 
    fseek(fptr,0,SEEK_END);
  if(ftell(fptr) != header->size)
    {  
      return FALSE;
      }
  
  return TRUE;
}

/* The input argument is the source file pointer. 
 * The function returns an address to a dynamically allocated BMP_Image only 
 * if the file * contains a valid image file 
 * Otherwise, return NULL
 * If the function cannot get the necessary memory to store the image, also 
 * return NULL
 * Any error messages should be printed to stderr
 */
BMP_Image *Read_BMP_Image(FILE* fptr) {

  rewind(fptr);
  if(fptr == NULL)
    {
      fprintf(stderr, "Can't open input file.\n");
      return NULL;
    }
  //Allocate memory for BMP_Image*;
   BMP_Image *bmp_image = (BMP_Image *)malloc(sizeof(BMP_Image));   
   if(bmp_image == NULL)
     {
       fprintf(stderr, "Error allocating memory\n");
       return NULL;
     }

  //Read the first 54 bytes of the source into the header
  BMP_Header* bheader = &(bmp_image->header);
  int n_read = fread(bheader,BMP_HEADER_SIZE,1,fptr);
  int check=0; 
  //printf("read in %d header\n",n_read);
  
  // if read successful, check validity of header
  if(n_read == 1)
    {
      check = Is_BMP_Header_Valid(bheader,fptr);
    }
  else
    {
      fprintf(stderr, "Can't read image from file\n");
      free(bmp_image);
      return NULL;	
    }
  if(check == FALSE)
    {
      fprintf(stderr, "Input file not in expected format\n");
      free(bmp_image);
      return NULL;
    }
   fseek(fptr,54,SEEK_SET);
 
  // Allocate memory for image data
  bmp_image->data = (unsigned char *)malloc(bheader->imagesize);
  
  // read in the image data
 
  n_read = fread(bmp_image->data,sizeof(unsigned char),bheader->imagesize,fptr);
  //printf("read in %d bytes\n",n_read);

  return bmp_image;
}

/* The input arguments are the destination file pointer, BMP_Image *image.
 * The function write the header and image data into the destination file.
 * return TRUE if write is successful
 * FALSE otherwise
 */
int Write_BMP_Image(FILE* fptr, BMP_Image* image) 
{
  rewind(fptr);
  if(fptr == NULL)
    {
      fprintf(stderr, "Can't open file for output\n");
      return FALSE;
    }
  if(image == NULL)
    {
      fprintf(stderr, "Error reading input file\n");
      return FALSE;
    }
 
   // write header
  BMP_Header* bheader = &(image->header);
  int n_write = fwrite(bheader,BMP_HEADER_SIZE,1,fptr);
 
  // printf("write in %d header\n",n_write);
 
   // write image data
  n_write = fwrite((const void*)image->data,sizeof(unsigned char),image->header.imagesize,fptr);
  // printf("write in %d bytes\n",n_write);

  return TRUE;
}

/* The input argument is the BMP_Image pointer. The function frees memory of 
 * the BMP_Image.
 */
void Free_BMP_Image(BMP_Image* image) {
  free(image->data);
  free(image);

  return;

}

/* Given a BMP_Image, create a new image that retains top half of the 
 * given image
 */
BMP_Image *Top_Half_BMP_Image(BMP_Image *image)
{
  int i;
  BMP_Image *image_top = (BMP_Image *)malloc(sizeof(BMP_Image));   
  
  if(image_top == NULL)
    {
      fprintf(stderr, "Error allocating memory\n");
      return NULL;
    }

  
      image_top->header = image->header;
    
  if(image->header.height % 2 == 0)
    {
      image_top -> header.height /= 2;
      image_top -> header.imagesize /= 2;
      image_top -> header.size =  image_top -> header.imagesize + BMP_HEADER_SIZE;
	}
  else
    {
      image_top -> header.height = (image_top -> header.height-1)/2+1;
      image_top -> header.imagesize = ((image->header.imagesize)/(image->header.height)*image_top->header.height);
      image_top -> header.size =  image_top -> header.imagesize + BMP_HEADER_SIZE;
    }
  image_top->data = (unsigned char *)malloc(image_top ->header.imagesize);
  if(image_top->header.height %2 == 0)
    {
  for(i=0;i<(image_top->header.imagesize);i++)
    {
      image_top -> data[i] = image -> data[i+image_top->header.imagesize];
    }
    }
  else
    {
      for(i=0;i<(image_top->header.imagesize);i++)
    {
      image_top -> data[i] = image -> data[i+(image->header.imagesize-image_top->header.imagesize)];
    }
    }
    

   
   return image_top;
}

/* Given a BMP_Image, create a new image that retains left half of the given 
 * image
 */
BMP_Image *Left_Half_BMP_Image(BMP_Image *image)
{
  int i,j;
  int padding =0;
  BMP_Image *image_left = (BMP_Image *)malloc(sizeof(BMP_Image));   
  
  if(image_left == NULL)
    {
      fprintf(stderr, "Error allocating memory\n");
      return NULL;
    }

  
      image_left->header = image->header;
    
      if(image->header.width % 2 == 0)
    {
      image_left -> header.width /= 2;
      
      if(image_left->header.width*(image_left->header.bits/8) % 4 !=0)
	{
	  padding = 4 - image_left->header.width*(image_left->header.bits/8) % 4;
	}

      image_left -> header.imagesize = (image_left->header.width*(image_left->header.bits/8)+padding)*image_left->header.height;
      image_left -> header.size =  image_left -> header.imagesize + BMP_HEADER_SIZE;
	}
  else
    {
      image_left -> header.width = (image_left -> header.width-1)/2+1;

      if(image_left->header.width*(image_left->header.bits/8) % 4 !=0)
	{
	  padding = 4 - image_left->header.width*(image_left->header.bits/8) % 4;
	}

      image_left -> header.imagesize = (image_left->header.width*(image_left->header.bits/8)+padding)*image_left->header.height;
      image_left -> header.size =  image_left -> header.imagesize + BMP_HEADER_SIZE;
    }
      image_left->data = (unsigned char *)malloc(image_left ->header.imagesize);
      
      unsigned char (*new)[image_left -> header.imagesize/image_left->header.height]= (unsigned char (*)[image_left -> header.imagesize/image_left->header.height])image_left->data;
      unsigned char (*src)[image -> header.imagesize/image->header.height] = (unsigned char (*)[image -> header.imagesize/image->header.height])image->data;

      for(i=0;i<image_left->header.height;i++)
	{
	  for(j=0;j<image_left->header.width*(image_left->header.bits/8);j++)
	    {
	      new[i][j] = src[i][j];
	    }
	  for(;j<image_left->header.width*(image_left->header.bits/8)+padding;j++)
	    {
	      new[i][j]=0;
	    }

	}
      for(i=0;i<image_left->header.imagesize;i++)
	{
	  image_left->data[i] = ((unsigned char *)new)[i];
	}
      return image_left;
}


BMP_Image *Convert_24_to_16_BMP_Image(BMP_Image *image)
{
// Given a BMP_Image, create a new 16-bit image that is converted from a given 
// 24-bit image
  int i,j,k,m=0;
  int padding1 =0;
  int padding2 =0;
  BMP_Image *image_16 = (BMP_Image *)malloc(sizeof(BMP_Image));   
 
  if(image_16 == NULL)
    {
      fprintf(stderr, "Error allocating memory\n");
      return NULL;
    }

      image_16->header = image->header;
      image_16 -> header.bits =16;
      
      if(image_16->header.width*(image_16->header.bits/8) % 4 !=0)
	{
	  padding1 = 4 - image_16->header.width*(image_16->header.bits/8) % 4;
	}
      if(image->header.width*(image->header.bits/8) % 4 !=0)
	{
	  padding2 = 4 - image->header.width*(image->header.bits/8) % 4;
	}

      image_16 -> header.imagesize = (image_16->header.width*(image_16->header.bits/8)+padding1)*image_16->header.height;
      image_16 -> header.size =  image_16 -> header.imagesize + BMP_HEADER_SIZE;

      image_16->data = (unsigned char *)malloc(image_16 ->header.imagesize);

      unsigned char new_b,new_g,new_r;
      unsigned char buf[2];
      uint16_t new_colour; 
      int width24 = image->header.width*(image->header.bits/8);

      for(i=0;i<image->header.height;i++)
	{
	  for(j=0;j<(width24);j+=3)
	    {
	      new_b = image->data[j+width24*i+padding2*i]>>3;
	      new_g = image->data[j+1+width24*i+padding2*i]>>3;
	      new_r = image->data[j+2+width24*i+padding2*i]>>3;
	      new_colour = ((new_r<<RED_BIT)|(new_g<<GREEN_BIT)|new_b);
	  
	      buf[0]=(new_colour);
	      buf[1]=(new_colour>>8);
	      
	      image_16->data[m]=buf[0];
	      m++;
	      image_16->data[m]=buf[1];
	      m++;
		    
	    }
	  if(padding1!=0)
	    {
	      for(k=0;k<padding1;k++)
		{
		  image_16->data[m] = 0;
		  m++;
		}
	    }
	}
      return image_16;
}

BMP_Image *Convert_16_to_24_BMP_Image(BMP_Image *image)
{
  int i,j,k,m=0;
  int padding1 =0;
  int padding2 =0;
  BMP_Image *image_24 = (BMP_Image *)malloc(sizeof(BMP_Image));   
 
  if(image_24 == NULL)
    {
      fprintf(stderr, "Error allocating memory\n");
      return NULL;
    }

      image_24->header = image->header;
      image_24 -> header.bits =24;
      
      if(image_24->header.width*(image_24->header.bits/8) % 4 !=0)
	{
	  padding1 = 4 - image_24->header.width*(image_24->header.bits/8) % 4;
	}
      if(image->header.width*(image->header.bits/8) % 4 !=0)
	{
	  padding2 = 4 - image->header.width*(image->header.bits/8) % 4;
	}

      image_24 -> header.imagesize = (image_24->header.width*(image_24->header.bits/8)+padding1)*image_24->header.height;
      image_24 -> header.size =  image_24-> header.imagesize + BMP_HEADER_SIZE;

      image_24->data = (unsigned char *)malloc(image_24 ->header.imagesize);

      unsigned char new_b,new_g,new_r;
      unsigned char buf[2];
      uint16_t pixel;
      int width16 = image->header.width*(image->header.bits/8);

      for(i=0;i<image->header.height;i++)
	{
	  for(j=0;j<(width16);j+=2)
	    {
	      buf[0] = image->data[j+ i*(width16+padding2)+1];
	      buf[1] = image->data[j+ i*(width16+padding2)];
	      
	      pixel = (buf[0]<<8)|buf[1];
	      
	      new_r = (pixel & RED_MASK)>>10;
	      new_g = (pixel & GREEN_MASK)>>5;
	      new_b = (pixel & BLUE_MASK);

	      new_r = (new_r)*255/31;
	      new_g = (new_g)*255/31;
	      new_b = (new_b)*255/31;
              
	      image_24->data[m] = new_b;
	      m++;
	      image_24->data[m] = new_g;
	      m++;
	      image_24->data[m] = new_r;
	      m++;	      
	    
	    }
	  if(padding1!=0)
	    {
	      for(k=0;k<padding1;k++)
		{
		  image_24->data[m] = 0;
		  m++;
		}
	    }
	}

  return image_24;
}
