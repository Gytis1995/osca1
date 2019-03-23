#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int start = 2048;
int end = 20480;
int arraySize = 65536;
int generateRandomNumber(int start, int end);


int main(){

	//restart the random numbers
	srand (time(NULL));

 	int bytes = generateRandomNumber(start, end);
	
	//ref: introduction to c malloc example moodle
	char *physicalMemory = malloc(arraySize);

	//indicating the empty spaces in the array
	for (int i = 0; i < arraySize; i++)
		{
			physicalMemory[i] = '~';
		}

	//generate random location to start populating the physical memory array
	int randomLocation = generateRandomNumber(512,((arraySize - 1)-bytes));
 
	//generate random values/characters that are going to be stored in the physical memory
	for(int i=randomLocation; i < (randomLocation+bytes); ++i)
	{
	 physicalMemory[i]  =  generateRandomNumber(32,126);
	}

	//write the physical memory to a file
	//ref: https://www.cs.utah.edu/~germain/PPS/Topics/C_Language/file_IO.html
	FILE *physical_memory = fopen("data/physical_memory.txt","w");
	if (physical_memory == NULL) 
            {   
              printf("Error! Could not open file\n"); 
              exit(-1); 
            } 
	fprintf(physical_memory, "       Address\t|     Frame\t|     Values\n");
	for(int i = 512; i < arraySize; i++)
	{
		fprintf(physical_memory, "\t0x%x\t|\t%d\t|\t%c\n",i,i/256,physicalMemory[i]);
	}
	fclose(physical_memory);
	
	
	//read from file 
	//ref: C programming tutorial 51 | how to read files (youtube)
	FILE * fPointer;   
	fPointer = fopen("data/physical_memory.txt","r");  
	char singleLine[100];
	while(!feof(fPointer)){
	fgets(singleLine, 100, fPointer);
	puts(singleLine);
	}
	fclose(fPointer);
	
	printf("Random number of bytes generated is : %d\n", bytes);


	//fill in page table data
	int frames = ((bytes+(randomLocation-1))/256) - (randomLocation/256);

	for(int i = 0; i <= frames; ++i){
		physicalMemory[i] = i + (randomLocation/256);
	}

	
	//write to page table
	//ref: https://www.cs.utah.edu/~germain/PPS/Topics/C_Language/file_IO.html
	FILE *page_table = fopen("data/page_table.txt","w");
	if (page_table == NULL) 
            {   
              printf("Error! Could not open file\n"); 
              exit(-1); 
            } 
	
	fprintf(page_table, "\tpage\t| page table entry\n");
	for(int i = 0; i <= frames; i++)
	{
		//this solves the problem of printing the minus values to the file
		if(physicalMemory[i]<0)
		{
			fprintf(page_table, "\t0x%x\t|\t%d\n",i,256 + physicalMemory[i]);
		}
		else{
		fprintf(page_table, "\t0x%x\t|\t%d\n",i,physicalMemory[i]);
		}
	}
	fclose(page_table);

	
		 
	//address translation
	//ref: white board tutorials
		 int virtualAddress=0;
	do
	{
	
  	 printf("\nEnter virtual address : ");
		 scanf("%x", &virtualAddress);
	
	
	int pageNumber = virtualAddress/256;	
	int frameNumber = physicalMemory[pageNumber];
	if (frameNumber<0)
 	{
		frameNumber = 256 + frameNumber;
	}
	int offset = virtualAddress - ((pageNumber*256)-1);
	int physicalAddress = (frameNumber * 256) + offset;

	printf("\nAddress: 0x%x",virtualAddress);
	printf("\nPage no: %d",pageNumber);
	printf("\nPage %d = frame %d", pageNumber, frameNumber);
	printf("\nOffset: %d", offset);
	printf("\nValue: %c",physicalMemory[physicalAddress]);
		
	}
	while(virtualAddress > 0);
	
	return 0;
}

	//generate random numbers
	// ref: https://www.youtube.com/watch?v=q1B27ivhON8
	int generateRandomNumber(int start, int end){
	int mid = end- start;
	int	randomNumber;

	randomNumber = rand() % (mid+1) + start;

	return randomNumber;	
}

