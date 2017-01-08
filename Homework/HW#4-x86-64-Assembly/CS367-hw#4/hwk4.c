#include <stdio.h>   /* printf  */
#include <string.h>  /* strncmp */
#include <stdlib.h>  /* atoi, strtol    */

extern long mul_20 (long);
extern long longlog(long);
extern long collatz(long);
extern long prime  (long);
extern long caller (long,long);
extern long sum_primes(long,long[]);

/*
receives command line arguments for:
 #1 function to be tested
 #2 first argument
 (#3+: more arguments, or array values for the last argument)
*/
int main(int argc, char ** argv){
  /* check for minimum number of arguments */
  if (argc<3){
    printf("error - not enough arguments.\n\n\tusage: hwk4 funcname arg1 arg2 arg3 ...\n\n");
    return 1;
  }
  
  /* read in first function argument (always a long) */
  long n;
  sscanf(argv[2],"%ld",&n);
  
  /* dispatch to the correct function */
  if ( ! strncmp("mul_20",argv[1],10)){
    printf("%ld\n",mul_20(n));
  }
  else if ( ! strncmp("longlog",argv[1],10)){
    printf("%ld\n",longlog(n));
  }
  else if ( ! strncmp("collatz",argv[1],10)){
    printf("%ld\n",collatz(n));
  }
  else if ( ! strncmp("prime",argv[1],10)){
    printf("%ld\n",prime(n));
  }
  else if ( ! strncmp("caller",argv[1],10)){
    /* rename our first argument, and get the second argument */
    long x = n;
    long y;
    sscanf(argv[3],"%ld",&y);
    printf("%ld\n",caller(x,y));
  }
  else if ( ! strncmp("sum_primes",argv[1],10)){
    /* get the array items, build array. */
    long xs [n];
    for (int i=0; i<n; i++){
      sscanf(argv[i+3],"%ld",&xs[i]);
    }
    printf("%ld\n",sum_primes(n,xs));
  }
  /* give a helpful message when the function is misspelled. */
  else {
    printf("error - unrecognized command '%s'.\n",argv[1]);
    return 2;
  }
}
