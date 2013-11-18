/*
 * game.h
 * Author: Tramaine Barnett
 *
<<<<<<< HEAD
 *This lab uses the MSP430 microcontroller and a lcd display
 *to create a simple game in which one
 *must navigate past mines and make it to the finish line
 * The shell code for this lab was given my Capt BranchFlower
 * Documentation: I looked at Capt Branchflowers work as well as other students when I was stuck at some of the more difficult stages.
 *
=======
 * This is shell code for the game to be implemented in Lab 4.  It provides basic functions that may prove useful in accomplishing the lab.
>>>>>>> e3262666c19562af235dbd5fc2b3e3fefff43b96
 */


#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define ROW_MASK 0x40

#define NUM_MINES 2

//
// Initializes player to starting position on board.
//
unsigned char initPlayer();

//
// Prints the player marker (*) at the player location passed in.
//
void printPlayer(unsigned char player);

//
// Clears the location passed in.
//
void clearPlayer(unsigned char player);

//
// Given a player's current position and a direction, returns an updated player position.
//
<<<<<<< HEAD
char movePlayer(char location, int mod);
=======
unsigned char movePlayer(unsigned char player, unsigned char direction);
>>>>>>> e3262666c19562af235dbd5fc2b3e3fefff43b96

//
// Returns true if the position passed in is the winning game position.
//
char didPlayerWin(unsigned char player);

<<<<<<< HEAD
void generateMines(unsigned char mines[NUM_MINES]);

=======
>>>>>>> e3262666c19562af235dbd5fc2b3e3fefff43b96
/*
 * Functions which may prove useful in achieving A-Functionality.
 *
char didPlayerHitMine(unsigned char player, unsigned char mines[NUM_MINES]);
<<<<<<< HEAD

=======
void generateMines(unsigned char mines[NUM_MINES]);
>>>>>>> e3262666c19562af235dbd5fc2b3e3fefff43b96
void printMines(unsigned char mines[NUM_MINES]);
*/
