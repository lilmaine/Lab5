#include <msp430g2553.h>
#include "game.h"
<<<<<<< HEAD
#include "LCD.h"

unsigned char initPlayer() {
	return 0x80;
}

void writeCommandByte(char commandByte);
void writeDataByte(char dataByte);

void printPlayer(unsigned char player) {
	writeCommandByte(player);
	writeDataByte('*');
}

void clearPlayer(unsigned char player) {
	writeCommandByte(player);
	writeDataByte(' ');
}

void printMine(unsigned char mine) {
	writeCommandByte(mine);
	writeDataByte('X');
}

void LCDclr();

char movePlayerInResponseToButtonPush(unsigned char buttonToTest) {

	char modification = 0;
	if (buttonToTest == BIT1) {
		modification++;
	}

	else if (buttonToTest == BIT2) {
		modification--;
	}

	else if (buttonToTest == BIT3) {
		modification = modification - 0x40;
	}

	else if (buttonToTest == BIT4) {
		modification = modification + 0x40;
	}

	return modification;
}

char movePlayer(char position, int mod) {

	if (position == 0x81 || position == 0x82 || position == 0x83
			|| position == 0x84 || position == 0x85 || position == 0x86
			|| position == 0x87 || position == 0x80 || position == 0xC1
			|| position == 0xC2 || position == 0xC3 || position == 0xC4
			|| position == 0xC5 || position == 0xC6 || position == 0xC7
			|| position == 0xC0) {

		printPlayer(position);

	} else {
		position -= mod;
		printPlayer(position);
	}
	return position;
}

void generateMines(unsigned char mines[NUM_MINES]) {

}

=======
#include "lcd.h"
#include "button.h"

unsigned char initPlayer()
{
        return 0x80;
}

void printPlayer(unsigned char player)
{
        writeCommandByte(player);
        writeDataByte('*');
}

void clearPlayer(unsigned char player)
{
        writeCommandByte(player);
        writeDataByte(' ');
}

unsigned char movePlayer(unsigned char player, unsigned char direction)
{
        switch (direction) {
        case RIGHT:
                if((player != 0x87) && (player != 0xC7)){
                player += 0x01;
                }
                break;
        case LEFT:
                if(player != 0x80 && player != 0xC0){
                player -= 0x01;
                }
                break;
        case UP:
                if(player > 0x87){
                player -= 0x40;
                }
                break;
        case DOWN:
                if (player < 0xC0){
                player += 0x40;
                }
                break;
        }

        return player;
}

unsigned char updatePlayer(unsigned char buttonPressed, unsigned char position) {

        if (buttonPressed == 1) {
                clearPlayer(position);
                position = movePlayer(position, RIGHT);
                printPlayer(position);

        }

        else if (buttonPressed == 2) {
                clearPlayer(position);
                position = movePlayer(position, LEFT);
                printPlayer(position);
        }

        else if (buttonPressed == 3) {
                clearPlayer(position);
                position = movePlayer(position, UP);
                printPlayer(position);
        }

        else if (buttonPressed == 4) {
                clearPlayer(position);
                position = movePlayer(position, DOWN);
                printPlayer(position);
        }


return position;
}

int buttonPoll() {

        int buttonPressed = 0;
        while (buttonPressed == 0) {
                if ((P1IN & BIT1)== 0){
                        buttonPressed = 1;
                        return buttonPressed;
                }

                if ((P1IN & BIT2)== 0){
                        buttonPressed = 2;
                        return buttonPressed;
                }

                if ((P1IN & BIT3)== 0){
                        buttonPressed = 3;
                        return buttonPressed;
                }

                if ((P1IN & BIT4)== 0){
                                        buttonPressed = 4;
                                        return buttonPressed;
                                }
        }
        return buttonPressed;
}


char didPlayerWin(unsigned char player)
{
        return player == 0xC7;
}
>>>>>>> e3262666c19562af235dbd5fc2b3e3fefff43b96
