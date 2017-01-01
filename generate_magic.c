#include <stdio.h>
#include <stdlib.h>

// Structure representing Square
// size: dimension(number of rows/columns) of the square
// array: 2D array of integers
typedef struct _Square {
	int size;
	int **array;
} Square;

int get_square_size();
Square * generate_magic(int size);
void write_to_file(Square * square, char *filename);

int main(int argc, char *argv[])
{
	// Check input arguments to get filename
	if(argc < 2){
		printf("%s\n", "Usage: ./generate_magic <filename>");
		exit(1);
	}
	// Get size from user
	int size = get_square_size();
	// Generate the magic square
	Square* sq = malloc(sizeof(Square));
	sq = generate_magic(size);
	// Write the square to the output file
	write_to_file(sq, *(argv+1));
	return 0;
}

// get_square_size prompts the user for the magic square size
// checks if it is an odd number >= 3 and returns the number
int get_square_size()
{
	int* size = malloc(sizeof(int));
	// prompt user to enter size of square
	printf("%s\n", "Enter size of magic square, must be odd");
	scanf("%d", size);
	// check if size is under 3
	if(*size < 3 || *size % 2 == 0){
		printf("%s\n", "Size must be an odd number >= 3.");
		exit(1);
	}
	return *size;
}

// generate_magic constructs a magic square of size n
// using the Siamese algorithm and returns the Square struct
Square * generate_magic(int n)
{

	Square* sqr = malloc(sizeof(Square));
	sqr->size = n;
	// allocate memory location for the array
	sqr->array = malloc(sizeof(int*)*n);
	for(int i = 0; i < n; i++){
		*(sqr->array+i) = malloc(sizeof(int)*n);
	}
	// initialize every location of int to 0
	for(int j = 0; j < n; j++){
		for(int k = 0; k < n; k++){
			*(*(sqr->array+j)+k) = 0;
		}
	}

	// put start location of 1
	int r = 0;
	int c = (n-1)/2;
	for(int i = 1; i <= n*n; i++){
		*(*(sqr->array+r)+c) = i;
		// temporarily store the value of current row and column
		int tempr = r;
		int tempc = c;
		// if the number of row is at the boundary, set it to the other end
		// else increment
		if(r == 0){
			r = n-1;
		}
		else{
			r--;
		}
		// if the number of column is at the boundary, set it to the other end
		// else increment
		if(c >= n-1){
			c = 0;
		}
		else{
			c++;
		}
		// check if the new location is occupied, if yes, change the new location accordingly
		if(*(*(sqr->array+r)+c) != 0){
			r = tempr + 1;
			c = tempc;
		}
	}
	return sqr;
}

// write_to_file opens up a new file(or overwrites the existing file)
// and writes out the square in the format expected by verify_magic.c
void write_to_file(Square * square, char *filename)
{
	// initialize a pointer for file
	FILE *fp = malloc(sizeof(FILE));
	// open the file for writing
	fp = fopen(filename, "w");
	// write the square size to file
	fprintf(fp, "%d\n", square->size);
	for(int i = 0; i < square->size; i++){
		for(int j = 0; j < square->size-1; j++){
			fprintf(fp, "%d,", *(*(square->array+i)+j));
		}
		fprintf(fp, "%d\n", *(*(square->array+i)+square->size-1));
	}
	fclose(fp);
}
