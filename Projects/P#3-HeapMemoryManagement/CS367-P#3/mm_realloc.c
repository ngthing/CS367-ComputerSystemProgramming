// Thi Nguyen Nov 25, 2016
#include <stdio.h>
#include <stdlib.h>

#include "memory.h"

extern mem_ptr Heap;


mem_ptr mm_realloc(mem_ptr m, int size) {
  /* Input: pointer to a mem_rec, new size of the block needed
     Output: 
       If the input pointer is null, call error_msg(2) and return

       Return a pointer to a mem_rec of the appropriate size (new_size).
       This block should be chosen as follows:
          if the new size is less than the current size of the block, 
            use the current block after moving the excess back to the free
            list
          if the new block size is larger than the current size, 
            first see if there is enough space after the current block
              to expand.  
            If this will not work, you will need to free the current block
              and find a location for this larger block using first-fit.
       If there is nowhere to place a block of the given size, print
          call error_msg(1) and return a NULL pointer
  */
  int new_size = ALIGN(size);
  if ( m == NULL)
   { error_msg(2); return NULL;}
  if ((m->next == NULL && m->previous == NULL && m == Heap)
                || m->next != NULL || m->previous != NULL)
        { //m is a free node
                error_msg(3); return;}
  if ( new_size < m->size )
  /*  if the new size is less than the current size of the block, 
          use the current block after moving the excess back to the free
          list
  */
  {
    // Create toFree of m->size - new_size
      mem_ptr toFree = NULL;
      toFree = (mem_ptr)malloc(sizeof(mem_rec));
      if (toFree == NULL) 
      { printf("Error allocating memory in the heap.\n"); exit(1); }
      toFree->size = m->size - new_size;  
      toFree->address = m->address + new_size;
      toFree->previous = toFree->next = NULL;
      m->size = new_size;
      mm_free(toFree); 
      return m;
  }
  else if (new_size > m->size)
  {
    int extraSpace = new_size - m->size;
    int nextAddress = m->address + m->size;
    if (Heap == NULL) // No more space
    { 
      mm_free(m);
      error_msg(1);
      return NULL;
    }
    mem_ptr current = Heap;
    while(current->address != nextAddress && current->next != NULL)
      { current = current->next;}

    if (current != NULL && current->address == nextAddress) 
    // found the free block next to m
    {
      if (current->size > extraSpace) 
      // after m expanding to this block, it still has more free space
      // Only need to shrinkn this free block.
        { 
          current->address += extraSpace;
          current->size -= extraSpace;
	  m->size += extraSpace;
        }
      else if (current->size == extraSpace && (current->next != NULL || current->previous != NULL )) 
      // after m explanding to this block, no more free space in current 
      // and current is not the only block in heap
      // then current block will be removed from the linked list of free blocks
        { 
          if (current->next != NULL && current->previous != NULL) // current is a middle block
          {
              m->size += extraSpace;
	      current->next->previous = current->previous;
              current->previous->next = current->next;
              free(current);
          }
           else if (current->next == NULL && current->previous != NULL) // current is the last block
          {
	      m->size += extraSpace;
              current->previous->next = NULL;
              free(current);
          }
          else if (current->previous == NULL && current->next != NULL) // current is the first block
          {
	      m->size += extraSpace;
              current->next->previous = NULL;
              Heap = current->next;
              free(current);
              if (Heap->address == HEAPSIZE && Heap->size == 0){Heap = NULL; free(Heap);}
          }

        }
      else if  ((current->size == extraSpace) && (current->next == NULL && current->previous == NULL ))
      // If current is the only block in the heap.
      {
	m->size += extraSpace;
        if (Heap == current) { Heap = NULL;}
        free(current);
      }

      else // not enough space in this block
        { mm_free(m); return mm_malloc(new_size);}
    }
    else // cannot find a free block next to m
      { mm_free(m); return mm_malloc(new_size);}

  }
   return m;
}



