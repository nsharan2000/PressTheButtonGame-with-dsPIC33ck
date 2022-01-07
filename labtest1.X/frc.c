/*
 * File:   frc.c
 * Author: shara
 *
 * Created on 17 March, 2021, 1:22 PM
 */


#include <xc.h>

#pragma config FNOSC FRCDIV    // Enable FRCDIV as system clock source
                    // default RCDIV setting sets FRC @ 4 MHz providing 4 MHz sys clk (2 MIPs)

int main(void)
{
    CLKDIVbits.RCDIV = 4;        // enable divide-by-16 setting
                        // sets FRC @ 0.5 MHz providing 0.5 MHz sys clk (0.25 MIPs)
    

    while(1);
}
