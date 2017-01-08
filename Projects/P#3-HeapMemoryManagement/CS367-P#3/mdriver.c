#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

// ***********************************************************
// DO NOT MODIFY THIS FILE
// This file hold the main driver program responsible for opening and
//   reading the trace files.  It will call the appropriate function and
//   store the returned value in the allocs[] array.
// 
// It contains the mm_dump() routine that prints out the contents of
//    memory when needed.
//
// It contains an error function to output the associated messages.  
// ***********************************************************

#define MAX_INDEX 10000
#define DEBUG 0

mem_ptr Heap = NULL;


static mem_ptr allocs[MAX_INDEX];
// The allocs array is what ties a numbered allocation to an area of memory.
// For example, mm_malloc(5,20) should point at the most recent allocation
//    designated as 5


extern mem_ptr mm_malloc(int),mm_realloc(mem_ptr,int);
extern void mm_free(mem_ptr),mm_dump(); 

main(int argc, char**argv) {
// The program expects that name of the trace file on the command line
    FILE *f;
    int num,i;
    if (argc != 2) {
      printf("Usage: %s trace_file\n",argv[0]);
      exit(2);
    }
    if (f = fopen(argv[1],"r"))  {   
      int op; int index, size;
      init_driver();
      mm_init();
      //
      // process the trace file one line at a time
      while (fscanf(f,"%d %d %d",&op,&index,&size)) {
         if (op == 1) { if (index >= MAX_INDEX) printf("Illegal index in input file\n"); else
                     allocs[index] = mm_malloc(size);}
         else if (op == 2) {if (index >= MAX_INDEX) printf("Illegal index in input file\n"); else
                     mm_free(allocs[index]);allocs[index]=NULL;}
	 else if (op == 3) {if (index >= MAX_INDEX) printf("Illegal index in input file\n"); else
                     allocs[index] = mm_realloc(allocs[index],size); }
         else if (op == 4)  {mm_dump();}
         else if (op == 5)  {mm_dump(); alloc_dump();}
         else if (op == 0) { fclose(f); if (Heap) free(Heap);exit(1);}
	// NOTE:  any nodes that have not been deallocated are still present
	//
      }
    } else {printf("Unknown trace file\n");
           printf("Usage: %s trace_file\n",argv[0]);
           exit(2);
		}

}




/* init function for the implicit impl */
mm_init() {
   Heap = (mem_ptr)malloc(sizeof(mem_rec));
   Heap->size = HEAPSIZE;  Heap->address = 0;
   Heap->previous = Heap->next = NULL;
}

// output the contents of memory.  This function simply walks through
//    memory via the 'next' pointer and prints out the information associated
//    with that node
void mm_dump() {
   mem_ptr t = Heap;
   printf("Free blocks in Memory: \n");
   while(t) {
     printf("%5d: size = %-5d \n",t->address,t->size);
     t = t->next;
   }
   printf("\n");
}

// output what is in the allocation array

alloc_dump() {
   int i;
   printf("Allocated Blocks: \n");
   for (i=0;i<MAX_INDEX;i++) 
        if (allocs[i]) 
	  printf("\tBlock %d: Address: %d  Size: %d\n",i,allocs[i]->address, allocs[i]->size); 
printf("\n");
    
}



error_msg(int which) {
   switch (which) {
        case 1:
        printf("ERROR: Insufficient heap space for desired allocation\n");
        break;
        case 2:
        printf("ERROR: Cannot free NULL pointer\n");
        break;
        case 3:
        printf("ERROR: cannot free() or realloc() a free node.\n");
        break;
   }
}

init_driver() {
   int i;
   for (i=0;i<MAX_INDEX;i++) 
        allocs[i] = NULL;
}
