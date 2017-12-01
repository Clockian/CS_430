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


To generate the test enviroment for this program, enter the following into the terminal to compile the test code. 

This will also automatically run the program with the following parameters

<pre><code>./raycast 80 60 input.csv raycast_output.ppm</code></pre>

This is for testing purposes, so I didn't have to type that command in repeatedly.

<pre><code>make -B test</code></pre>

The test code can be ran with the following argument in the terminal, which will also run the tests with this command.

<pre><code>./test</code></pre>

This command can also be used separatly to run the tests.

The test code is primarily unit tests on the functions to ensure they work. They do not test for incorrect input or program misusage as of yet.

<b>Known Issues</b>

Camera width and height is being loaded into raycast.c improperly. Temporarily rectified with constants

Closest t calculation bugged, so sphere appears behind plane

Didn't implement lighting or raytracing in any way, shape or form.

This project will be updated on the Github until it is completed
