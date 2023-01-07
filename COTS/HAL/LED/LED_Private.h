#ifndef LED_PRIVATE_H
#define LED_PRIVATE_H
//*****************************************************************************
//
// INCLUDES
//
//*****************************************************************************
#include "stdint.h"
#include "../MCAL/inc/GPIO_Interface.h"
//*****************************************************************************
//
// DATATYPES
//
//*****************************************************************************
static uint16_t Counter,
								TotalCount,
								Global_ONTime,
								Global_OFFTime;
typedef enum 
{
	LED_SysTick,
	LED_Timer0A
}LED_TimerType;

typedef struct 
{
	DIO_ChannelType LED_Pin;
	DIO_ChannelType LED_SW1;
	DIO_ChannelType LED_SW2;
}LED_ControlType;


#endif /* LED_PRIVATE_H */
