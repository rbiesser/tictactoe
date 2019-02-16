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
#include <string.h> // bring in functions to manipulate the board like a string

// prototypes

/* We need a method to print the board */
void printBoard(char * board);

/* We need a method for the player to select a square */
int chooseSquare(char * board, char player, int choice);

/* We need a method to determine when a player has won */
int playerWins(char * board, char player);

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

	// variable to track how may turns are left in this game
	int openSquares = 9;

	// variable for main app loop
	char playAgain = 'y';

	// keep playing until user exits
	while (playAgain != 'n')
	{
		// reset game
		strncpy(board, "123456789", 9); // board is a string which is an array of characters
		openSquares = 9;

		// currentPlayer stays the same from last game so it will alternate who starts

		// keep alternating between player turns until one wins or there are no more squares left
		while (openSquares > 0 && !playerWins(board, currentPlayer))
		{

			// alternate between players
			currentPlayer = (currentPlayer == player1) ? player2 : player1;

			do // chooseSquare will make sure the player makes a valid move or gives them another chance.
			{
				// give notice of the current player
				printf("\n%c to play...\n", currentPlayer);

				// displaying the board is as easy as calling the printBoard function
				// the board prints with the current state
				printBoard(board);

				// prompt the user for input
				printf("%s", "Choose a square on the board (1-9) ");
				scanf("%d", &choice);

					// the array is zero based but the player selects 1-9
			} while (!chooseSquare(board, currentPlayer, choice-1));

			// decreasing the number of squares available after each turn
			openSquares--;
		}

		// print the final game board
		printBoard(board);

		// if a player didn't win last turn, we know the board ran out of squares
		if (!playerWins(board, currentPlayer))
		{
			printf("\n%s\n", "This game is cat. =^_^= Play again.");
		}

		// prompt to continue
		printf("%s\n", "Play Again? (y/n) ");
		scanf(" %c", &playAgain);

	}

	return 1;

	// end main
}

/**
	We need a method to determine when a player has won 

	There are 8 ways to win

	1 2 3 = 6
	4 5 6 = 15
	7 8 9 = 24
	1 4 7 = 12
	2 5 8 = 15
	3 6 9 = 18
	1 5 9 = 15
	3 5 7 = 15

	@param the current player
	@return true when a player wins
*/
int playerWins(char * board, char player)
{
	// brute force would have you check every square in order
	// but we can use short circuit logic to find a winner.

	if (
		// zero based
		// horizontal
		(board[0] == player && board[1] == player && board[2] == player) ||
		(board[3] == player && board[4] == player && board[5] == player) ||
		(board[6] == player && board[7] == player && board[8] == player) ||

		// vertical
		(board[0] == player && board[3] == player && board[6] == player) ||
		(board[1] == player && board[4] == player && board[7] == player) ||
		(board[2] == player && board[5] == player && board[8] == player) ||

		// diagonal
		(board[0] == player && board[4] == player && board[8] == player) ||
		(board[2] == player && board[4] == player && board[6] == player)
		)
	{
		printf("\n%c WINS!\n", player);

		return 1; // exit loop and end game
	}

	return 0; // default to false

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
	-------------------------
			|		|
		4	|	5	|	6
			|		|
	-------------------------
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