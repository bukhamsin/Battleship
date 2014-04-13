/***********************************************************************************
 * Abdullah Bukhamsin                                                              *
 * April 8, 2014                                                                   *
 * Programming Assignment 6                                                        *
 * Description: This Program implements a battleship game according to some rules. *
 *		The player plays against a computer. once the game is done. Stats  *
 *		of the game is outputted to a log file.                            *
 ***********************************************************************************/

#include "battleship.h"

/***************************************************
 * Function: print_game_rules ()                   *
 * Description:  Prints the game rules when called *
 ***************************************************/

void print_game_rules (void)
{
	system ("cls");
	printf ("Battleship rules are simple. Battleship is a two player Navy game.\n"
			"You are player 1 and the computer is player 2. The objective of the\n"
			"game is to sink all ships in your enemy's fleet. Whoever shinks all\n"
			"ships first wins. Both players' fleet consist of five ships that are\n"
			"hidden from the enemy. Each ship has a different length (besides the\n"
			"Cruiser and Submarine) The Carrier has 5 cells, Battleship has 4 cells,\n"
			"Cruiser and Submarine has 3 cells, and Destroyer has 2 cells.\n");
}

/***************************************************************
 * Function: select_who_starts_first ()                        *
 * Description:  randomize a number to decide who starts first *
 ***************************************************************/

void select_who_starts_first (int *random)
{
	*random = rand () % 2;
}

/************************************************
 * Function: init_game_board ()                 *
 * Description: initializes an empty game board *
 ************************************************/

void init_game_board (char board[10][10], int num_rows, 
					  int num_cols)
{
	int row_index = 0, col_index = 0;

	for (row_index = 0; row_index < num_rows; row_index++)
	{
		for (col_index = 0; col_index < num_cols; col_index++)
		{
			board[row_index][col_index] = '-';
		}
	}
}

/****************************************************
 * Function: print_board ()                         *
 * Description: prints the game board to the screen *
 ****************************************************/

void print_board (char board[10][10], int num_rows, int num_cols)
{
	int row_index = 0, col_index = 0;

	printf ("  0 1 2 3 4 5 6 7 8 9\n");

	for (row_index = 0; row_index < num_rows; row_index++)
	{
		printf ("%d ", row_index);
		for (col_index = 0; col_index < num_cols; col_index++)
		{
			printf ("%c ", board[row_index][col_index]);
		}
		putchar ('\n');
	}
}

/*****************************************************
 * Function: is_invalid_start_pt ()                  *
 * Description: checks if the start point to place a *
 *		ship is occupied                     *
 * Return: if the point is invalid or not            *
 *****************************************************/

int is_invalid_start_pt (char board [10][10], int row, int col, int dir, int length)
{
	int index = 0, invalid = 0;

	for (index = 0; index < length; index++)
	{
		if (dir)
		{
			if (board [row + index][col] != '-')
			{
				invalid = 1;
			}
		}
		
		else
		{
			if (board [row][col + index] != '-')
			{
				invalid = 1;
			}
		}
	}
	return invalid;
}

/*******************************************************
 * Function: randomly_place_ships ()                   *
 * Description: generates a random location to place a *
 *		ship. If the location is occupied then *
 *		place the ship in another location     *
 *******************************************************/

void randomly_place_ships (char board [10][10], char symbol, int length, int direction,
						   int row, int col)
{
	int invalid = 0, index = 0;
	
	do
	{
		direction = rand () % 2;
		
		if (direction) //vertical
		{
			row = (rand () % (10 - length + 1));
			col = rand () % 10;
		}
		else // horizontal
		{
			row = rand () % 10;
			col = (rand () % (10 - length + 1));
		}	

		invalid = is_invalid_start_pt (board, row, col,	direction, length);

	} while (invalid);

	for (index = 0; index < length; index++)
	{
		switch (direction)
		{
		case 0:  board[row][col + index] = symbol;
			     break;
		case 1: board[row  + index][col] = symbol;
			     break;
		}
	}
}

/****************************************************
 * Function: manually_place_ships ()                *
 * Description: takes the coordinates from the user *
 *		and place each ship accordingly     *
 ****************************************************/

void manually_place_ships (char game_board[10][10],char symbol) 
{
     int length = 0, row = 0, col = 0, count = 0;
     
     if (symbol == 'c')
     {
         length = 5;
         printf("Enter the 5 cells to place the Carrier.\n");
     }
     else if (symbol == 'b')
     {
         length = 4;
         printf("Enter the 4 cells to place the Battleship.\n");
     }
     else if (symbol == 'r' || symbol == 's')
     {
         length = 3;
         if (symbol == 'r')
         {
            printf("Enter the 3 cells to place the Cruiser.\n");
         }
         else 
         {
             printf("Enter the 3 cells to place the Submarine.\n");
         }
     }
     else
     {
         length = 2;
         printf("Enter the 2 cells to place the Destroyer.\n");
     }

     while (count < length)
     {
         printf("%d. Row: ", count + 1);
         scanf("%d", &row);
         printf("%d. Column: ", count + 1);
         scanf("%d", &col);
         
         if (game_board[row][col] == '-')
         {
            game_board[row][col] = symbol;
            count++;
         }
         else
         {
             printf("Ships cannot overlap. Enter different cells.\n");
         }
     }
}

/**********************************************************
 * Function: random_shot ()                               *
 * Description: chooses a random location to shoot in the *
 *		board. If the location is already shot    *
 *		then choose another location              *
 **********************************************************/

void random_shot (char board [10][10], int row_rand, int col_rand, FILE *infile,
				  int *hits, int *misses)
{
	int num_hits = *hits;
	int	num_misses = *misses;
	do
	{	
		row_rand = rand () % 10;
		col_rand = rand () % 10;

	} while (board [row_rand][col_rand] == '*' || board [row_rand][col_rand] == 'm');

	if (board[row_rand][col_rand] == '-')
	{
		board[row_rand][col_rand] = 'm';
		num_misses++;
		fprintf (infile, "CPU turn: (%d, %d) = miss\n", row_rand, col_rand);
	}

	else
	{
		board[row_rand][col_rand] = '*';
		num_hits++;
		fprintf (infile, "CPU turn: (%d, %d) = hit\n", row_rand, col_rand);
	}

	*hits = num_hits;
	*misses = num_misses;
}

/******************************************************
 * Function: target_shot ()                           *
 * Description: takes the coordinates of the point to *
 *		shoot from the user.                  *
 ******************************************************/

void target_shot (char board [10][10], int row, int col, FILE *infile,
				  int *hits, int *misses)
{
	int num_hits = *hits, num_misses = *misses;

	do
	{
		printf ("Enter the coordinates for the cell you want to shoot.\n");
		printf ("Row: ");
		scanf ("%d", &row);
		printf ("Col: ");
		scanf ("%d", &col);
	} while (board[row][col] == 'm' || board[row][col] == '*' || row > 9 || col > 9);

	if (board[row][col] == '-')
	{
		board[row][col] = 'm';
		num_misses++;
		fprintf (infile, "P1 turn: (%d, %d) = miss\n", row, col);

	}

	else
	{
		board[row][col] = '*';
		num_hits++;
		fprintf (infile, "P1 turn: (%d, %d) = hit\n", row, col);
	}

	*hits = num_hits;
	*misses = num_misses;
}

/*****************************************************
 * Function: update_board ()                         *
 * Description: displayes the computer board without *
		the ships and only the shots.        *
 *****************************************************/

void update_board (char board [10][10], char updated_board [10][10], 
				   int num_rows, int num_cols)
{
	int index = 0, row_index = 0, col_index = 0;

	updated_board = board;

	printf ("  0 1 2 3 4 5 6 7 8 9\n");

	for (row_index = 0; row_index < num_rows; row_index++)
	{
		printf ("%d ", row_index);
		for (col_index = 0; col_index < num_cols; col_index++)
		{
			if (updated_board[row_index][col_index] == 'm')
				printf ("m ");
			else if (updated_board[row_index][col_index] == '*')
				printf ("* ");
			else
				printf ("- ");
		}
		putchar ('\n');
	}
}

/************************************************
 * Function: check_if_sunk_ship ()              *
 * Description: checks if the ships are unsunk. *
 * Return: 1 as long as ships are unsunk.       *
 ************************************************/

int check_if_sunk_ship (char board [10][10])
{
	int row = 0, col = 0, count = 0, sunk = 0;

	for (row = 0; row < 10; row++)
	{
		for (col = 0; col < 10; col++)
		{
			if (board [row][col] != '-')
			{
				if (board [row][col] != '*' && board [row][col] != 'm')
				{
					count++;
				}
			}
		}
	}

	if (count > 0)
	{
		sunk = 1;
	}

	return sunk;
}
