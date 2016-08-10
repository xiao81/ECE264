#include <stdio.h>
#include <stdlib.h>
#include "list_tree.h"


int main(int argc,char **argv)
{
  if(argc!=3){
    fprintf(stderr,"Incorrect number of arguments\n");
    return EXIT_FAILURE;
  }
  FILE *infptr=fopen(argv[1],"r");
  if(infptr ==NULL){
    fprintf(stderr,"Can't open input file\n");
    return EXIT_FAILURE;
  }
  tnode*huffman =Build_huffman_tree(infptr);
  fclose(infptr);
  if(huffman ==NULL){
    fprintf(stderr,"Can't build tree\n");
    return EXIT_FAILURE;
  }
  //printout
  FILE *outfptr =fopen(argv[2],"w");
  if(outfptr ==NULL){
    fprintf(stderr,"Can't open output file\n");
    fprintf(stderr,"Redirect to stdout\n");
    outfptr = stdout;
}
    int array[ASCII_COUNT];
    post_order_print(huffman,outfptr,array,0);

    if(outfptr != stdout)
      {
	fclose(outfptr);
      }
    tree_destruct(huffman);
    return EXIT_SUCCESS;
}


