#include <errno.h>
#include <ctype.h>
#include <limits.h>

#include "answer02.h"

// Given a char c, return a numeric value
// '0'..'9' --> 0..9
// 'a'..'z' --> 10..35
// 'A'..'Z' --> 10..35
// for other characters, return INV_SYMBOL (see answer02.h);
//
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
     n = INV_SYMBOL;
   }

   return n;
}

// you are not allowed to change the contents at the location whose address in 
// stored in nptr (the way to interpret the type of nptr is that it is an address
// pointing to a constant char.)
//
// you have to check for whether the base in the valid range 2 through 36
// if not, set errno to EINVAL
// 
// This is a suggestion on how you should process the string
// (1)  skip over all white space
// (2)  if a +/- sign is encountered, set the polarity of the number accordingly
//      By default, the number is assumed to be positive if no sign is given.
// (3)  Convert the string until you encounter an invalid symbol for that 
//      base or when you reach the end of the string.
//
// examples (not exhaustive, of course):
//    "10a:" in base 10 is 10, in base 16 is 266, in base 36 is 1306
//    "   -10a:" in base 10 is -10, in base 16 is -266, and in base 36 is -1306 
//    " +10a:" in base 10 is 10, in base 16 is 266, in base 36 is 1306
//    "922337203685477580710304" in base 10 should return LONG_MAX, and errno 
//    should be set to ERANGE.
//    "-922337203685477580710304" in base 10 should return LONG_MIN, and errno 
//    should be set to ERANGE.
//    "garbage" should be 0 in base 10, 0 in base 16, and 35479055534 in base 36
//
long int str_to_long_int(const char *nptr, int base)
{
   long int ret_value = 0;  // return value
                            // if no conversion happens, return 0
   int cnt = 0;
   int sign = 1;
   long int compare;
   //long int tmp;
   // if invalid base, set errno and return immediately
   if(base < 2 || base > 36)
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
   // if a negative sign is encountered, the conversion must
   // produce a negative number
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

	
   // now, convert the string to number
   // the conversion has to account for the +/- sign
   // need to check whether you have out-of-range ret_value
 

   /*if(nptr[cnt] != '\0' && char_to_int(nptr[cnt]) < base)
     {
       ret_value = char_to_int(nptr[cnt]);
       cnt++;
     }
   */
   while(nptr[cnt] != '\0' && char_to_int(nptr[cnt]) < base)
     {
       compare = ret_value;
       ret_value = ret_value * base + char_to_int(nptr[cnt]);
        
          if(ret_value < compare && sign == 1)
	    {
	      ret_value = LONG_MAX;
	      errno = ERANGE;
              return(ret_value);
	    }
          else if(ret_value < compare && sign == -1)
	    {
	      ret_value = LONG_MIN;
	      errno = ERANGE;
	      return(ret_value);
	    }
       cnt++;
     }
          
     
  


   // clean up before returning
   // need to set errno and ret_value correctly if the converted number 
   // is out of range
  
   return ret_value * sign;
}
