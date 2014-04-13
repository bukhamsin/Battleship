/***********************************************************************************
 * Abdullah Bukhamsin                                                              *
 * April 8, 2014                                                                   *
 * Programming Assignment 6                                                        *
 * Description: This Program implements a battleship game according to some rules. *
 *		The player plays against a computer. once the game is done. Stats  *
 *		of the game is outputted to a log file.                            *
 ***********************************************************************************/

#include "battleship.h"
#include "battleship.h"

int main (void)
{
	int option = 0, rand_man = 0, sunk_p1 = 0, sunk_cpu = 0, direction = 0,
		row_start = 0, col_start = 0, invalid = 0, random = 0, 
		cpu_hits = 0, cpu_misses = 0, p1_hits = 0, p1_misses = 0,
		total_hits = 0, total_misses = 0, ratio = 0;

	FILE *infile = NULL;

	char p1_game_board[10][10] = {{'\0', '\0'}, {'\0'}};
	char cpu_game_board[10][10] = {{'\0', '\0'}, {'\0'}};
	char updated_board[10][10] = {{'\0', '\0'}, {'\0'}};

	srand ((unsigned int) time (NULL));
	infile = fopen ("battleship.log", "w");
	fprintf (infile, "------Game Data------\n\n");

	do
	{
		do 
		{
			system ("cls"); // to clear the screen.
			printf ("Hello, and welcome to Battleship!\n"
					"Press [1] to display the game rules.\n"
					"Press [2] to play the game.\n"
					"Press [3] to exit.\n");
			scanf ("%d", &option);

		} while ((option < 1) || (option > 3)); // to make sure that inputs are between 1 and 3.

		if (option == 1) // if option equals to 1, print game rules.
		{
			print_game_rules();
			system ("pause");
		}

		else if (option == 2) // if option equals to 2, start the game.
		{
			system ("cls");

			init_game_board (p1_game_board, 10, 10);
			init_game_board (cpu_game_board, 10, 10);
			init_game_board (updated_board, 10, 10);

			randomly_place_ships (cpu_game_board, 'c', 5, direction, row_start, col_start);
			randomly_place_ships (cpu_game_board, 'b', 4, direction, row_start, col_start);
			randomly_place_ships (cpu_game_board, 'r', 3, direction, row_start, col_start);
			randomly_place_ships (cpu_game_board, 's', 3, direction, row_start, col_start);
			randomly_place_ships (cpu_game_board, 'd', 2, direction, row_start, col_start);

			printf ("now the computer will choose randomly who starts first.\n");
			system ("pause");
			select_who_starts_first (&random);

			if (random)
			{
				printf ("You were chosen to start first.\n");
				system ("pause");
				system ("cls");

				printf ("Press [1] if you want to place ships manually.\n"
						"Press any other number if you want to place ships randomly.\n");
				scanf ("%d", &rand_man);
				
				if (rand_man == 1)
				{
					manually_place_ships (p1_game_board, 'c');
					manually_place_ships (p1_game_board, 'b');
					manually_place_ships (p1_game_board, 'r');
					manually_place_ships (p1_game_board, 's');
					manually_place_ships (p1_game_board, 'd');
				}

				else 
				{
					randomly_place_ships (p1_game_board, 'c', 5, direction, row_start, col_start);
					randomly_place_ships (p1_game_board, 'b', 4, direction, row_start, col_start);
					randomly_place_ships (p1_game_board, 'r', 3, direction, row_start, col_start);
					randomly_place_ships (p1_game_board, 's', 3, direction, row_start, col_start);
					randomly_place_ships (p1_game_board, 'd', 2, direction, row_start, col_start);
				}

				do
				{
					system ("cls");
					printf ("  ---Player Board---\n\n");
					print_board (p1_game_board, 10, 10);
			
					printf ("\n\n  --Computer Board--\n\n");
					update_board (cpu_game_board, updated_board, 10, 10);

					//print_board (cpu_game_board, 10, 10); // uncomment this for easier testing

					target_shot (cpu_game_board, row_start, col_start, infile, &p1_hits, &p1_misses);
					random_shot (p1_game_board, row_start, col_start, infile, &cpu_hits, &cpu_misses);
					
					sunk_p1 = check_if_sunk_ship (p1_game_board);
					sunk_cpu = check_if_sunk_ship (cpu_game_board);

				} while (sunk_p1 == 1 && sunk_cpu == 1);
			}
		
			else
			{
				printf ("The computer will start first.\n"
						"But you need to set up your fleet.\n");
				
				system ("pause");
				system ("cls");

				printf ("Press [1] if you want to place ships manually.\n"
						"Press any other number if you want to place ships randomly.\n");
				scanf ("%d", &rand_man);

				if (rand_man == 1)
				{
					manually_place_ships (p1_game_board, 'c');
					manually_place_ships (p1_game_board, 'b');
					manually_place_ships (p1_game_board, 'r');
					manually_place_ships (p1_game_board, 's');
					manually_place_ships (p1_game_board, 'd');
				}

				else 
				{
					randomly_place_ships (p1_game_board, 'c', 5, direction, row_start, col_start);
					randomly_place_ships (p1_game_board, 'b', 4, direction, row_start, col_start);
					randomly_place_ships (p1_game_board, 'r', 3, direction, row_start, col_start);
					randomly_place_ships (p1_game_board, 's', 3, direction, row_start, col_start);
					randomly_place_ships (p1_game_board, 'd', 2, direction, row_start, col_start);
				}
			}

			do
			{
				system ("cls");
			

				random_shot (p1_game_board, row_start, col_start, infile, &cpu_hits, &cpu_misses);

				printf ("  ---Player Board---\n\n");
				print_board (p1_game_board, 10, 10);

				printf ("\n\n  --Computer Board--\n\n");
				update_board (cpu_game_board, updated_board, 10, 10);
			
				//print_board (cpu_game_board, 10, 10); // uncomment this for easier testing
						
				target_shot (cpu_game_board, row_start, col_start, infile, &p1_hits, &p1_misses);
				
				sunk_p1 = check_if_sunk_ship (p1_game_board);
				sunk_cpu = check_if_sunk_ship (cpu_game_board);

			} while (sunk_p1 == 1 && sunk_cpu == 1);

			if (sunk_p1)
			{
				printf ("You win!\n"
						"Stats outputted to log file successfuly.\n");
				fprintf (infile, "\n------Game Result------\n\n"
								 "Player won\n");
			}

			else
			{
				printf ("You lost!\n"
						"Stats outputted to log file successfuly.\n");
				fprintf (infile, "\n------Game Result------\n\n"
								 "Computer won\n");
			}

			fprintf (infile, "\n------Player Stats------\n\n"
								"total hits: %d\n"
								"total misses: %d\n"
								"total shots: %d\n"
								"Accuracy: %.2lf%%\n",
								p1_hits, p1_misses, p1_hits + p1_misses, 
								(double) p1_hits * 100 / (p1_hits + p1_misses));
								
			fprintf (infile, "\n-----Computer Stats-----\n\n"
								"total hits: %d\n"
								"total misses: %d\n"
								"total shots: %d\n"
								"Accuracy: %.2lf%%",
								cpu_hits, cpu_misses, cpu_hits + cpu_misses, 
								(double) cpu_hits * 100 / (cpu_hits + cpu_misses));
			// when the game is done, the data are printed to battleship.log
			fclose (infile);

			break;
		}

	} while (option == 1 || option == 2 ); // Keep looping if option equals to 1 or 2.

	return 0;
}
