<b>Author</b>

Jasque Saydyk - jrsaydyk@gmail.com

<b>Purpose</b>

The purpose of the is program is to convert a P3 or P6 PPM image file inbetween one another. Given any other input, or an inproperly formated file or file name, with result in an error. These files must be in 24 bit RGB color.

<b>Usage</b>

To use this program to convert a P3 to P3 or P6, or a P6 to P3 or P6, enter the following argrument into the console

<pre><code>ppmrw 3 input.ppm output.ppm</code></pre>
<pre><code>ppmrw 6 input.ppm output.ppm</code></pre>

+ ppmrw - The program's name
+ 3 or 6 - The program will convert the input file to a P3 file
+ input.ppm - The input file to be converted, must be a ppm file that is properly formatted
+ output.ppm - The name of the output file that is converted, must end in .ppm

<b>Assumptions</b>

A properly formated image header will abide by these standards:

+ The "magic number" of the file. This must be either "P3" or "P6"
+ Any amount of comments with a "#" at the beginning may appear anywhere except for the first and last entry
+ The width and height of the image, separated by a space as an ASCII decimal number
+ The maximum color value in ASCII decimal, which should normally be 255

After the image's header, it is followed by the description of image in ASCII for P3 files and raw binary for P6 image files

For interpreting the P3 files:

Each line after the header represents a portion of a color, with 3 lines being the RGB color of a single pixel

    255
    255
    255


For interpreting the P6 files:

The binary values are a single line containing all of the values, with each group of 8 bits representing the hex value of a portion color of the pixel. Each 24 bits represent the RGB color of a single pixel. Below is an example of how this looks, but there are no spaces in the actual file.

    11111111 11111111 11111111
