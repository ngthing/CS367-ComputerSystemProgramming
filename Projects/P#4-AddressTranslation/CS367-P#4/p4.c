//Thi Nguyen, Dec 7, 2016
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "log.h"

int main ( int argc, char *argv[])
{
	start_logging();
	FILE *infile = NULL;
	int pageTable[128]; 
	// Packed bit in tlb as follow: 
	// signed bit  = valid bit/ flag
	// 4 least significant bits  = tag bits
	// next 15 least significant bits = ppn 
	int tlb[8]; 	
	// These varibles are for reading the PageTable file. 
	char fileName[50], extention[5], line[10];

	if ( argc < 2) 
	{ printf("Invalid command line. Please try again.\n");
	exit(1);
	}

	// Concate the extension to file name.
	strcpy(fileName,  argv[1]);
	strcpy(extention, ".pt");
	strcat(fileName, extention);
	// Open the page table file
	infile = fopen( fileName, "r");
	assert (infile != NULL);
	if (infile == NULL)
	{ printf("Error opening input file.\n");
	  exit(1);
	} 
	// Read the page table file and build an internal page table
	int i = 0; // Index for pageTable
	while(fgets(line, sizeof(line), infile) != NULL)
	{
        int validBit = atoi(&line[0]); // Get validBit
        char *ppnString = &line[2]; // Get pp
        if ( validBit == 1)//add the valid ppn to pageTable.
       	{	pageTable[i] = atoi(ppnString);	} 
       	else 
       		{ pageTable[i] = 40000; } // if the valid bit = 0, just add an invalid ppn

        i++;
	}
	int inputVA;
	char input[300];
	// After building the pageTable, start to read input from user
	do {
		printf("Enter a virtual address or -1 to exit: ");
		scanf("%s",input);
		inputVA = atoi(input);
		if (inputVA == -1)
			{ exit(0);}
		else if ( inputVA <= 131071) 
		{
			printf("Virtual Address: 0x%x\n", inputVA);
			int maskToGetVPN =  0x1fc00, maskToGetVPO = 0x3ff;
			int maskToGetTLBI = 0x7, maskToGetTLBT = 0x78;
			int vpn, vpo, tlbi, tlbt, outputPA, ppn; 
		    vpn = (inputVA & maskToGetVPN) >> 10; 
		    vpo = inputVA & maskToGetVPO; 
		    tlbi = vpn & maskToGetTLBI;
		    tlbt = (vpn & maskToGetTLBT) >> 3; 
		   //  printf("tlbi %d\n", tlbi);
		  	// printf("tlbt %d\n", tlbt);
			
			if ( (tlb[tlbi] < 0) && ((tlb[tlbi] & 0xF) == tlbt)) 
			// If tlb cached the data already
		  	{ 
		  		ppn = (tlb[tlbi] & 0x7FFF0) >> 4;
		  		outputPA = (ppn << 10) | vpo; 
		  		printf("Physical Address: 0x%x from the tlb\n", outputPA);
				log_it(FROM_TLB,inputVA, outputPA);
		  	}
		    // After get vpn, get pageTable[vpn]
		    else if ( pageTable[vpn] == 40000) // Page fault
		   	{
		    	printf("Page fault\n");
			log_it(PAGE_FAULT,inputVA, outputPA);
		    }
		    else 
		    {
		    	ppn = pageTable[vpn];
		    	outputPA = (ppn << 10) | vpo; 
		    	printf("Physical Address: 0x%x from the page table\n", outputPA);
			log_it(FROM_PT,inputVA, outputPA);
		    	// update TLB
		    	int temp = ppn<<4; 
			temp = temp | tlbt; 
			temp = temp |  0x80000000; 
			tlb[tlbi] = temp ; // update valid bit
		    }	    
		}
		else 
                    { printf("Illegal virtual address\n");log_it(ILLEGAL,inputVA,0);}
	}while(1);
    
	fclose(infile);
	stop_logging();
	return(0);
}
