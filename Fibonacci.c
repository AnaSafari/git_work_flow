/// A code to find the fibonacci of any integer n.
/// n cat get negative or positive values and the output of 
/// Fibonnacci can also be negative or positive integers.
/// : Anahita Safarishahrbijari

#include <stdio.h>
#include <stdlib.h>

//Prototyping
int Fibonacci(int n);

#define MAX_OVERFLOW 46 
#define MIN_OVERFLOW -46

int main(void){
	int n;
	printf("Enter an Integer Number: \n");
	scanf("%d", &n);
	// if (n % 1 != 0){
	// 	printf("Not a Valid Number! Please enter an integer \n");
	// 	exit(0);
	// }
	

	if (n > MAX_OVERFLOW || n < MIN_OVERFLOW){
		printf("Integer Over Flow, please enter an enteger lower than 47 and greater than -47");
		exit(0);
	}

	printf("Fibonacci is: %d \n", Fibonacci(n));

	return 0;
	
}


int Fibonacci(int n) {
	int fib;
	if (n==0){
		fib=0;
		
	} else if (n==1){
		fib=1;

	} else if (n<0){
		fib = Fibonacci(n+2) - Fibonacci(n+1);
		printf("test4\n");
	} else {
		fib = Fibonacci(n-1) + Fibonacci(n-2);
	}
	
	return fib;	
}


