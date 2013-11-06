#include <msp430.h>
#include "game.h"
#include "lcd.h"
#include "button.h"
//#include "lcd.c"

void init_timer();
void init_buttons();

int TIMER = 0; //tracks if game is in progress or lost
int LOSE = 0;
int GAMEOVER = 0;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;        // Stop watchdog timer

    initSPI();

    LCDinit();

    LCDclr();
    unsigned char position = 0x80;
    unsigned char player = initPlayer();
    int checkButton = 0;

    init_timer();
    init_buttons();
    __enable_interrupt();
           printPlayer(player);




    while(1)
    {
    	printPlayer(position);
    					checkButton = buttonPoll();

    	                if (position == 0xC7) {
    	                		LCDclr();
    	                		cursorToLineOne();
    	                		writeString("you");
    	                		cursorToLineTwo();
    	                		writeString("win");
    	                        checkButton = buttonPoll();
    	                        position = initPlayer();

    	                } else {
    	                		position = movePlayer(position, checkButton);
    	                        printPlayer(position);
    	                        __delay_cycles(0x44444);
    	                }

    }



    return 0;
}











#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR()
{
    TACTL &= ~TAIFG;            // clear interrupt flag
    TIMER += 1;
    if (TIMER == 4){
            LOSE = 1;
    }
}

void init_timer()
{
         TACTL &= ~(MC1|MC0);
         TACTL |= TACLR;
         TACTL |= TASSEL1;
         TACTL |= ID1|ID0;
         TACTL &= ~TAIFG;
         TACTL |= MC1;
         TACTL |= TAIE;
}

void init_buttons()
{
        configureP1PinAsButton(BIT1|BIT2|BIT3|BIT4);
}
