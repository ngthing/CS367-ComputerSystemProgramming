// Thi Nguyen Nov 25,2016
#include <stdio.h>
#include <stdlib.h>

#include "memory.h"

extern mem_ptr Heap;


mem_ptr
mm_malloc(int size) {
  /* Input: size of the block needed
     Output: 
       Return a pointer to a mem_rec of the appropriate size (new_size).
       This block should be found using first-fit.     
       If there is nowhere to place a block of the given size, call error_msg(1) 
          and return a NULL pointer
  */
  int new_size = ALIGN(size);
  mem_ptr current = Heap;
  // look for the first fit by traversing the linked list
  while ( current != NULL && current->size < new_size) 
  	{ current = current->next; }

  // There is nowhere to place a block of the given size, call error_msg(1) 
  // and return a NULL pointer
  if (current == NULL)
  {	
  	error_msg(1);
  	return NULL;
  }  
  // Found a mem_rec of the appropriate size (new_size).
  else if (current != NULL) 
  {
  	// Create allocated_mem of new_size
  	mem_ptr allocated_mem = NULL;
	allocated_mem = (mem_ptr)malloc(sizeof(mem_rec));
	if (allocated_mem == NULL)
	{ printf("Error allocating memory in the heap.\n"); exit(1); }
   	allocated_mem->size = new_size;  
   	allocated_mem->address = current->address;
   	allocated_mem->previous = allocated_mem->next = NULL; 
   	
   	if ((current->size == new_size) && (current->next != NULL || current->previous != NULL ))
   	// If current->size == new_size, and current is not the only block in heap
   	// the current block will be removed from the linked list of free blocks
   	{
	if (current->next != NULL && current->previous != NULL) // current is a middle block
   	{
       		current->next->previous = current->previous;
        	current->previous->next = current->next;
        	free(current);
      	}
      	else if (current->next == NULL && current->previous != NULL) // current is the last block
      	{
        	current->previous->next = NULL;
        	free(current);
      	}
      	else if (current->previous == NULL && current->next != NULL) // current is the first block
      	{
        	current->next->previous = NULL;
		Heap = current->next;
        	free(current);
		if (Heap->address == HEAPSIZE && Heap->size == 0){Heap = NULL; free(Heap);}
      	}		
   	}
	else if  ((current->size == new_size) && (current->next == NULL && current->previous == NULL ))
	// If current is the only block in the heap.
	{
		if (Heap == current) { Heap = NULL;}
		free(current);	
	}	 
   	else  
   	{
   		current->size=current->size - new_size;
   		current->address = current->address + new_size;
   	}
  	return allocated_mem;
  }

  return NULL;
}



