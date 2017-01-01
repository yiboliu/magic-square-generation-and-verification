#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure representing Square
// size: dimension(number of rows/columns) of the square
// array: 2D array of integers
typedef struct _Square {
	int size;
	int **array;
} Square;

Square * construct_square(char *filename);
int verify_magic(Square * square);

int main(int argc, char *argv[])
{
	// Check input arguments to get filename
	if(argc < 2){
		printf("%s\n", "Usage: ./verify_magic <filename>");
		exit(1);
	}
	FILE *fp = fopen(*(argv+1), "r");
	if(fp == NULL){
		fprintf(stderr, "Cannot open file for reading.\n");
		exit(1);
	}
	fclose(fp);
	// Construct square
	Square *sq = construct_square(*(argv+1));
	// Verify if it's a magic square and print true or false
	if(verify_magic(sq) == 1) printf("%s\n", "true");
	else printf("%s\n", "false");
	return 0;
}

// construct_square reads the input file to initialize a square struct
// from the contents of the file and returns the square.
// The format of the file is defined in the assignment specifications
Square * construct_square(char *filename)
{
	// Open and read the file
	FILE *fp = fopen(filename, "r");
  // Read the first line to get the square size
	int *size = malloc(sizeof(int));
	fscanf(fp, "%d", size);
 	// Initialize a new Square struct of that size
  Square *sq = malloc(sizeof(Square));
	sq->size = *size;
 	// Read the rest of the file to fill up the square
	int **table = malloc(sizeof(int*)*(*size));
	for(int i = 0; i < sq->size; i++){
		*(table+i) = malloc(sizeof(int)*sq->size);
	}
	// read each line in the file recursively
	const size_t line_size = 100;
	char* tempLine = malloc(line_size);
	int i = 0;
	fgets(tempLine, line_size, fp);
	while (fgets(tempLine, line_size, fp) != NULL)  {
		int j = 0;
		for (char *p = strtok(tempLine,","); p != NULL; p = strtok(NULL, ",")){
  		*(*(table+i)+j) = atoi(p);
			j++;
		}
		i++;
	}
	free(tempLine);
	fclose(fp);
	// assign the value of array in sq
	sq->array = table;
 	return sq;
}

// verify_magic verifies if the square is a magic square
// returns 1(true) or 0(false)
int verify_magic(Square * square)
{
	int sum = 0;
	for(int i = 0; i < square->size; i++){
		sum += *(*(square->array)+i);
	}
	// Check all rows sum to same number
	for(int j = 1; j < square->size; j++){
		int temp = 0;
		for(int k = 0; k < square->size; k++){
			temp += *(*(square->array+j)+k);
		}
		if(temp != sum) return 0;
	}
	// Check all cols sum to same number
	for(int l = 0; l < square->size; l++){
		int temp = 0;
		for(int m = 0; m < square->size; m++){
			temp += *(*(square->array+m)+l);
		}
		if(temp != sum) return 0;
	}
	// Check main diagonal
	int temp = 0;
	for(int n = 0; n < square->size; n++){
			temp += *(*(square->array+n)+n);
	}
	if(temp != sum) return 0;
	// Check secondary diagonal
	temp = 0;
	int p = square->size-1;
	for(int o = 0; o < square->size; o++){
			temp += *(*(square->array+o)+p);
			p--;
	}
	if(temp != sum) return 0;
	return 1;
}
