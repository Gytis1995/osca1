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

  	int r = generateRandomNumber(start, end);
	
	
	char *n = malloc(arraySize);
	

	//indicate empty space in array
	for (int i = 0; i < arraySize; i++)
		{
			n[i] = '0';
		}

	//generate random location to start populating array
	int randomLocation = generateRandomNumber(512,((arraySize - 1)-r));
 
	//generate random characters
	for(int i=randomLocation; i < (randomLocation+r); ++i)
	{
	 n[i]  =  generateRandomNumber(32,126);
	}

	
	//printf("%s\n", n);


	//write to file
	FILE *physical_memory = fopen("data/physical_memory.txt","w");
	for(int i = 512; i < arraySize; i++)
	{
		fprintf(physical_memory, "| 0x%x | %d | %c |\n",i,i/256,n[i]);
	}
	fclose(physical_memory);
	
	
	//read from file
	FILE * fPointer;   
	fPointer = fopen("data/physical_memory.txt","r");  
	char singleLine[100];
	while(!feof(fPointer)){
	fgets(singleLine, 100, fPointer);
	puts(singleLine);
	}
	fclose(fPointer);
	
	printf("Random number generated is : %d\n", r);


	//fill in page table data
	int frames = ((r+(randomLocation-1))/256) - (randomLocation/256);

	for(int i = 0; i <= frames; ++i){
		n[i] = i + (randomLocation/256);
	}

	
	//write to page table
	FILE *page_table = fopen("data/page_table.txt","w");
	for(int i = 0; i <= frames; i++)
	{
		if(n[i]<0)
		{
			fprintf(page_table, "| 0x%x | %d |\n",i,256 + n[i]);
		}
		else{
		fprintf(page_table, "| 0x%x | %d |\n",i,n[i]);
		}
	}
	fclose(page_table);

	
		 
	//address translation
		 int virtualAddress=0;
	do
	{
	
  	 printf("\nEnter virtual address : ");
		 scanf("%x", &virtualAddress);

	int pageNumber = virtualAddress/256;
	int frameNumber = n[pageNumber];
	if (frameNumber<0)
 	{
		frameNumber = 256 + frameNumber;
	}
	int offset = virtualAddress - ((pageNumber*256)-1);
	int physicalAddress = (frameNumber * 256) + offset;

	printf("\nAddress : 0x%x",virtualAddress);
	printf("\nPage no : %d",pageNumber);
	printf("\nPage %d : frame %d", pageNumber, frameNumber);
	printf("\nOffset : %d", offset);
	printf("\nValue : %c",n[physicalAddress]);
		
	}
	while(virtualAddress > 0);
	
	return 0;
}

	//generate random numbers
	int generateRandomNumber(int start, int end){
	int mid = end- start;
	int	randomNumber;

	randomNumber = rand() % (mid+1) + start;

	return randomNumber;	
}

