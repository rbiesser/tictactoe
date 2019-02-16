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

/* We need a method to print the board */
void printBoard(char * board);

/* We need a method for the player to select a square */
int chooseSquare(char * board, char player, int choice);

/* the players will either be an X or an O and represented as a macro */
#define player1 'X'
#define player2 'O'

/**
	Program execution starts in main
*/
int main()
{
	// we're going to use an array to represent the locations on our board
	char board[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

	// variable to keep track of alternating turns
	char currentPlayer = player2;

	// variable to hold the player's selection from the board
	int choice;

	// displaying the board is as easy as calling the printBoard function
	printBoard(board);

	// prompt the user for input
	printf("%s", "Choose a square on the board (1-9) ");
	scanf("%d", &choice);

	// the array is zero based but the player selects 1-9
	chooseSquare(board, currentPlayer, choice-1);

	// display the changed board
	printBoard(board);

	return 1;

	// end main
}

/**
	We need a method for the player to select a square

	@param board is passed by reference
	@param function accepts a player and a choice
	@return true on success or false if square is already taken
			The chosen location on the board is changed to hold the player's mark
*/
int chooseSquare(char * board, char player, int choice)
{
	// each square can only be marked once
	if (board[choice] == player1 || board[choice] == player2)
	{
		printf("\n%s\n", "!NOTICE: Choose from one of the open squares");

		return 0; // try again
	}

	board[choice] = player;

	return 1; // success
}

/**
	We need a method to print the board 

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

	@param board is a single dimension array representing the locations on the grid
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