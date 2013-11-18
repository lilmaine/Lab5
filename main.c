#include <msp430.h>
#include "LCD.h"
#include "game.h"
#include "rand.h"
/*
 * main.c
 */




void init_timer()
{
        TACTL &= ~(MC1|MC0);        // stop timer

        TACTL |= TACLR;             // clear TAR

        TACTL |= TASSEL1;           // configure for SMCLK - what's the frequency (roughly)?

        TACTL |= ID1|ID0;           // divide clock by 8 - what's the frequency of interrupt?

        TACTL &= ~TAIFG;            // clear interrupt flag

        TACTL |= MC1;               // set count mode to continuous

        TACTL |= TAIE;              // enable interrupt

        __enable_interrupt();       // enable maskable interrupts

}

void init_buttons()
{
        configureP1PinAsButton(BIT1|BIT2|BIT3|BIT4);
        P1IE |= BIT1|BIT2|BIT3|BIT4;
        P1IES |= BIT1|BIT2|BIT3|BIT4;
}

char position = 0x80;
char flag = 0;
char increment = 0;

int main(void) {
        WDTCTL = WDTPW | WDTHOLD;        // Stop watchdog timer

        //Use seed to create a random number
        static const char seed = 1234;

        init_timer();
        init_buttons();
        __enable_interrupt();
        initSPI();
        LCDinit();
        LCDclr();
        printPlayer(position);

        char random = prand(seed);
        random = prand(random);
        char mine1 = 0x81 + random % 7;
        random = prand(random);
        char mine2 = 0xC0 + random % 7;
        char string1[] = "YOU     ";
        char string2[] = "WIN!    ";
        char string3[] = "GAME    ";
        char string4[] = "OVER!   ";
        char string5[] = "BOOM!   ";
        char string6[] = "        ";

        printMine(mine1);
        while (mine2 == mine1
                        || mine2 == (mine1 + 0x40)
                        || mine2 == (mine1 + 0x41)
                        || mine2 == (mine1 + 0x3F)) {
                random = prand(random);
                mine2 = 0xC0 + random % 7;
        }
        printMine(mine2);

        while (1) {

                if (position == 0xC7) {
                        LCDclr();
                        cursorToLineOne();
                        writeString(string1);
                        cursorToLineTwo();
                        writeString(string2);
                        flag = 5;
                        increment = 5;
                        while (flag > 4) {
                        }
                        LCDclr();
                        position = initPlayer();
                        printPlayer(position);
                        mine1 = 0x81 + random % 7;
                        printMine(mine1);
                        while (mine2 == mine1
                                        || mine2 == (mine1 + 0x40)
                                        || mine2 == (mine1 + 0x41)
                                        || mine2 == (mine1 + 0x3F)) {
                                random = prand(random);
                                mine2 = 0xC0 + random % 7;
                        }
                        printMine(mine2);
                        increment = 0;
                }

                if (position == mine1 || position == mine2) {
                        flag = 4;
                        LCDclr();
                        cursorToLineOne();
                        writeString(string5);
                        cursorToLineTwo();
                        writeString(string6);
                        __delay_cycles(444444);
                        LCDclr();
                }
                if (increment == 4) {
                        clearPlayer(mine1);
                        clearPlayer(mine2);
                        mine1--;
                        mine2++;
                        printMine(mine1);
                        printMine(mine2);
                        increment = 0;
                }

                if (flag == 4) {
                        LCDclr();
                        cursorToLineOne();
                        writeString(string3);
                        cursorToLineTwo();
                        writeString(string4);
                        flag = 5;
                        increment = 5;

                        while (flag > 4) {
                        }
                        LCDclr();
                        position = initPlayer();
                        printPlayer(position);
                        flag = 0;
                        increment = 0;
                        mine1 = 0x81 + random % 7;
                        printMine(mine1);
                        while (mine2 == mine1
                                        || mine2 == (mine1 + 0x40)
                                        || mine2 == (mine1 + 0x41)
                                        || mine2 == (mine1 + 0x3F)) {
                                random = prand(random);
                                mine2 = 0xC0 + random % 7;
                        }
                        printMine(mine2);
                }
        }

}


#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR() {
        TACTL &= ~TAIFG;
        flag++;
        increment++;
}

void clearTimer() {
        flag = 0;
}


void testAndRespondToButtonPush(char buttonToTest) {
        if (buttonToTest & P1IFG) {

                if (buttonToTest & P1IES) {

                        if (flag == 5) {
                                LCDclr();
                                position = initPlayer();
                                printPlayer(position);
                                flag = 0;
                        }

                        else {
                                int mod = 0;
                                mod = movePlayerInResponseToButtonPush(buttonToTest);
                                clearPlayer(position);
                                position += mod;
                                position = movePlayer(position, mod);
                                clearTimer();
                        }

                } else {
                        debounce();
                }

                P1IES ^= buttonToTest;
                P1IFG &= ~buttonToTest;
        }

}


#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR() {
        testAndRespondToButtonPush(BIT1);
        testAndRespondToButtonPush(BIT2);
        testAndRespondToButtonPush(BIT3);
        testAndRespondToButtonPush(BIT4);

}
