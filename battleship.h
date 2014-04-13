/***********************************************************************************
 * Abdullah Bukhamsin                                                              *
 * April 8, 2014                                                                   *
 * Programming Assignment 6                                                        *
 * Description: This Program implements a battleship game according to some rules. *
 *				The player plays against a computer. once the game is done. Stats  *
 *				of the game is outputted to a log file.                            *
 ***********************************************************************************/

#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <stdio.h>   // for printf (), scanf () and fprintf ()
#include <stdlib.h>  // for rand () and srand ()
#include <time.h>    // for time

// List of function prototypes
// Description of the functions can be found before each function definition in battleship.c

void print_game_rules (void);
void select_who_starts_first (int *random);
void init_game_board (char board[10][10], int num_rows, int num_cols);
void print_board (char board[10][10], int num_rows, int num_cols);
int is_invalid_start_pt (char board [10][10], int row, int col, int dir, int length);
void randomly_place_ships (char board [10][10], char symbol, int length, int direction,
						   int row, int col);
void manually_place_ships (char board [10][10], char symbol);
void random_shot (char board [10][10], int row_rand, int col_rand, FILE *infile,
				  int *hits, int *misses);
void target_shot (char board [10][10], int row_rand, int col_rand, FILE *infile,
				  int *hits, int *misses);
void update_board (char board [10][10], char updated_board [10][10], 
				   int num_rows, int num_cols);
int check_if_sunk_ship (char board [10][10]);

#endif
