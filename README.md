# Huffman-Tree

This program uses the Tree Data Structure and command line parameters to run. This is the final project from my Data Structures II class and I created all of these files from scratch.

This program takes in a file for input and then creates a frequency table with the occurrences of each character in the file. The frequency table is sorted from the element with the highest frequency to the lowest. The huffman tree is created by making a table of tree nodes and two nodes are removed from the table to make a parent node with the merged elements and frequencies. Once the tree is created, it is traversed to create the encoding table. The encoding for each character is created by adding a 1 when it traverses to the left child and a 0 when it traverses to the right child. Then the encoding table is used to write the encoding for each character to the given output file based on how those characters appear in the input file.

## Running the Project

Download the project, navigate to it in Linux (I used Ubuntu), then use these commands to run it:

- `./huffman -encode inputfile outputfile`
	-	It will encode the file `inpufile` and create a file `outputfile` with the huffman encoding of the first file. It outputs the number of bytes written to the `outputfile`
- `./huffman -single inputfile c`
  - It will encode the file `inputfile`, and then it will print the string of 0's and 1's representing the given `c` character. If a string is given as the `c` parameter, it will only use the first character of the string
- `./huffman -frequency inputfile`
  - It will output to console the frequency table of the `inputfile`
- `./huffman -encoding-table inputfile`
  - It will output to console the encoding table of the `inputfile`

To remove all of the .o files, enter `make clean`

The available files that can be used to try out this program are: test-file-0.txt, test-file-1.txt, test-file-2.txt, and test-file-2.txt
