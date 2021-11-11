#include <msp430.h> 


/**
 * main.c
 */

void signal_SOS(void){
    P1OUT ^= BIT1;
    __delay_cycles(16000000);
    P1OUT ^= BIT1;
    __delay_cycles(16000000);
    P1OUT ^= BIT1;
    __delay_cycles(16000000);
    P1OUT ^= BIT1;
    __delay_cycles(16000000);
    P1OUT ^= BIT1;
    __delay_cycles(16000000);
    P1OUT ^= BIT1;
    __delay_cycles(16000000);

    P1OUT ^= BIT1;
    __delay_cycles(32000000);
    P1OUT ^= BIT1;
    __delay_cycles(16000000);
    P1OUT ^= BIT1;
    __delay_cycles(32000000);
    P1OUT ^= BIT1;
    __delay_cycles(16000000);
    P1OUT ^= BIT1;
    __delay_cycles(32000000);
    P1OUT ^= BIT1;

    __delay_cycles(16000000);
    P1OUT ^= BIT1;
    __delay_cycles(16000000);
    P1OUT ^= BIT1;
    __delay_cycles(16000000);
    P1OUT ^= BIT1;
    __delay_cycles(16000000);
    P1OUT ^= BIT1;
    __delay_cycles(16000000);
    P1OUT ^= BIT1;
    __delay_cycles(16000000);
}

void initLCD(void){
    // initialize LCD Display
}

void displayScrollText(char* str){
    // display text
}

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    signal_SOS();
    initLCD();

    P2IFG &= ~(BIT3 | BIT7);

    unsigned int select = 0;

    __enable_interrupt();

    while(1){
        P1OUT ^= BIT1;
        __delay_cycles(16000000);
        if(select % 2 == 0){
            while(1){
                displayScrollText("< NAMETAG >");
                // Both buttons pressed = SELECT
                if (!(P2IN & BIT3) && !(P2IN & BIT7)){
                    P2IES |= (BIT3 | BIT7);
                    P2IFG &= ~(BIT3 | BIT7);
                    //exec_nametag();
                    break;
                } else if(P2IFG & BIT3){    // Left button pressed
                    P2IFG &= ~BIT3;
                    if (P2IN & BIT3){       // Left button released
                        P2IES |= BIT3;
                        select--;
                        break;
                    } else
                        P2IES &= ~BIT3;
                } else if(P2IFG & BIT7) {   // Right button pressed
                    P2IFG &= ~BIT7;
                    if(P2IN & BIT7){        // Right button released
                        P2IES |= BIT7;
                        select++;
                        break;
                    } else
                        P2IES &= ~BIT7;
                }
            }
        } else {
            while(1){
                displayScrollText("< GAME >");
                // Both buttons pressed = SELECT
                if (!(P2IN & BIT3) && !(P2IN & BIT7)){
                    P2IES |= (BIT3 | BIT7);
                    P2IFG &= ~(BIT3 | BIT7);
                    //exec_game();
                    break;
                } else if(P2IFG & BIT3){    // Left button pressed
                    P2IFG &= ~BIT3;
                    if (P2IN & BIT3){       // Left button released
                        P2IES |= BIT3;
                        select--;
                        break;
                    } else
                        P2IES &= ~BIT3;
                } else if(P2IFG & BIT7) {   // Right button pressed
                    P2IFG &= ~BIT7;
                    if(P2IN & BIT7){        // Right button released
                        P2IES |= BIT7;
                        select++;
                        break;
                    } else
                        P2IES &= ~BIT7;
                }
            }
        }
    }
}
