#include <msp430g2553.h>
#include "game.h"
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
