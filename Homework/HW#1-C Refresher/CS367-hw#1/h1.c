// Thi Nguyen 9/1/2016
// CS 367 Section 3 
// Homework1


#include <stdio.h>
#include <stdlib.h>

void moveUp(int toInsert, int lastIndex, int *temp)
{
	int tempIndex = lastIndex;
	while ((tempIndex > 0) && (toInsert > temp[(tempIndex-1)/2])) 
		//while tempIndex is not root and toInsert > the tempIndex's parent
	{
		temp[tempIndex] = temp[(tempIndex-1)/2]; 
		tempIndex = (tempIndex -1)/2;
	}
	temp[tempIndex] = toInsert;
	
}

int newTempIndex(int toMove, int tempIndex, int lastIndex, int *temp)
{
	int leftChildIndex = tempIndex*2 + 1;
	int rightChildIndex = tempIndex*2 +2;
	int result = tempIndex;
	if ((leftChildIndex <= lastIndex) && (rightChildIndex <= lastIndex))
	{
		if ((temp[leftChildIndex] > toMove) && (temp[rightChildIndex] > toMove))
		{
			if (temp[leftChildIndex] >= temp[rightChildIndex])
				{ result = leftChildIndex; }
			else if (temp[leftChildIndex] < temp[rightChildIndex])
				{ result = rightChildIndex;}
		}
	
		else if (temp[leftChildIndex] >= toMove)
			result = leftChildIndex;
		else if (temp[rightChildIndex] > toMove)
			result = rightChildIndex;
	}
	else if (leftChildIndex <= lastIndex)
	{
		if (temp[leftChildIndex] >= toMove)
			result = leftChildIndex;	
	}
	else 
		result = tempIndex;
	return result;
}

void moveDown(int toMove, int lastIndex, int *temp)
{
	int tempIndex = 0; // current index 
	int newtempIndex; // index where toMove should be moved to 
	newtempIndex = newTempIndex(toMove,tempIndex,lastIndex,temp);
	while (newtempIndex != tempIndex)
	{
		temp[tempIndex] = temp[newtempIndex];
		tempIndex = newtempIndex;
		newtempIndex = newTempIndex(toMove,tempIndex,lastIndex,temp);
	}

	temp[tempIndex] = toMove;
}

int main()
{	
	// Declare variable 
	int k,n,i, *originalArray, *temp;
	printf("Please enter k and n, follow by n integers:\n");
	scanf("%d %d", &k,&n);
	// if n is non-positive, print message "bad size"
	if (n < 0)
	{
		printf("bad size\n");
		return 0;

	}
	//if k is non-positive or greater than n, print message "bad index"
	if (k < 1 || k > n)
	{
		printf("bad index\n");
		return 0;

	}
	// Allocate memory for the array of n integers 
	originalArray = malloc(n*sizeof(int));
	if ( originalArray == NULL) // Check to see whether the memory is located 
	{	
		printf("Error! Insufficient memory allocating!\n");
		exit(1);
	}
	// Read n integers to originalArray
	for (i=0;i<n;i++)
	{
		scanf("%d", &originalArray[i]);
	}

	
	/*
	 Allocate memory for the temp array of k integers. This array is contructed as a 
	 max heap, and ultimately will hold the k smallest integers extracted from originalArray
	*/
	temp = malloc(k*sizeof(int));
	if ( temp == NULL) // Check to see whether the memory is located 
	{	
		printf("Error! Insufficient memory allocating!\n");
		exit(1);
	}

	int lastIndex = -1; // the last index was inserted to temp array
	int toInsert,toMove;
	/* this loop traverses the originalArray once.
	Then, it will check each integer from index k to n-1
	and  
	*/
	for ( i=0; i<n ; i++)
	{
		 toInsert = originalArray[i];
		 if (i<k) //read in the first k integers and put them into temp array (max heap).
		 {
		 	lastIndex++;
		 	temp[lastIndex] = toInsert;
		 	moveUp(toInsert,lastIndex,temp); // reorganize the heap after insert the new integer at the lastIndex
		 }
		// For the integers from k to n
		if (i >= k)
		 {
		 	if (toInsert <= temp[0]) // If there is an integer smaller than the maximum integer in temp array
		 	{
		 		if (lastIndex >= 0) // and If temp array it not empty
		 		{
		 			// remove the max integer in temp array and reorganize the heap
		 			toMove = temp[lastIndex];  
		 			lastIndex--;
		 			if (lastIndex != -1)
		 			{
		 				moveDown(toMove, lastIndex,temp); 
		 			}
		 		}
	 			// After the heap is reorganized, add the new integer to temp array
	 			lastIndex++;
	 			temp[lastIndex] = toInsert;
	 			moveUp(toInsert,lastIndex,temp); // reorganize the heap after insert the new integer at the lastIndex	
		 	}
		 		
		 }
	}
	printf("The %dth-lowest number: %d\n", k, temp[0]);
	free(originalArray);
	free(temp);
	return 0;
}

