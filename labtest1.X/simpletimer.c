/*
 * File:   simpletimer.c
 * Author: shara
 *
 * Created on 16 March, 2021, 6:58 PM
 */


// FOSCSEL
#pragma config FNOSC = FRC            // Oscillator Source Selection (Internal Fast RC (FRC))
#pragma config IESO = OFF               // Two-speed Oscillator Start-up Enable bit (Start up device with FRC, then switch to user-selected oscillator source)

// FOSC
#pragma config POSCMD = HS             // Primary Oscillator Mode Select bits (HS Crystal Oscillator Mode)
#pragma config OSCIOFNC = OFF           // OSC2 Pin Function bit (OSC2 is clock output)
#pragma config FCKSM = CSDCMD           // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor are disabled)
#pragma config PLLKEN = ON              // PLL Lock Status Control (PLL lock signal will be used to disable PLL clock output if lock is lost)
#pragma config XTCFG = G3               // XT Config (24-32 MHz crystals)
#pragma config XTBST = ENABLE           // XT Boost (Boost the kick-start)

#define FCY 8000000UL
#include <libpic30.h>
#include "xc.h"
int main(void) {
    TRISDbits.TRISD10 = 0;   //set AN2 as output pin

    while(1)
    {
        __delay_ms(1000);
        LATDbits.LATD10 = 0; //write AN2 output as 0   
        __delay_ms(1000);  
        LATDbits.LATD10 = 1; //write AN2 output as 1   
        
    }
    return 0;
}
