#include "stdint.h"
//*****************************************************************************
//
// INCLUDES
//
//*****************************************************************************
#include "stdint.h"
#include "../Libraries/Bit_Math.h"
#include "../inc/SYSTICK_Interface.h"

//*****************************************************************************
//
// DRIVER IMPLEMENTATIONS
//
//*****************************************************************************

/************************************************************************************
* Function Name: SYSTICK_Init
* Sync/Async: Synchronous
* Reentrancy: Non-reentrant
* Parameters (in): TimerConfig - Timer Configurations
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initialize SysTick with given prescaler and preload values
************************************************************************************/
void SysTick_Init(uint32_t LoadValue)
{
	*SYSTICK_RELOAD_R|=LoadValue;
	*SYSTICK_CURRENT_R=0x00000000;
	*SYSTICK_CTRL_R|=(uint32_t)6;
}

void SysTick_Enable(void)
{
	*SYSTICK_CTRL_R|=(uint32_t)7;
}

void SysTick_Disable(void)
{
	*SYSTICK_CTRL_R|=(uint32_t)6;
}
	
void SysTick_Callback(void (*ptrF) (void))
{
	ptrFCallback = ptrF;
}

void SysTick_Handler(void)
{
	if (ptrFCallback != NULL)
	{
		ptrFCallback();
	}
}
