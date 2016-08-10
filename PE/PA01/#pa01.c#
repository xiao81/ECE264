#include <stdio.h>
#include <stdlib.h>

// This includes the /definitions/ of the functions that you write
// in this assignment. Including the definitions allows you to use
// the functions in this file.

#include "answer01.h"

void printArray(int * array, int len)
{
    printf("{");
    int ind;
    for(ind = 0; ind < len; ++ind) {
	printf("%d", array[ind]);
	if(ind != len - 1) {
	    printf(", ");
	}
    }
    printf("}");
    // If we don't include a '\n' character, then we need to 
    // include this line to ensure that our output is immediately
    // printed out output.
    fflush(stdout); 
}

// Given a filename, this function reads the entries in the file 
// into an array, and returns the array and the size of the array
// the file is assumed to store only numbers.
// The function first determines the number of numbers in the file,
// then allocates the right array size, 
// and reads all the numbers into the array.
//
int *read_in_Array(char *filename, int *arraysize)
{
   if (filename == NULL) {
      *arraysize = 0;
      return NULL;
   } 
   // we have a valid filename
   // check if the file is present, open the file for read operation

   FILE *fp = fopen(filename, "r");
   if (fp == NULL) { // the file is not present, or we don't have the permission to read the file
      fprintf(stderr, "can't open input file, return NULL array\n");
      *arraysize = 0;
      return NULL;
   }

   // check the number of lines in the file

   int n_line = 0;
   while (!feof(fp)) { 
      int read_stat;
      int dummy;
      read_stat = fscanf(fp, "%d\n", &dummy);
      if (read_stat != 1) { // no number in that line, return NULL;
	 fprintf(stderr, "input file in wrong format, return NULL array\n");
	 fclose(fp);
         *arraysize = 0;
         return NULL;
      }
      n_line++;
   }
   if (fseek(fp, 0, SEEK_SET) != 0) { // unsuccessfully rewind to the beginning of file   
      fprintf(stderr, "can't rewind input file, return NULL array\n");
      fclose(fp);
      *arraysize = 0;
      return NULL;
   }
   int *array = (int *)malloc(sizeof(int) * n_line);
   if (array == NULL) { // no memory available
      fprintf(stderr, "no memory available, return NULL array\n");
      fclose(fp);
      *arraysize = 0;
      return NULL;
   }

   // now, we can fill in the array
   n_line = 0;
   while (!feof(fp)) {
      int read_stat;
      read_stat = fscanf(fp, "%d\n", &(array[n_line]));
      if (read_stat != 1) { // no number in that line, return NULL;
	 fprintf(stderr, "input file in wrong format, return NULL array\n");
	 free(array);
         fclose(fp);
         *arraysize = 0;
         return NULL;
      }
      n_line++;
   }
   fclose(fp);
   *arraysize = n_line;
   return array;
}

void test_arraySum(int * array, int len, int expected)
{
    printArray(array, len);
    int sum = arraySum(array, len);
    printf(". sum = %d, expected = %d.", sum, expected);
    if(sum != expected)
	printf(" FAIL");
    printf("\n");
}

void test_00_arraySum()
{
    printf("Testing arraySum(...)\n");

    // Here we use "static initialization" to create an array
    int array1[] = { -4, -1, 0, 1, 5, 10, 20, 21 };
    int len1 = 8;
    int expected1 = 52;
    test_arraySum(array1, len1, expected1);

    // Our functions must always work... even on empty arrays
    int array2[] = {};
    int len2 = 0;
    int expected2 = 0;
    test_arraySum(array2, len2, expected2);

    // You can add more test-cases here
    // ...

    printf("\n"); // Tidy output is easier to use
}

void test_arrayCountNegative(int * array, int len, int expected)
{
    printArray(array, len);
    int count = arrayCountNegative(array,len); 
    printf(". count = %d, expected = %d.", count, expected);
    if(count != expected)
	printf(" FAIL");
    printf("\n");
}

void test_01_arrayCountNegative()
{
    printf("Testing arrayCountNegative(...)\n");

    int array1[] = { 1, 4, -5, 4 };
    int len1 = 4;
    test_arrayCountNegative(array1, len1, 1);

    int array2[] = {};
    int len2 = 0;
    test_arrayCountNegative(array2, len2, 0);

    int array3[] = { 0, 1, 2, 3, 4 };
    int len3 = 5;
    test_arrayCountNegative(array3, len3, 0);

    int array4[] = { -1, -2, -3, -4 };
    int len4 = 4;
    test_arrayCountNegative(array4, len4, 4);
    // You can add more test-cases here
    // ...

    printf("\n");
}

void test_arrayIsIncreasing(int * array, int len, int expected)
{
    printArray(array, len);
    int count = arrayIsIncreasing(array,len);
    printf(". count = %d, expected = %d.", count, expected);
    if(count != expected)
  printf(" FAIL");
    printf("\n");
}

void test_02_arrayIsIncreasing()
{
    printf("Testing arrayIsIncreasing(...)\n");

    int array1[] = { 1, 1, 2, 3, 3 };
    int len1 = 5;
    test_arrayIsIncreasing(array1, len1, 1);

    int array2[] = {1, 2, 0, 4};
    int len2 = 4;
    test_arrayIsIncreasing(array2, len2, 0);

    int array3[] = { 0, 1, 2, -3, 4 };
    int len3 = 5;
    test_arrayIsIncreasing(array3, len3, 0);

    int array4[] = {};
    int len4 = 0;
    test_arrayIsIncreasing(array4, len4, 1);
    
    printf("\n");
}

void test_arrayFindSmallest(int * array, int len, int expected)
{
    printArray(array, len);
    int count = arrayFindSmallest(array,len);
    printf(". count = %d, expected = %d.", count, expected);
    if(count != expected)
  printf(" FAIL");
    printf("\n");
}

void test_03_arrayFindSmallest()
{
    printf("Testing arrayFindSmallest(...)\n");

    int array1[] = { 1, 1, 2, 3, 3 };
    int len1 = 5;
    test_arrayFindSmallest(array1, len1, 0);

    int array2[] = {3, 4, -5};
    int len2 = 4;
    test_arrayFindSmallest(array2, len2, 2);

    int array3[] = { 0, 1, 2, -3, 4 };
    int len3 = 5;
    test_arrayFindSmallest(array3, len3, 3);

    int array4[] = {};
    int len4 = 0;
    test_arrayFindSmallest(array4, len4, 0);

    printf("\n");
}

int main(int argc, char * * argv)
{
    printf("Welcome to ECE264, we are working on PA01.\n\n");

    // Uncomment to run two example (incomplete) testcases.
    if (argc < 2) {  // when no arguments are given, we are in test mode

    	test_00_arraySum();
    	test_01_arrayCountNegative();
      test_02_arrayIsIncreasing();
      test_03_arrayFindSmallest();
    } else { // now, try to parse the arguments and call the correct function

	int return_value = 0;
	int *array = NULL;
	int len = 0;

        // fill in the correct statements to complete the main function
	// we expect two arguments:
	//
	// the first argument is an integer from the sets {0, 1, 2, 3}
	// 0: run arraySum(int * array, int len)
	// 1: run arrayCountNegative(int * array, int len)
	// 2: run arrayIsIncreasing(int * array, int len)
	// 3: run arrayFindSmallest(int * array, int len)
	// otherwise: do nothing;
	// for the cases of first argument being 0, 1, 2, or 3,
	// store the results in the variable return_value, e.g., return_value = arraySum(...);
	// print the return_value using the statement printf("%d\n", return_value);
	// 
	// the second argument is a filename.  The function read_in_Array 
	// is called to fill in the array and to initialize len correctly.

	// check that we have an argument for the filename
	// call the function to fill in the array
		

        if (argc == 3) {
	    array = read_in_Array(argv[2], &len); 
	    printArray(array, len);
            
	} else {
	    return EXIT_FAILURE;
	} 

        // fill in the rest of the statements here
        // so that the correct function is called based on the first argument
        if ((int)strtol(argv[1], (char **)NULL,10)== 0) 
        {
           return_value = arraySum(array, len);
        }
        else if ((int)strtol(argv[1], (char **)NULL,10)== 1)
        {
           return_value = arrayCountNegative(array, len);
        }
        else if ((int)strtol(argv[1], (char **)NULL,10)== 2)
        {
           return_value = arrayIsIncreasing(array, len);
        }
        else if ((int)strtol(argv[1], (char **)NULL,10)== 3)
        {
           return_value = arrayFindSmallest(array, len);
        }











        // fill in the rest of the statements above this line

	printf("\n\n%d\n", return_value);

	if (array != NULL) {
	   free(array);
	}
    }
    return EXIT_SUCCESS;
}
