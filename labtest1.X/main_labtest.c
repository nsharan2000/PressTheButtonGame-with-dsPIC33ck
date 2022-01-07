/*
 * File:   main_labtest.c
 * Author: shara
 *
 * Created on 16 March, 2021, 3:50 PM
 */


#include "xc.h"
#define FCY 16000000UL
#include <libpic30.h>

int value = 1;

#pragma config ICS = 2

void __attribute__((__interrupt__,no_auto_psv)) _T1Interrupt(void)
{  
    if (PORTDbits.RD10 == 1)//led1==1
        {LATDbits.LATD10 = 0;//led1=0;
        LATDbits.LATD11 = 1;//led2=1
    }
    else if (PORTDbits.RD11 == 1)//led2==1
        {LATDbits.LATD11 = 0;//led2=0; 
        LATCbits.LATC3 = 1;//led3=1
    }
    else if (PORTCbits.RC3 == 1)//ledmain==1
        {LATCbits.LATC3 = 0;//ledMAIN=0; 
        LATCbits.LATC6 = 1;//led4=1
    }
    else if (PORTCbits.RC6 == 1)//led4==1
        {LATCbits.LATC6 = 0;//led4=0; 
        LATCbits.LATC2 = 1;//led5=1
    }
    else if (PORTCbits.RC2 == 1)//led5==1
        {LATCbits.LATC2 = 0;//led5=0; 
        LATDbits.LATD10 = 1;//led1=1
    }
    IFS0bits.T1IF = 0;       // Clear timer interrupt flag
}


int main(void)
{   
    /* PIN CONFIGURATIONS IN THE DSPIC MICROCONTROLLER
     * 
     * led1=rd10,
     * led2=rd11,
     * ledmain=rc3,
     * led4=rc6,
     * led5=rc2
     * 
     * REDLED=rc12
     * greenled=rb15
     * 
     * LEVEL READ =RB13
     * PUSH BUTTON READ =RBC9
    
    red led,greenled=output
    level  button, pushbutton=readpin[0 is easy level,1 is tough level]
     * 
      */
    TRISDbits.TRISD10 = 0;   //set AN2 as output pin led1   
    TRISDbits.TRISD11 = 0;  //led2
    TRISCbits.TRISC3 = 0;   //ledmain
    TRISCbits.TRISC6 = 0;   //led4
    TRISCbits.TRISC2 = 0;   //led5
    
    TRISCbits.TRISC12 = 0; //red led for failing the game
    TRISBbits.TRISB15 = 0; //green led for passing the game
    
    TRISBbits.TRISB13 = 1;  //level button
    TRISCbits.TRISC9 = 1;   //push button
    
    
    T1CON = 0x0; // disable timer AND clear control register
    T1CONbits.TCKPS = 0b11; //set prescaler at 1:256
    T1CONbits.TECS = 0b11; //select FRC
    T1CONbits.TCS = 1; //SELECT CLOCK IN TECS
    TMR1 = 0x0; // Clear timer register
    PR1 = 0x3D09; // Load period register
    INTCON2bits.GIE=1;//Enable Global Interrupt
    IEC0bits.T1IE = 1;   /* Enable Timer1 interrupt */  
    T1CONbits.TON = 1; // Start timer1
    
    a:
    LATCbits.LATC12 =0//redled =0;
    LATBbits.LATB14 =0//greenled =0;

    while(1)
    {   
        //LEVEL DECIDE
        if(PORTBbits.RB13 == 0) //level button == 1
            {PR1 = 0x09;}//tough level
        else
            {PR1 = 0xD09;}//easy level
        
        //GAME PLAY
        if (PORTCbits.RC3 == 1 && PORTCbits.C9 == 1){    
            //ledmain==1 && PORTBbits.RB15 == 1pushbuttton==0
            LATBbits.LATB14 =1;//GREENLED=1
            __delay_ms(1000);
            goto a;//reset system for the next try for user
        }
        else if (PORTCbits.RC3 == 0 && PORTCbits.C9 == 1){
            //ledmain==0 && pushbutton ==1
            LATCbits.LATC12 =1;//REDLED=1
            __delay_ms(1000);
            goto a;// reset system for the next try from user
            
        }
        
            
        
        
        
        
        
        
    }
}

