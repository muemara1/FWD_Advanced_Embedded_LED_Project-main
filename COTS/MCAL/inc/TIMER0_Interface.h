#ifndef TIMER0_INTERFACE_H
#define TIMER0_INTERFACE_H
//*****************************************************************************
//
// INCLUDES
//
//*****************************************************************************
#include "stdint.h"
#include "TIMER0_Private.h"

//*****************************************************************************
//
// DRIVER PROTOTYPES
//
//*****************************************************************************

void TIMER0_Callback(void (*ptrF) (void));
void TIMER0_O_P_Init(Timer0_ConfigType TimerConfig);
void Timer0_Start(void);

#endif /*TIMER0_INTERFACE_H */
