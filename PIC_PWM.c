#include "PIC_PWM.h"

void PWM_Init(PWM_Init_PORTTypedef PMW_Init_PORT,TMR2_PRESCALER_VAL pre_val,uint8_t period)
{
    PMW_Init_PORT();
    
    PR2 = period;                   //Set Period Register
    TMR2 = 0x00;                    //Clear 
    T2CON |= ((uint8_t)pre_val<<0); //Set Clock Prescaler
    T2CON |= (0x00<<3);             //Post Scaler is 1
    T2CON |= (0x01<<2);             //Timer2 is enabled
    
    CCP1CON &= ~(3<<6);             // PWM is single output
    
    CCPR1L = 0x00;
}

void PWM_SetDuty(uint16_t duty)
{
    uint8_t RegTemp = CCP1CON&0xCF;
    
    CCPR1L = (duty&0x03FC)>>2;
    CCP1CON = RegTemp | ((duty&0x0003)<<4);
}
