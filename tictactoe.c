/**
	Tic Tac Toe
	tictactoe.c

	* Two players compete to match 3 squares in a row by take alternating turns 
	placing their letter on the board.

	* Matches can be horizontal, vertical, or diagonal.

	---------------------------------------------------------------------------

	* compile with gcc 
	gcc tictactoe.c -o tictactoe

*/

#include <stdio.h> // standard library for printf and scanf

// prototypes
void printBoard(char * board);

/**
	Program execution starts in main
*/
int main()
{
	// we're going to use an array to represent the locations on our board
	char board[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

	// displaying the board is as easy as calling the printBoard function
	printBoard(board);		

	return 1;

	// end main

}

/**
	@output: prints this board to standard output

			|		|
		1	|	2	|	3
			|		|
	--------------------------
			|		|
		4	|	5	|	6
			|		|
	--------------------------
			|		|
		7	|	8	|	9
			|		|

	@params: board is a single dimension array representing the locations on the grid
			 board is passed as a pointer to conserve memory
*/
void printBoard(char * board)
{
	printf("%10c%10c\n", '|', '|');
	printf("%5c%5c%5c%5c%5c\n", board[0], '|', board[1], '|', board[2]);
	printf("%10c%10c\n", '|', '|');
	printf("-----------------------------\n");
	printf("%10c%10c\n", '|', '|');
	printf("%5c%5c%5c%5c%5c\n", board[3], '|', board[4], '|', board[5]);
	printf("%10c%10c\n", '|', '|');
	printf("-----------------------------\n");
	printf("%10c%10c\n", '|', '|');
	printf("%5c%5c%5c%5c%5c\n", board[6], '|', board[7], '|', board[8]);
	printf("%10c%10c\n", '|', '|');

}