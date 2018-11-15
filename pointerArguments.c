
////Anahita Safari
#include<stdio.h>

// this function has two return values and uses pointer arguments two return two different values.
// This function gets an argent arg and returns multiplication by 2 and 3 of that argument.


int func1(int arg, int *ret1, int *ret2){
	* ret1= 2 * arg;
	* ret2= 3 * arg;

	return 0;
}

int main(){
	int arg = 5;
	int multi2; 
	int multi3;

	func1(arg, &multi2, &multi3);

	printf("multi2= %d, multi3= %d \n", multi2, multi3);


}