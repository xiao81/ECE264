#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>
#include "pa_answer01.h"

int char_to_int(char c)
{
   int n = 37;
   // what if c is '0'--'9'
   if((int)c >= '0' && (int)c <= '9')
   {
     n = (int)c - 48;
   }

   // what if c is 'a'--'z'
   if((int)c >= 'a' && (int)c <= 'z')
   {
     n = (int)c - 87;
   }

   // what if c is 'A'--'Z'
   if((int)c >= 'A' && (int)c <= 'Z')
   {
     n = (int)c - 55;
   }

   // otherwise
   if(n == 37)
   {
     n = 37;
   }

   return n;
}

// you should try to re-use a majority of the algorithms in PE02
// for this programming assignment.
// However, you have to take care of endptr, base 0, and base 16
// these are the three additional things you have to deal with in
// this assignment, as compared to the str_to_long_int function
// that you wrote for PE02.
//
// it is really IMPORTANT that you extensively try out the function
// strtol on your own.
//
long int my_strtol(const char *nptr, char **endptr, int base)
{
   long int ret_value = 0;  // return value
   long int cnt = 0;
   long int compare = 0;
   int sign = 1;
  

   // if invalid base, set errno and return immediately
   if((base < 2 || base > 36) && base != 0)
     {
       errno = EINVAL;
       return(ret_value);
     }

   // valid base, skip over white space
   while(isspace(nptr[cnt]))
     {
       cnt++;
     }

   // if encounter a sign, expect a number after that 
   // if a negative sign is encountered, change the sign
   if((int)nptr[cnt] == '+')
       {
         sign = 1;
         cnt++;
       }
     if((int)nptr[cnt] == '-')
       {
         sign -= 2;
         cnt++;
       }
   
   // the exact algorithm is not given, but these are 
   // the tasks the function has to perform:  
   //
   // determine the actual base if the base is 0
   // if it starts with '0', it is octal
   // if '0' is followed by 'x' or 'X' it is hexadecimal or base 16
   // otherwise, it is decimal
   // therefore you have to determine the actual base and the starting
   // location to perform conversion
   //
   // for bases 2 to 15, perform conversion as in PE02
   //
   // for base 16, you have to decide when the conversion should
   // start: after the optional "0x" or "0X" or immediately
   // question: if you have "0xG", what should be converted?
   //
   // for bases 17 to 36, perform conversion as in PE02
   // 
   // after you have determine the real base, and where to start,
   // perform the conversion
   if(base == 0)
     {
       base = 10;
       if((int)nptr[cnt] == '0')
         { 
           base = 8;
           
   	   if ((int)nptr[cnt+1] == 'x' || (int)nptr[cnt+1] == 'X')
             {
		base = 16;
             }
         }   
     }
   if(base == 16)
     {
       if((int)nptr[cnt] == '0' && ((int)nptr[cnt+1] == 'x' || (int)nptr[cnt+1] == 'X'))
         {
  	   cnt += 2;
         }
     }
    while(nptr[cnt] != '\0' && char_to_int(nptr[cnt]) < base)
     {
       compare = ret_value;
       ret_value = ret_value * base + char_to_int(nptr[cnt]);
   
       if(ret_value < compare && sign == 1)
         {
           ret_value = LONG_MAX;
           errno = ERANGE;
	    while(nptr[cnt] != '\0')
             {
	       cnt++;
             }
           *endptr = (char *)&(nptr[cnt]);
           return(ret_value);
         }
       else if(ret_value < compare && sign == -1)
         {
           ret_value = LONG_MIN;
           errno = ERANGE;
           while(nptr[cnt] != '\0')
             {
	       cnt++;
             }
           *endptr = (char *)&(nptr[cnt]);
           return(ret_value); 
         }
       cnt++;
     }
    if(base == 16 && nptr[cnt] != '\0')
      {
	cnt-=1;
      }
    
   // clean up, set ret_value properly if the conversion went out of range
   // set errno if necessary
   // set *endptr properly if the endptr is not NULL
    if(endptr != NULL)
      {
        *endptr = (char *)&(nptr[cnt]);
      }
    else
      {
         *endptr = (char *)&(nptr[0]);
      }
    if(ret_value == 0)
      {
	*endptr = (char *)&(nptr[0]);
      }


   return ret_value*sign;
}
