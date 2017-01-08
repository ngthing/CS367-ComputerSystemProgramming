/**
 Thi Nguyen - CS367 - Project1 
 09/23/2016
 **/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fp.h"


int computeFP(float val) {
// input: float value to be represented
// output: integer version in our representation
//
// Perform this the same way we did in class -
//    either dividing or multiplying the value by 2
//    until it is in the correct range (between 1 and 2).
//    Your exponent is the number of times this operation
//    was performed.   
// Deal with rounding by simply truncating the number.
// Check for overflow and underflow - 
//    with 4 exponent bits, we have overflow if the number to be 
//       stored is > 14
//    for overflow (E > 14), return -1
//    For underflow (E < 1), return 0 
  float temp_val = val, frac =0; 
  int result = 0, exp = 0, E = 0, i=0;
  int bias = 15; // our bias = 2^(5-1) -1 = 15
// If val < 1, multiply val by 2 and decrement E by 1 repeatedly until val is >= 1 
  if (val < 1)
  {
  	while ( temp_val < 1)
	{ 
		temp_val = temp_val * 2; 
		E = E - 1; 
	}
  }
  // Else if val >= 2, divide val by 2 and increment E by 1  until val is < 2
  else if (val >= 2)
  {
  	while (temp_val >=2)
  	{
  		temp_val = temp_val / 2;
  		E = E + 1;
  	}
  }
	
   exp = E + bias;
   // If the number is overflow 
   if (exp > 30)
   	result = -1;
// If the number is underflow
   else if (exp < 1)
   	result = 0; 
   else
   	/** 
   	 The step below will get 7bits frac
	**/
	frac = temp_val -1;
	for (i =0; i <7; i++){
	frac = frac * 2;
	}
   	result = result | (int)frac; 
   	/** 
   	The exp value will be shift left 7 bits and | with the current result 
   	to give the integer version in our representation 
   	**/
   	result = result | (exp << 7);

  return result;
}

float getFP(int val) {
// Using the defined representation, compute the floating point
//    value
// For denormalized values (including 0), simply return 0.
// For special values, return -1;
	int exp = 0, frac = 0, bias = 15, i=0, E=0;
	float M, frac_temp ;
	// extract the exp bits from val
	exp = (val & 0xF80)>> 7;
	// extract the frac bits from val
	frac = val & 0x7F; 
 	frac_temp = (float) frac;
	// convert the frac bits to frac_temp
	for (i =0; i <7; i++){
        frac_temp = frac_temp / 2;
        }
	// if the number is a special number 
	if ( exp > 30)
		return  -1;
	// if the number is a denormalized number
	else if (exp < 1)
		return 0;
	else{
	// find E = exp - bias
	E = exp - bias;
	// Find M
	M= frac_temp +1;
	// value = M*2^(E) 
	if ( E < 0)
                { while(E <0) { M = M/2; E++;}}
                else if (E>0)
                { while(E>0) { M=M*2; E--;}}
	}
	return M;
}
int
multVals(int source1, int source2) {
// You must implement this by using the algorithm
//    described in class:
//    Add the exponents:  E = E1+E2 
//    multiply the fractional values: M = M1*M2
//    if M too large, divide it by 2 and increment E
//    save the result
// Be sure to check for overflow - return -1 in this case
// Be sure to check for underflow - return 0 in this case
	int exp1 = 0,exp2=0,exp =0,frac=0, frac1 = 0,frac2=0, bias = 15, i=0, E1=0, E2=0,E=0, result =0;
        float M1,M2,M,frac_float, frac_float1, frac_float2 ;
	// extract exp1 bits from source1
	exp1 = (source1 & 0xF80) >> 7;
	// extract exp2 bits from source2
	exp2 = (source2 & 0xF80) >> 7;
	// chech if source1 or source 2 are overflow
	if ( exp1 > 30 || exp2 > 30)
		return -1;
	else if ( exp1 < 1 || exp2 < 1)
		return 0;
	// find E = E1 + E2
	E = (exp1 - bias) + ( exp2 - bias); 	
	//find frac1 and frac2 
	frac1 = source1 & 0x7F;
        frac_float1 = (float) frac1;
	frac2 = source2 & 0x7F;
        frac_float2 = (float) frac2;
	// convert the frac bits to frac_float
	for (i =0; i <7; i++)
	{frac_float1 = frac_float1 / 2;
	 frac_float2 = frac_float2 / 2; }
	//find M1, M2, and M= M1*M2
	M1 = frac_float1 +1;
	M2 = frac_float2 +1;
	M = M1*M2; 
	while (M >=2) 
	{ M = M/2; E++; }
	exp = E + bias;
	if (exp > 30) return -1;
	else if (exp < 1) return 0; 
	// Convert the result to our int representation
	frac_float = M -1;
	for (i = 0; i < 7; i++) {frac_float = frac_float *2; } 
        
	result = result | (int)frac_float;
        result = result | (exp << 7);

  return result;
}

int
addVals(int source1, int source2) {
// Do this function last - it is the most difficult!
// You must implement this as described in class
//
//     If needed, adjust one of the two number so that 
//        they have the same exponent E
//     Add the two fractional parts:  F1' + F2 = F
//              (assumes F1' is the adjusted F1)
//     Adjust the sum F and E so that F is in the correct range
//     
// As described in the handout, you only need to implement this for
//    positive, normalized numbers
// Also, return -1 if the sum overflows
	int exp1 = 0,exp2=0,exp =0,frac=0, frac1 = 0,frac2=0, bias = 15, i=0, E1=0, E2=0,E=0, result =0;
        float M1,M2,M,frac_float, frac_float1, frac_float2 ;
	// extract exp1 bits from source1, exp2 from source2
	exp1 = (source1 & 0xF80) >> 7;
	exp2 = (source2 & 0xF80) >> 7;
	E1 = exp1 - bias;
	E2 = exp2 - bias; 
	// find frac1 and frac2
	frac1 = source1 & 0x7F;
        frac_float1 = (float) frac1;
        frac2 = source2 & 0x7F;
        frac_float2 = (float) frac2;
	// convert the frac bits to frac_float
 	for (i =0; i <7; i++)
        {frac_float1 = frac_float1 / 2; 
         frac_float2 = frac_float2 / 2; }
	// Get M1, M2
	M1 = frac_float1 +1;
        M2 = frac_float2 +1;
	// align E1 and E2 and adjust M1 accordingly
	if (E1 > E2) { while(E1 > E2) {M1 = M1*2; E1--;}}
	else if (E1< E2) { while(E1<E2) {M1 = M1/2; E1++;}}
	// Compute M = M1+M2	        
	M = M1+M2;
	E = E2;	
	// If M is not in range [1,2), increment E and fix M	
	while (M >=2)
        { M = M/2; E++; }
        exp = E + bias;
        if (exp > 30) return -1;
        else if (exp < 1) return 0;
        // Convert the result to our int representation
	frac_float = M -1;
        for (i = 0; i < 7; i++) {frac_float = frac_float *2; }
	
        result = result | (int)frac_float;
        result = result | (exp << 7);

	return result;
	
}
