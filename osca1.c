#include <stdio.h>
#include <stdlib.h>

int start = 2048;
int end = 20480;

int generateRandomNumber(int start, int end);

int main(){

	int r = generateRandomNumber(start, end);
	printf("Random number generated is : %d\n", r); 

	return 0;

}

int generateRandomNumber(int start, int end){
	int mid = end- start;
	int	randomNumber;

	randomNumber = rand() % (mid+1) + start;

	return randomNumber;	
}
