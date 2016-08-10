#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "answer04.h"

int main(int argc, char *argv[])
{
   Initialize_counter();
 
   printf("Welcome to ECE264, we are working on PE04.\n\n");

   if (argc != 2) {
      return EXIT_FAILURE;
   }
   int n = atoi(argv[1]);
   if (n < 0) {
      return EXIT_FAILURE;
   }
   unsigned long ans = Fibonacci(n);
   printf("%lu\n", ans);
   printf("%d\n", Get_counter());
   return EXIT_SUCCESS;
}
