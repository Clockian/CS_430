#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
	char rgb_data[50];
	// clears memory of what might have previously been there
	for (int y = 0; y < 50; y += 1) {
		size_data[y] = ' ';
		temp[y] = ' ';
		temp2[y] = ' ';
		rgb_data[y] = ' ';
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

	printf("Width -> %d, Height -> %d\n", WIDTH, HEIGHT);

	//printf("next_char, before = %c\n", next_char);


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

	int RGB_color = atoi(next_char_array);
	printf("RGB_color = %d\n", RGB_color);

	// Error check on RGB value, can't compute anything but 255
	if (RGB_color != 255) {
		printf("Error: Only RGB 255 color supported\n");
		return 1;
	}

	// Read input file into memory, else it can't be read from
	char *memory;
	memory = malloc(sizeof(char) * WIDTH * HEIGHT * 3);
	long cur = ftell(fr);
	fseek(fr, 0, SEEK_END);
	long size = ftell(fr);
	fseek(fr,cur, SEEK_SET);

	fread(memory, size, 1, fr);
	fclose(fr);
	
	printf("Output from memory begins\n");

	for (int x = 0; x < 13; x +=1 ) {
		printf("%c", *(memory + sizeof(char)*x));
	}
	printf("\n");

	// If converting from P3 to P6, change the ASCII decimal to binary
	char conv_char_int[4];
	conv_char_int[0] = *(memory);
	conv_char_int[1] = *(memory + sizeof(char));
	conv_char_int[2] = *(memory + sizeof(char)*2);
	conv_char_int[3] = *(memory + sizeof(char)*3);

	int pixel_rgb = atoi(conv_char_int);
	printf("%d\n", pixel_rgb);
	
	// Convert int to hex, then later concatone to offically declare hex
	//int hex_remainder1;
	//int hex_remainder2;
	//hex_remainder1 = pixel_rgb % 16;
	//pixel_rgb = pixel_rgb / 16;
	//hex_remainder2 = pixel_rgb % 16;

	//printf("%d, %d\n", hex_remainder1, hex_remainder2);
	//char holding_hex[2];
	//sprintf(holding_hex, "%x", pixel_rgb);
	//for(int x =0; x<2;x++){
	//	printf("%c", holding_hex[x]);
	//}
	//printf("\n");
	
	//holding_hex[3] = holding_hex[1];
	//holding_hex[2] = holding_hex[0];
	//holding_hex[1] = 'x';
	//holding_hex[0] = '\\';

	//for(int x =0; x<4;x++){
	//	printf("%c", holding_hex[x]);
	//}
	//printf("\n");

/*	char *hex2;
	if (hex_remainder2 < 10) {
		*hex2 = hex_remainder2 + '0';
	} else if (hex_remainder2 == 10) {
		*hex2 = 'a';
	} else if (hex_remainder2 == 11) {
		*hex2 = 'b';
	} else if (hex_remainder2 == 12) {
		*hex2 = 'c';
	} else if (hex_remainder2 == 13) {
		*hex2 = 'd';
	} else if (hex_remainder2 == 14) {
		*hex2 = 'e';
	} else if (hex_remainder2 == 15) {
		*hex2 = 'f';
	}


	char *hex1;
	if (hex_remainder1 < 10) {
		*hex1 = hex_remainder1 + '0';
	} else if (hex_remainder1 == 10) {
		*hex1 = 'a';
	} else if (hex_remainder1 == 11) {
		*hex1 = 'b';
	} else if (hex_remainder1 == 12) {
		*hex1 = 'c';
	} else if (hex_remainder1 == 13) {
		*hex1 = 'd';
	} else if (hex_remainder1 == 14) {
		*hex1 = 'e';
	} else if (hex_remainder1 == 15) {
		*hex1 = 'f';
	}
*/
	//printf("%c\n", hex1);
	
	// Concatonate both hex chars together with \x
	//char *hex22 = (char)hex2;
	//char *hex11 = (char)hex1;
	
//	char *init = "\x%s", holding_hex;
	//char *concatonate;
	//concatonate = malloc(sizeof(char) * 4);
	//strcpy(concatonate, "\x");

	//char binary_rgb[8];
	//for(int x = 7; x != 0; x--) {
	//	if(pixel_rgb % 2 == 0){
	//		binary_rgb[x] = '0';
	//	} else {
	//		binary_rgb[x] = '1';
	//	}
	//	pixel_rgb = pixel_rgb/2;
	//}
	//printf("Binary = ");
	//for(int x = 0; x < 8; x++){
	//	printf("%c", binary_rgb[x]);
		//printf("here");
	//}
	//printf("\n");

	FILE *fw;
	fw = fopen(argv[3], "w");

	//unsigned char testing_raw = 'fc';
	char *s = "\xfc";

	//for (int x = 0; x < 8; x++) {
	fprintf(fw, "%c", *s);//binary_rgb[x]);
	//}
	

	//fprintf(fw, "%x", pixel_rgb);
	
	fclose(fw);

	//char binary_rgb[8];
	//itoa(pixel_rgb, binary_rgb, 2);
	//printf("Binary = %s\n", binary_rgb);

	// If converting from P6 to P3, convert the binary to ASCII decimal
}
