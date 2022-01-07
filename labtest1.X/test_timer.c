/*
 * File:   test.c
 * Author: shara
 *
 * Created on 17 March, 2021, 12:04 PM
 */


#include "xc.h"


int value = 1;

#pragma config ICS = 2

void __attribute__((__interrupt__,no_auto_psv)) _T1Interrupt(void)
{  
    if(IFS0bits.T1IF == 1)
    {
        value=~value;   // complement the value for blinking the LEDs
        IFS0bits.T1IF = 0;       // Clear timer interrupt flag
    } 
}


int main(void)
{  
    TRISDbits.TRISD10 = 0;   //set AN2 as output pin    
    //T1CON = 0x0; // Stop timer and clear control register,
    T1CON = 0x0; // disable timer AND 
    T1CONbits.TCKPS = 0b11; //set prescaler at 1:256
    T1CONbits.TECS = 0b11; //select FRC
    T1CONbits.TCS = 1; //SELECT CLOCK IN TECS
    TMR1 = 0x0; // Clear timer register
    PR1 = 0x3D09; // Load period register
    //TMR1=0x0BDC;     // Load the time value(0xBDC) for 100ms delay
    //IFS0bits.T1IF = 1;
    //T1IE=1;       //Enable timer interrupt bit in PIE1 register
    INTCON2bits.GIE=1;
    //GIE=1;          //Enable Global Interrupt
    /* Enable Timer1 interrupt */
    IEC0bits.T1IE = 1;
    //IPC0bits.T1IP = 2;
    //PEIE=1;         //Enable the Peripheral Interrupt
    //PEIEbits.TMR1IE = 1;
    //IEC0bits.T1IE = 0
    //TMR1ON = 1;     //Start Timer1  
    T1CONbits.TON = 1; // Start 

    while(1)
    {
        LATDbits.LATD10 = value; //write b14 output as 1   
    }
}

