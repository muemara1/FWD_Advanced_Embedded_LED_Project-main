#ifndef SYSTICK_INTERFACE_H
#define SYSTICK_INTERFACE_H
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
void SysTick_Callback(void (*ptrF) (void));
void SysTick_Init(uint32_t LoadValue);
void SysTick_Enable(void);
void SysTick_Disable(void);
#endif /*SYSTICK_INTERFACE_H */
