<b>Author</b>

Jasque Saydyk - jrsaydyk@gmail.com

<b>Purpose</b>

The purpose of this program is to create a functioning raycaster. This raycaster will have the following components:
+ Parser - to read the contents of a CSV file, then put that data into a usable data structure
+ Raycast - using the data, creates the scene and "takes the picture"
+ Store - store the "picture" as a P3 .ppm file

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

The test code is primarily unit tests on the functions created for this project

<b>Known Issues</b>

The following are unresolved issues with the program

+ Raycast.c incomplete, doesn't produce the image of the scene
+ Program doesn't store the image as a .ppm

This project has made me realize that I am remarkably bad with C, as it took me the past week and a half to get the parser functioning correctly, and before that I burnt alot of time re-exploring how a raycaster functions so I could get an idea to complete the project.

<b>Description of Files</b>
+ raycast.c - Main program file
+ parser.c - Converts each line from a compatible .csv file into a struct containing the data for the file, and those structs are stored in an array, which is used by the main program file
+ parser.h - Header file for parser.c, defines the struct the data uses
+ math3D.c - Contains vector math functions, because I was unable to figure out static inline functions
+ math3D.h - Contains the struct for a vector
+ README.md - Readme file describing the project
+ test_parser.c - The tests for the program, only tests parser.c at the moment
+ makefile - Interpets the two different compilation methods for the program
+ makefile.raytracer - Specifies the compilation for the raycaster
+ makefile.test - Specifies the compilation for the test
+ input.csv - The example .csv input provided with the project