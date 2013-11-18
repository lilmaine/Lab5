#include <msp430g2553.h>
#include "game.h"
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

