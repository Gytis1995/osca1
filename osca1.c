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
	 FILE *physical_memory = fopen("data/physical_memory.txt","w");
	 
	for(i=0;i<=r;i++)
	{
int rand = 	generateRandomNumber(32,126);
 char n = rand;
		fprintf(physical_memory, "%d random char: %c\n",i,n);
	}  

//int loop;
//for(loop = 0; loop<r; loop++){
	//printf("%d, ", n[loop]);
//}


	return 0;

}

int generateRandomNumber(int start, int end){
	int mid = end- start;
	int	randomNumber;

	randomNumber = rand() % (mid+1) + start;

	return randomNumber;	
}

