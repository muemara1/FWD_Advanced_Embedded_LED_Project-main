#include "stdint.h"
//*****************************************************************************
//
// INCLUDES
//
//*****************************************************************************
#include "stdint.h"
#include "LED_Private.h"
#include "LED_Config.h"
#include "../Libraries/Bit_Math.h"
#include "../MCAL/inc/GPIO_Interface.h"
#include "../MCAL/inc/TIMER0_Interface.h"
#include "../MCAL/inc/NVIC_Interface.h"
#include "../MCAL/inc/SysTick_Interface.h"
#include "../HAL/LED/LED_Interface.h"

//*****************************************************************************
//
// DRIVER IMPLEMENTATIONS
//
//*****************************************************************************
/************************************************************************************
* Function Name: LED_Init
* Sync/Async: Synchronous
* Reentrancy: Non-reentrant
* Parameters (in): LED - LED to be initilaized
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initialize a LED 
************************************************************************************/
void LED_Init(LED_ControlType LED_Controls,void (*LED_Toggle) (void) ,LED_TimerType	LED_Timer)
{
	if(LED_Timer==LED_Timer0A)
	{
		/* Use Timer0A */
		Timer0_ConfigType Timer;
		Timer.Mode=Timer0_Periodic;
		Timer.Preload=64000;
		Timer.Prescaler=249;
		Timer.Config=Timer0_16Bit;
		TIMER0_O_P_Init(Timer);
		NVIC_Int_CfgType Timer_Interrupt;
		Timer_Interrupt.GroupScheme=NVIC_G_xxx;
		Timer_Interrupt.GroupPriority=NVIC_Priority_0;
		Timer_Interrupt.INT_Number=NVIC_TIMER0A_16_32;
		NVIC_Init(Timer_Interrupt);
		NVIC_EnableINT(Timer_Interrupt);
		TIMER0_Callback(LED_Toggle);
	}
	else
	{
		/* Use SysTick */
		SysTick_Init(16000000);
		SysTick_Callback(LED_Toggle);
	}
	/* Pin Config */
	Port_ConfigType Pins[3];
	Pins[0].PinNum=LED_Controls.LED_Pin;
	Pins[0].PinMode=PIN_GPIO;
	Pins[0].PinDir=OUTPUT;
	Pins[0].PinLevelValue=LOW;
	/* SW1 Config */
	Pins[1].PinNum=LED_Controls.LED_SW1;
	Pins[1].PinMode=PIN_GPIO;
	Pins[1].PinDir=INPUT;
	Pins[1].PinLevelValue=LOW;
	/* SW2 Config */
	Pins[2].PinNum=LED_Controls.LED_SW2;
	Pins[2].PinMode=PIN_GPIO;
	Pins[2].PinDir=INPUT;
	Pins[2].PinLevelValue=LOW;
	Port_Init(Pins);
	
	NVIC_Int_CfgType LED_SW_INT;
	LED_SW_INT.GroupScheme=NVIC_G_xxx;
	LED_SW_INT.GroupPriority=NVIC_Priority_1;
	LED_SW_INT.INT_Number=NVIC_GPIOF;
	NVIC_Init(LED_SW_INT);
	NVIC_EnableINT(LED_SW_INT);
	GPIOF0_Callback(LED_IncreaseOFF);
	GPIOF4_Callback(LED_IncreaseON);
}
/************************************************************************************
* Function Name: LED_Blink
* Sync/Async: Synchronous
* Reentrancy: Non-reentrant
* Parameters (in): On-Time- Required ON time
									 Off-Time - Required OFF time
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Configure LED for blinking
************************************************************************************/
void LED_Blink(uint16_t On_Time, uint16_t Off_Time,LED_TimerType	LED_Timer)
{
	TotalCount= On_Time+Off_Time;
	Counter=0;
	Global_ONTime=On_Time;
	Global_OFFTime=Off_Time;
	if(LED_Timer==LED_Timer0A)
	{
		Timer0_Start();
	}
	else if(LED_Timer==LED_SysTick)
	{
		SysTick_Enable();
	}
}

void LED_IncreaseON(void)
{
	if(Global_ONTime<=10)
	{
		Global_ONTime++;
		TotalCount= Global_ONTime+Global_OFFTime;
	}
	else 
	{
		Global_ONTime=1;
		TotalCount= Global_ONTime+Global_OFFTime;
	}
}

void LED_IncreaseOFF(void)
{
	if(Global_OFFTime<=10)
	{
		Global_OFFTime++;
		TotalCount= Global_ONTime+Global_OFFTime;
	}
	else 
	{
		Global_OFFTime=1;
		TotalCount= Global_ONTime+Global_OFFTime;
	}
}

void LED_Toggle(void)
{
	if(Counter<Global_ONTime)
	{
		DIO_WriteChannel(PF2,HIGH);
	}
	else if (Counter>TotalCount)
	{
		Counter=0;
	}else if(Counter>Global_ONTime)
	{
		DIO_WriteChannel(PF2,LOW);
	}
	Counter++;
}

