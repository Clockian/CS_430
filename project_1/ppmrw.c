#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

	// Checks if the # of arguements is correct
	if (argc != 4) {
		printf("Error: ppmrw CONVERT-TO-# INPUT-FILE OUTPUT-FILE\n");
		return 1;
	}

	// Check if arg 1 is a 3 or 6
	// If conversion section of program was complete, it would dictate
	// which conversion section it would go through
	int conversion_num = atoi(argv[1]);
	if (conversion_num != 3 && conversion_num != 6) {
		printf("Usage: Choose between '3' for P3 or '6' for P6\n");
		return 1;
	}
	
	// Check file names to see if they
	// 	-Check if files exists
	// 	-End in .ppm ### Scratch, not possible, magic number replicates this
	// 	-input and output filename are different ### unable to do without comparing everything in each other
	FILE *fr = fopen(argv[2], "r");
	if (fr == NULL) {
		printf("Input file does not exist\n");
		return 1;
	}

	// Read "magic number" in the file for P3 or P6
	char magicnum1 = fgetc(fr);
	char magicnum2 = fgetc(fr);
	char newline = fgetc(fr);
	if (magicnum1 != 'P' && magicnum2 != '3' || magicnum1 != 'P' && magicnum2 != '6') {
		printf("Error: Incorrect magic number");
		return 1;
	}
	
	// Skip any comments "#" to get the "HEIGHT WIDTH"
	// Didn't know fscanf existed at time of writing
	char next_char = fgetc(fr);
	while (1) {
		if (next_char == '#') {
			while (next_char != '\n') {
				next_char = fgetc(fr);
			}
		} else {
			break;
		}
	}

	// Clearing memory of arrays, didn't know memset existed at time of writing, maybe useless code
	char size_data[50];
	char temp[50];
	char temp2[50];
	char rgb_data[50];
	for (int y = 0; y < 50; y += 1) {
		size_data[y] = ' ';
		temp[y] = ' ';
		temp2[y] = ' ';
		rgb_data[y] = ' ';
	} 

	fgets(size_data, 50, fr);
	
	// Goal: Converting Height and Width into int's
	// It does this by finding splitting the string by the space into 2 separate
	// strings, then converts each on into int

	// Copy's first number from input to separate array to be converted to int
	int iterate = 0;
	while (size_data[iterate] != ' ') {
		temp[iterate] = size_data[iterate];
		iterate += 1;
	}

	// Copies second num from input to separate array to be converted to int
	int iterate2 = iterate + 1;
	while (size_data[iterate2] != '\n' && size_data[iterate2] != ' ') {
		temp2[iterate2] = size_data[iterate2];
		iterate2 += 1;
	}

	int WIDTH = atoi(temp);
	int HEIGHT = atoi(temp2);

	// Skip any comment "#" to get the RGB max color value
	char next_char_array[50];
	fgets(next_char_array, 49, fr);
	while (1) {
		if (next_char_array[0] == '#') {
			fgets(next_char_array, 49, fr);
		} else {
			break;
		}
	}
	// Convert the RGB max color value to int
	int RGB_color = atoi(next_char_array);

	// Error check on RGB value, can't compute anything but 255
	if (RGB_color != 255) {
		printf("Error: Only RGB 255 color supported\n");
		return 1;
	}

	// Read the image data into memory, it acheives this by pre-setting the
	// end of the file, then reading into memory to that point
	char *memory;
	memory = malloc(sizeof(char) * WIDTH * HEIGHT * 3);
	
	long cur = ftell(fr);
	fseek(fr, 0, SEEK_END);
	long size = ftell(fr);
	fseek(fr,cur, SEEK_SET);

	fread(memory, size, 1, fr);
	fclose(fr);

	// Converting from P3 to P6, changing the ASCII decimal to binary
	// Explaination: Unable to find a pipeline to convert ASCII decimal
	// to binary. The solution presented is the only way I could find to
	// convert an ASCII decimal to binary, which I couldn't figure out how
	// to pipeline. This solutions "converts" the int RGB value 252 to hex
	// "fc". From there, the hex is squeezed into a single char, giving a
	// true single byte, correct result. The issue is being able to insert
	// any hex value into the string, which proved beyond my capablility.
	// The code has been cleaned of attempts to do so.
	
	FILE *fw;
	fw = fopen(argv[3], "w");
	char *s = "\xfc";
	fprintf(fw, "%c", *s);
	fclose(fw);
	
	// If converting from P6 to P3, convert the binary to ASCII decimal
	// Unable to get this far, as I ran out of time
}
