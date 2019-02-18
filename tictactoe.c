/**
	Tic Tac Toe
	tictactoe.c

	* Two players compete to match 3 squares in a row by take alternating turns 
	placing their letter on the board.

	* Matches can be horizontal, vertical, or diagonal.

	* The C language does some weird things and can be more difficult than other
	scripting languages. This application presents easy solutions while exploring
	the C language.

	* The methods presented are a first step in using functions and passing variables
	by reference. A cleaner solution may exist by creating the board object and the
	player object.

	---------------------------------------------------------------------------

	* compile with gcc 
	gcc tictactoe.c -o tictactoe

	---------------------------------------------------------------------------

	TODO
	* computer player [complete]
		* how many players? 0 1 2
	* track stats: w/l turns
	* how many game variations are there?
	* will the starting player win every time?
	* replace magic numbers with macro names

	---------------------------------------------------------------------------

	AI strategies
		> do you want to allow choosing computer difficulty?
		> randomize difficulty?
		> can we build a strategy to win everytime?
	* middle
	* corners
	* block
	* random [complete]
		> computer may occasionally make intelligent moves but will not purposefully
			try to block a winning move.
	* edges

	https://www.quora.com/Is-there-a-way-to-never-lose-at-Tic-Tac-Toe
		> discussion of strategies

	---------------------------------------------------------------------------

	Simulation
	1234567 player 1 wins in 4 moves

*/

#include <stdio.h> // standard library for printf and scanf
#include <string.h> // bring in functions to manipulate the board like a string
#include <stdlib.h> // for rand()
#include <time.h>

// prototypes

/* We need a method to print the board */
void printBoard(char * board);

/* We need a method for the player to select a square */
int chooseSquare(char * board, char player, int choice);

/* We need a method to determine when a player has won */
int playerWins(char * board, char player);

/* copies the available squares on the board to the vision board */
int getOpenSquares(char * board, char * aiBoardVision);

// int getChosenSquares(char * board, char * aiBoardVision, char player);

/* the players will either be an X or an O and represented as a macro */
#define player1 'X'
#define player2 'O'

/**
	Program execution starts in main
*/
int main()
{
	srand(time(0));

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

	int gameMode; // 0 = 2 ai players, 1 = 1 human vs 1 ai, 2 = 2 human players

	// we need a variable to distinguish a human player vs ai player
	// might be easier to eventually create a player object
	int player1Type =1; // 1 represents human player
	int player2Type =1; // 0 = ai player
	int currentPlayerType; // temp variable similar to currentPlayer

	char aiBoardVision[10] = ""; // a look at how the computer sees the board
						   // might could find a better name but we need some way to tell the
						   // computer what squares are remaining
						   // maybe replace openSquares and use string length instead of int

	// keep playing until user exits
	while (playAgain != 'n')
	{
		// select the players (game mode)
		printf("%s", "Select a game mode:\n");
		printf("%s", "0. Simulate play with 2 ai players\n");
		printf("%s", "1. Play against the computer\n");
		printf("%s", "2. Play against a friend\n");
		scanf("%d", &gameMode);

		switch(gameMode)
		{
			// letters translate as case 0 when expecting a digit
			case 0:
				player1Type = player2Type = 0;
				printf("%s", "\nSimulation Mode\n");
				break;
			case 1: 
				player1Type = 1;
				player2Type = 0;
				printf("%s", "\nPlaying against the computer\n");
				break;
			case 2:
				player1Type = player2Type = 1; 
				printf("%s", "\n2 Player Mode\n");
				break;
			// any other integer
			default:
				player1Type = player2Type = 0; 
				printf("%s", "\nUnrecognized Selection :: Starting Demo Mode\n");
		}

		// reset game
		strncpy(board, "123456789", 9); // board is a string which is an array of characters
		openSquares = 9;

		// currentPlayer stays the same from last game so it will alternate who starts

		// keep alternating between player turns until one wins or there are no more squares left
		while (openSquares > 0 && !playerWins(board, currentPlayer))
		{

			// alternate between players
			currentPlayer = (currentPlayer == player1) ? player2 : player1;
			currentPlayerType = (currentPlayer == player1) ? player2Type : player1Type;


			// give notice of the current player
			printf("\n%c to play...\n", currentPlayer);

			// human player enters choice from input
			if (currentPlayerType == 1) // 1 = human player
			{
				do // chooseSquare will make sure the player makes a valid move or gives them another chance.
				{
					// give notice of the current player
					// printf("\n%c to play...\n", currentPlayer);

					// displaying the board is as easy as calling the printBoard function
					// the board prints with the current state
					printBoard(board);

					// prompt the user for input
					printf("%s", "Choose a square on the board (1-9) ");
					scanf("%d", &choice);

						// the array is zero based but the player selects 1-9
				} while (!chooseSquare(board, currentPlayer, choice-1));
			}
			else // ai player runs functions
			{

				int j;

				// ai player needs to decide which square to choose
				j = getOpenSquares(board, aiBoardVision);

				// debug size of aiBoardVision
				// printf("sizeof: %d\n", j); 

				// aiBoardVision contains the possible choices still left on the board
				// printf("aiBoardVision: %s\n", aiBoardVision);

				// the null pointer keeps moving but the whole array is still addressable
				// printf("aiBoardVision: %c\n", aiBoardVision[8]);

				/**

					adding logic to change how the ai makes a choice should be done here
				
				*/

				// random
				choice = aiBoardVision[rand() % j] - '0'; // ascii characters for numbers
														  // subtract zero to get int value 
														  // https://stackoverflow.com/a/628766

				// debug
				// printf("currentPlayer: %c choice: %c\n", currentPlayer, choice);

				// and uses the same call to chooseSquare as human player
				chooseSquare(board, currentPlayer, choice-1);

				// it can be helpful to let a human player know what the computer did
				printf("Computer chose %d\n", choice);
			}

			// decreasing the number of squares available after each turn
			// could be using getOpenSquares method but keeping a running calculator might be more efficient
			// although its replacing an extra variable with a function call
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
	@return int zize of aiBoardVision 
	@param aiBoardVision containing squares remaining to be played 

	C doesn't have a method like sizeof that tells the number of elements 
	in an array, only the size of memory allocated. This function will
	both return the size and the values in the array
	https://www.quora.com/How-do-I-find-the-length-of-an-array-in-C


	take care when passing strings
	https://stackoverflow.com/a/25799033
*/
int getOpenSquares(char * board, char * aiBoardVision)
{
	// reset vision board each time
	// found that this only works with string functions and not array access
	strcpy(aiBoardVision, "\0");
	// printf("aiBoardVision: %s\n", aiBoardVision);
	int i;
	int j; // j is tracking the count of squares still remaining

	j = 0;
	// loop through the board and add to vision board when a square is still open
	for (i = 0; i < 9; i++)
	{
		if (board[i] != player1 && board[i] != player2)
		{	
			aiBoardVision[j] =  board[i];
			j++;
		}

		// C strings end with null character
		// this is only useful when printing as a string but array elements past null are still accessible
		aiBoardVision[j] = '\0';
	}

	return j; // return count
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
	if (choice < 0 || choice > 8 || board[choice] == player1 || board[choice] == player2)
	{	
		// temp board to hold open squares
		char aiBoardVision[10];
		
		// getOpenSquares returns int, but setting to a value is not necesary
		getOpenSquares(board, aiBoardVision);

		printf("\n!NOTICE: Choose from one of these open squares: %s\n", aiBoardVision);

		return 0; // try again
	}

	// a valid choice has been made and gets set to the player's character
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