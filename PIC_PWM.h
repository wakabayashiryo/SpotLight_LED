/* 
 * File:   PWM.h
 * Author: evaota
 *
 * Created on 2017/08/25, 12:18
 */

#ifndef PIC_PWM_H
#define	PIC_PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "main.h"
typedef enum
{
    TMR2_PRESCALER1 = 0,
    TMR2_PRESCALER4 = 1,
    TMR2_PRESCALER16 = 2,
    TMR2_PRESCALER64 = 3,
}TMR2_PRESCALER_VAL;

typedef void (*PWM_Init_PORTTypedef)(void);

void PWM_Init(PWM_Init_PORTTypedef PMW_Init_PORT,TMR2_PRESCALER_VAL pre_val,uint8_t period);
#define PWM_Start()    CCP1CON |=  (3<<2);     //CCP module is PWM mode and start 
#define PWM_Stop()     CCP1CON &= ~(3<<2);     //CCP module is PWM mode and stop
void PWM_SetDuty(uint16_t duty);

#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

