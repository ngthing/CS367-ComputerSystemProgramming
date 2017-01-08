// Thi Nguyen Nov 25,2016
#include <stdlib.h>
#include "memory.h"

extern mem_ptr Heap;


void mm_free(mem_ptr m) {
  /* Input: pointer to a mem_rec 
     Output:  None
        You must coalesce this block with adjacent blocks if appropriate. 
        If the input pointer is null, call error_msg(2) and return 
  */
	if (m == NULL)
		{ error_msg(2); return;}
	if ((m->next == NULL && m->previous == NULL && m == Heap)
		|| m->next != NULL || m->previous != NULL)
	{ //m is a free node
		error_msg(3); return;}
	if (Heap == NULL)// There is no free block in the list
	{ Heap = m;return; }
	mem_ptr current = Heap;	
	while (current->next != NULL && current->address < m->address)
		// Traverse the linked list of free blocks to find a place to insert the newly freed block
		// such that the list are sorted in acending order of addresses
	{ current = current->next;}
	
	// Once found a place to insert the newly freed block, e.i. m->address < current->address
	// Assuming Case 1: Allocated -> m -> Allocated
	if (current->address > m->address) 
	{
		m->next = current;
		if (current->previous != NULL)
		{
			m->previous = current->previous;
			m->previous->next = m;

		}
		current->previous = m;
		if (current == Heap) //current is the first in heap
		{
			Heap = m; // assign the Heap to m 
		}
			
	}
	else if (current->address < m->address) // current is the end of the list
	{
		current->next = m;
		m->previous = current;
	}

	// Coalescing 
	// Case 4: Free -> m -> Free
	if ( (m->next != NULL) && (m->previous != NULL)
		&&((m->address + m->size) == m->next->address) 
		&& ((m->previous->address + m->previous->size) == m->address))
	{
		m->previous->size += m->size + m->next->size;
		m->previous->next = m->next->next;
		if ( m->next->next != NULL)
		{ m->next->next->previous = m->previous;}
		free(m->next);free(m);
	}
	//  Case 2: Allocated -> m -> Free
	else if ((m->next != NULL) && (m->address + m->size) == m->next->address)
	{
		mem_ptr mnext = m->next;		
		m->size += mnext->size;
		if ( mnext->next != NULL)
		{ 
		 mnext->next->previous = m;
		 m->next = mnext->next;
		}
		else if ( mnext->next == NULL)//m->next is the last block in heap
		{ m->next = NULL; } 
		free(mnext);
	}
	// Case 3: Free -> m -> Allocated
	else if ((m->previous != NULL) && (m->previous->address + m->previous->size) == m->address)
	{
		m->previous->size += m->size;
		m->previous->next = m->next;
		if ( m->next != NULL)
		{ m->next->previous = m->previous;} 
		free(m);
	}


}




