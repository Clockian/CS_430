#include <stdlib.h>
#include <stdio.h>

// The main function provides the adder which adds one argument to another
int main(int argc, char *argv[]){
	if(argc != 3){  // 3 arguments as the name of the program is the first argument
		printf("This program requires two args");
		return 1;  // Return 1 indicates error, return 0 indicates success
	}
	int a = atoi(argv[1]);  // atoi is ascii to int, argc[1] pulls the second argument to be used
	int b = atoi(argv[2]);

	printf("%d + %d = %d\n", a, b, a+b);
	return 0;
}
