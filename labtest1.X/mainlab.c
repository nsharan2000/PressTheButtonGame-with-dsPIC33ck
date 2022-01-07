/*
 * File:   mainlab.c
 * Author: shara
 *
 * Created on 21 March, 2021, 12:57 AM
 */


#include "xc.h"

int count = 0;
int inc=2;

#pragma config ICS = 2

void resetled(void){
    LATDbits.LATD10 = 0;
    LATDbits.LATD11 = 0;
    LATCbits.LATC6 = 0;
    LATCbits.LATC2 = 0;
    LATCbits.LATC2 = 0;
    count=-6;
}
void __attribute__((__interrupt__,no_auto_psv)) _T1Interrupt(void)
{  
    if (count == 2)//led1==1
        {LATDbits.LATD10 = 0;//led1=0;
        LATDbits.LATD11 = 1;//led2=1
    }
    else if (count == 4)//led2==1
        {LATDbits.LATD11 = 0;//led2=0; 
        LATCbits.LATC3 = 1;//led3=1
    }
    else if (count == 6)//ledmain==1
        {LATCbits.LATC3 = 0;//ledMAIN=0; 
        LATCbits.LATC6 = 1;//led4=1
    }
    else if (count == 8)//led4==1
        {LATCbits.LATC6 = 0;//led4=0; 
        LATCbits.LATC2 = 1;//led5=1
    }
    else if (count == 10)//led5==1
        {LATCbits.LATC2 = 0;//led5=0; 
        LATDbits.LATD10 = 1;//led1=1
        count=0;
    }
    count= count+inc;
    if (count>10){
        count = 0;
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
     * READLED MAIN=RC1
    
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
    TRISCbits.TRISC8 = 1;   //LEDMAIN READ
    
    
    T1CON = 0x0; // disable timer AND clear control register
    T1CONbits.TCKPS = 0b11; //set prescaler at 1:256
    T1CONbits.TECS = 0b11; //select FRC
    T1CONbits.TCS = 1; //SELECT CLOCK IN TECS
    TMR1 = 0x0; // Clear timer register
    PR1 = 0x2F00; // Load period register
    INTCON2bits.GIE=1;//Enable Global Interrupt
    IEC0bits.T1IE = 1;   /* Enable Timer1 interrupt */  
    T1CONbits.TON = 1; // Start timer1
    
    a:
    LATCbits.LATC12 =0;//redled  =0;
    LATBbits.LATB15 =0;//greenled=0;
    //LATDbits.LATD10 = 1;//led1=1;


    while(1)
    {   
        //LEVEL DECIDE
        if(PORTBbits.RB13 == 1) //level button == 1
            {inc = 2;}//tough level
        else
            {inc = 1;}//easy level
        
        //GAME PLAY
        if (PORTCbits.RC8 == 1 && PORTCbits.RC9 == 0){    
            //ledmain==1 && pushbuttton==pressed
            LATBbits.LATB15 = 1;//GREENLED=1
            while (count<0){}
            resetled();
            goto a;//reset system for the next try for user
        }
        else if (PORTCbits.RC8 == 0 && PORTCbits.RC9 == 0){
            //ledmain==0 && pushbutton ==pressed
            LATCbits.LATC12 =1;//REDLED=1
            while (count<0){}
            resetled();
            goto a;// reset system for the next try from user

        
        }
         
             
        
    }
}


