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
	int conversion_num;

	conversion_num = atoi(argv[1]);

	if (conversion_num != 3 && conversion_num != 6) {
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
	if (fr == NULL) {
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
	
	if (magicnum1 == 'P' && magicnum2 == '3' && conversion_num == 3) {
		printf("Error: Cannot convert file to P3 as file is already P3\n");
	} else if (magicnum1 == 'P' && magicnum2 == '3' && conversion_num == 6) {
		printf("Run P3 to P6 conversion function\n");
	} else if (magicnum1 == 'P' && magicnum2 == '6' && conversion_num == 3) {
		printf("Run P6 to P3 conversion function\n");
	} else if (magicnum1 == 'P' && magicnum2 == '6' && conversion_num == 6) {
		printf("Error: Cannot convert file from P6 to P6\n");
	} else {
		printf("Error: invalid file header\n");
	}
	
	// Read input file into memory, else it can't be read from
	

	// Skip any comments "#" to get the "HEIGHT WIDTH"
	

	// Skip any comment "#" to get the RGB max color value
	

	// If converting from P3 to P6, change the ASCII decimal to binary
	

	// If converting from P6 to P3, convert the binary to ASCII decimal
	

}
