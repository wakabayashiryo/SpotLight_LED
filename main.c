/*
 * File:   main.c
 * Author: evaota
 *
 * Created on 2017/08/25, 11:48
 */

#include "main.h"

void Basic_Init(void);

void UART_Init_Port(void);
void PWM_Init_Port(void);
void mTouch_Init_Port(void);

void main(void)
{
    Basic_Init();
    
    Timer0_Init(TMR0_PRESCALER64,125);//set interrupt time is 1ms

    PWM_Init(PWM_Init_Port,TMR2_PRESCALER4,0xFF);
    PWM_Start();
    
    CPS_CHANNELCONFIG cps_conf[1];
    cps_conf[0].CPS_Channel = 0;
    cps_conf[0].Threshould_Diff = 1000;     
    mTouch_Init(mTouch_Init_Port,cps_conf,1);
    
    UART_Init(UART_Init_Port,BAUD_9600);
    
    while(1)
    {
//        mTouch_Display_Config();
        if(mTouch_Check(0))
            LATA5 = 1;;
    }
//        for(uint16_t i=0;i<0x03FF;i++)
//        {
//            PWM_SetDuty(i);
//            __delay_ms(10);
//        }
//    }
}

void Basic_Init(void)
{
    OSCCON = 0xF0;      //PLL ON: 
                        //internal Oscilltor is 32MHz
                        //clock source is internal one.
    
    TRISA = 0x00;       //All PORTA is output 
    ANSELA = 0x00;      //All PORTA  is digital
    WPUA = 0x00;        
    
    /*alternate pin fuction control*/
    APFCON = 0x00;     //no alteration
    
    PORTA = 0x00;       //clear
    
}

void interrupt Handler(void)
{
    static uint16_t Interval = 0;
    
    if(Timer0_CheckFlag())
    {
        mTouch_Count1ms();   

        if(++Interval>30)//Scanning Timer1 ever 30ms
        {
            Interval = 0;
            mTouch_Scan();
        }
    }
    UART_Interrupt();
}


void UART_Init_Port(void)
{
    TRISA &= ~(1<<4);
    ANSELA &= ~(1<<4);
    APFCON |= (1<<2);   //TX of UART assingn to RA4
}

void PWM_Init_Port(void)
{
    TRISA &= ~(1<<2);       //PWM out port is RA2
    APFCON &= ~(1<<0); 
    ANSELA &= ~(1<<2);
}

void mTouch_Init_Port(void)
{
    TRISA |= (1<<0);        //RA0 is used as Channel0 of CPS.
    ANSELA |= (1<<0);
}
