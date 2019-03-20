 #include <stdio.h>
#include <stdlib.h>

int start = 2048;
int end = 20480;
int arraySize = 65536;

int generateRandomNumber(int start, int end);

int main(){

	int r = generateRandomNumber(start, end);
	printf("Random number generated is : %d\n", r);
	
	char n[arraySize];
	int i;
	int r2;
	
		//write file
		FILE *physical_memory = fopen("data/physical_memory.txt","w");
	  FILE * fPointer;
	  //read from file
	  fPointer = fopen("data/physical_memory.txt","r");  

	//generate random characters
	for(i=0;i<=r;i++)
	{
		int rand = 	generateRandomNumber(32,126);
		char n = rand;

	//print to the file
		fprintf(physical_memory, "%d random char: %c\n",i,n);
	}

	//read from file	
	char singleLine[100];
	fPointer = fopen("data/physical_memory.txt","r");  
	while(!feof(fPointer)){
	fgets(singleLine, 100, fPointer);
	puts(singleLine);
	}  

	fclose(fPointer);

	return 0;
}

	//generate random numbers
	int generateRandomNumber(int start, int end){
	int mid = end- start;
	int	randomNumber;

	randomNumber = rand() % (mid+1) + start;

	return randomNumber;	
}

