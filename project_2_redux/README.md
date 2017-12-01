<b>Author</b>

Jasque Saydyk - jrsaydyk@gmail.com

<b>Purpose</b>

The purpose of this program is to create a functioning raycaster. This raycaster will have the following components:
+ Parser - to read the contents of a CSV file, then put that data into a usable data structure
+ Raycast - using the data, creates the scene and "takes the picture"
+ Writer - stores the "picture" as a P6 .ppm file

<b>Usage</b>

To use this program to create an image, enter the following argument into the terminal

<pre><code>./raycast width height input.csv output.ppm</code></pre>

+ ./ - optional, but maybe required on your system to run to program
+ raycast - the name of the main file of the program
+ width - the number of pixels wide the image will be
+ height - the number of pixels high the image will be
+ input.csv - the name of the input file for the project, must be .csv
+ output.ppm - the name of the output file for the project, must be .ppm

To compile the raycast program, enter the following into the terminal to run the makefile for the program

<pre><code>make</code></pre>


To generate the test enviroment for this program, enter the following into the terminal to compile the test code

<pre><code>make test</code></pre>

The test code can be ran with the following argument in the terminal

<pre><code>./test</code></pre>

The test code is primarily unit tests on the functions to ensure they work. They do not test for incorrect input or program misusage as of yet.

<b>Known Issues</b>

The following are unresolved issues with the program

+ Raycast.c incomplete, doesn't produce the image of the scene

Raycast.c has implemented the obtaining of Rd and normalizing it, but the intersection test and obtaining the color data has yet to be implemented.

This project will be updated on the Github until it is completed

<b>Description of Files</b>
+ raytracer.c - Main program file
+ raycast.c - Has functions necessary for the for the raycasting.
+ parser.c - Converts each line from a compatible .csv file into a struct containing the data for the file, and those structs are stored in an array, which is used by the main program file
+ writer.c - Writes a given file to disk as a P6 .ppm
+ raycast.h - Defines the struct for a vector, misnamed as pixel
+ parser.h - Defines the struct the data uses
+ writer.h - Defines the struct for the color of a pixel, named Pixel
+ README.md - Readme file describing the project
+ makefile - Interpets the two different compilation methods for the program
+ makefile.raytracer - Specifies the compilation for the raycaster
+ makefile.test - Specifies the compilation for the test
+ input.csv - The example .csv input provided with the project


+ test_main.c - The main file that runs all of the tests. Tests simply produce a print statement stating pass or fail
+ test_raycast.c - The unit tests for the raycaster
+ test_parser.c - The unit tests for the parser
+ test_writer.c - The unit test for the writer, produces checkerboard image that needs to be checked visually
