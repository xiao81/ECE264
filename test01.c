#include <stdio.h>
#include <stdlib.h>
int swap1(int * a, int * b)
{
int *temp = a;
a = b;
b = temp; /* Questions 2.1 and 2.2 */
return *temp;
}
int swap2(int * a, int * b)
{
int temp = *a;
(*a) = (*b);
(*b) = temp; /* Question 2.1 */
return temp;
}
int swap3(int a, int b)
{
int temp = a;
a = b;
b = temp; /* Questions 2.1 and 2.3 */
return temp;
}
int main(int argc, char * argv[])
{
int i = 3, j = 4, k = 5;
k = swap1(&i, &j); /* Questions 2.1 and 2.2 */
k = swap2(&i, &j); /* Question 2.1 */
k = swap3(i, j); /* Questions 2.1 and 2.3 */
i = 3; j = 4;
printf("%d %d %d\n", i, j, swap2(&i, &j));
i = 3; j = 4;
printf("%d %d %d\n", swap2(&i, &j), i, j);
i = 3; j = 4;
printf("%d %d %d\n", i, swap2(&i, &j), j); /* Question 2.4 */
return 0;
}
