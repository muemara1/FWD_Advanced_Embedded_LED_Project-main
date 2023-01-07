#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H
//*****************************************************************************
//
// INCLUDES
//
//*****************************************************************************
#include "stdint.h"
#include "LED_Private.h"
#include "LED_Config.h"
#include "../MCAL/inc/GPIO_Interface.h"

//*****************************************************************************
//
// DRIVER PROTOTYPES
//
//*****************************************************************************

void LED_Init(LED_ControlType LED_Controls,void (*LED_Toggle) (void) ,LED_TimerType	LED_Timer);
void LED_Blink(uint16_t On_Time, uint16_t Off_Time,LED_TimerType	LED_Timer);
void LED_IncreaseON(void);
void LED_IncreaseOFF(void);
void LED_Toggle(void);

#endif /*LED_INTERFACE_H */
