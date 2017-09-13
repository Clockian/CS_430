#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

	// Checks if the # of arguements is correct
	if (argc != 4) {
		printf("Usage: ppmrw CONVERT-TO-# INPUT-FILE OUTPUT-FILE\n");
		return 1;
	} else {
		printf("Section 1: Success\n");
	}

	// Check if arg 1 is a 3 or 6
	int magic_num;

	magic_num = atoi(argv[1]);

	if(magic_num != 3 && magic_num != 6) {
		printf("Usage: Choose between '3' for P3 or '6' for P6\n");
		return 1;
	} else {
		printf("Section 2: Success\n");
	}
	

	// Check file names to see if they
	// 	-Check if files exists
	// 	-End in .ppm ### Scratch, not possible, magic number replicates this
	// 	-input and output filename are different ### unable to do 
	// 	without comparing everything in each other
	// 	-No negative "-" at the beginning  ### Scratch, if it works, who cares
	FILE *fr = fopen(argv[2], "r");
	if(fr == NULL) {
		printf("Input file does not exist\n");
		return 1;
	} else {
		printf("Section 3.1: Success\n");
	}


	// Read "magic number" in the file for P3 or P6
	char magicnum1 = fgetc(fr);
	char magicnum2 = fgetc(fr);
	char newline = fgetc(fr);
	printf("%c%c%c", magicnum1, magicnum2, newline);

	
	// Read input file into memory, else it can't be read from
	

	// Skip any comments "#" to get the "HEIGHT WIDTH"
	

	// Skip any comment "#" to get the RGB max color value
	

	// If converting from P3 to P6, change the ASCII decimal to binary
	

	// If converting from P6 to P3, convert the binary to ASCII decimal
	

}
