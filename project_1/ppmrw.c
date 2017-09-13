#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

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
		return 1;
	} else if (magicnum1 == 'P' && magicnum2 == '3' && conversion_num == 6) {
		printf("Run P3 to P6 conversion function\n");
	} else if (magicnum1 == 'P' && magicnum2 == '6' && conversion_num == 3) {
		printf("Run P6 to P3 conversion function\n");
	} else if (magicnum1 == 'P' && magicnum2 == '6' && conversion_num == 6) {
		printf("Error: Cannot convert file from P6 to P6\n");
		return 1;
	} else {
		printf("Error: invalid file header\n");
		return 1;
	}
	
	// Skip any comments "#" to get the "HEIGHT WIDTH"
	char next_char = fgetc(fr);
	while (1) {
		if (next_char == '#') {
			while (next_char != '\n') {
				next_char = fgetc(fr);
				//printf("in innner while loop\n");
			}
			//printf("skipping commented line\n");
		} else {
			//printf("breaking from loop\n");
			break;
		}
	}
	printf("Made it past while loop\n");
	char size_data[50];
	char temp[50];
	char temp2[50];
	// clears memory of what might have previously been there
	for (int y = 0; y < 50; y += 1) {
		size_data[y] = ' ';
		temp[y] = ' ';
		temp2[y] = ' ';
	} 

	fgets(size_data, 50, fr);
	// prints what is in array for verification purposes
	//for (int x = 0; x < 50; x += 1) {
	//	printf("%c", size_data[x]);
	//}
	//printf("\n");
	
	char num;
	
	// copy's first number from input to separate array to be converted to int
	int iterate = 0;
	while (size_data[iterate] != ' ') {
		temp[iterate] = size_data[iterate];
		iterate += 1;
	}

	int WIDTH = atoi(temp);
	
	// copies second num from input to separate array to be converted to int
	int iterate2 = iterate + 1;
	while (size_data[iterate2] != '\n' && size_data[iterate2] != ' ') {
		//printf("%c is what is in size_data\n", size_data[iterate2]);
		temp2[iterate2] = size_data[iterate2];
		iterate2 += 1;
	}

	int HEIGHT = atoi(temp2);

	printf("Width - %d, Height - %d\n", WIDTH, HEIGHT);


	// Skip any comment "#" to get the RGB max color value
	

	// Read input file into memory, else it can't be read from


	// If converting from P3 to P6, change the ASCII decimal to binary
	

	// If converting from P6 to P3, convert the binary to ASCII decimal
	

}
