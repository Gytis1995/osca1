#include <stdio.h>
#include <stdlib.h>

int main(){

int i;
int start = 2048;
int end = 20480;
int middle = end - start;
int randomNumber;
start = 2048;
end = 20480;
for(i=0;i<=20;i++){
//int generatorRandomNumber(int start, int end){
randomNumber = rand() % (middle+1) + start ;
printf("random number between 2048 and 20480 %d\n",randomNumber);
}
return 0;
}

