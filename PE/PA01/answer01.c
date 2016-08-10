#include <stdlib.h>
#include "answer01.h"

int arraySum(int * array, int len)
{
  int i;
  int sum;

  sum = 0;
  for(i = 0; i < len; i++)
  {
    sum = sum + array[i];
  }

    return sum;
}

int arrayCountNegative(int * array, int len)
{
  int j;
  int cnt;

  cnt = 0;
  for(j = 0; j < len; j++)
  {
    if(array[j] < 0)
    {
      cnt++;
    }
  }
  
  return cnt;
}

int arrayIsIncreasing(int * array, int len)
{
  int k;
  int inc;
  if(len == 0)
  {
    inc = 1;
  }
  else
  {
    inc = 1;
    for(k = 1; k < len; k++)
    {
      if(array[k-1] > array[k])
      {
        inc = 0;
      }
    }
  }
  
  return inc;
}

int arrayFindSmallest(int * array, int len)
{
	int l;
	int pos;
	int index;
	
	index = array[0];
  pos = 0;
	for(l = 0; l < len; l++)
	{
		if(array[l] < index)
		{
			pos = l;
		}
    }
    return pos;
}
