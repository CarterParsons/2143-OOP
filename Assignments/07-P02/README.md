Program 2: Command-Line Argument Parser (imgtool)
Overview

This program builds a simple command-line argument parser for an image tool called imgtool.

The program does NOT process images. Instead, it:

reads command-line arguments (argc, argv)
validates inputs
stores the results in an Args class
prints a clean summary of the configuration
How to Build

Compile the program using:

g++ main.cpp Args.cpp -o imgtool
How to Run
./imgtool <input_image> <output_image> [options]

Example:

./imgtool in.png out.png --grayscale --brighten 20 --blur
Supported Options
Flags (no value required)
--grayscale or -g
--blur or -l
--flipH or -h
--flipV or -v
Options with Values
Brighten
--brighten N
-b N
--brighten=N
N must be an integer between -255 and 255
Rotate
--rotate N
-r N
--rotate=N
N must be one of: 0, 90, 180, 270
Example Commands
Valid Examples
./imgtool in.png out.png -g
./imgtool in.png out.png --blur --brighten 50
./imgtool in.png out.png -g -l -h -v
Invalid Examples
./imgtool in.png

Error: missing output file

./imgtool in.png out.png --brighten

Error: --brighten requires an integer value

./imgtool in.png out.png --rotate 45

Error: rotate must be one of {0, 90, 180, 270}

./imgtool in.png out.png --graycale

Error: unknown option --graycale

Output Format

If successful, the program prints:

INPUT  : in.png
OUTPUT : out.png
FLAGS  : grayscale blur flipH
PARAMS : brighten=20 rotate=90

Only enabled flags and parameters are shown.

Design

The program uses an Args class to store:

input and output filenames
flags (booleans)
options with values

Parsing is handled using a static method:

static Args parse(int argc, char* argv[]);

This keeps the code clean and separates parsing logic from main.

Notes
The program stops on the first error
All error messages are clear and descriptive
Only valid inputs are accepted