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

  //int r = generateRandomNumber(start, end);
  int r = generateRandomNumber(start, end);
	
	
	char *n = malloc(arraySize);
	int i;

	//indicate empty space in array
	for (int i = 0; i < arraySize; i++)
		{
			n[i] = '0';
		}

	//generate random location to start populating array
  int randomLocation = generateRandomNumber(512,((arraySize - 1)-r));
  //int count = 0;

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
		fprintf(physical_memory, "| 0x%d | %d | %c |\n",i,i/256,n[i]);
	}

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
	
		 
	//get the element from the array by position
	//	 int arrayPosition;  
  //	 printf("\n enter the position of the number in the array you want : ");
  //   scanf("%d", &arrayPosition);
  //   printf("\n the character at position %d is : %c\n", arrayPosition, n[arrayPosition]);	 
	
	return 0;
}

	//generate random numbers
	int generateRandomNumber(int start, int end){
	int mid = end- start;
	int	randomNumber;

	randomNumber = rand() % (mid+1) + start;

	return randomNumber;	
}

