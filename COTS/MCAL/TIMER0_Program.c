#include "stdint.h"
//*****************************************************************************
//
// INCLUDES
//
//*****************************************************************************
#include "stdint.h"
#include "../Libraries/Bit_Math.h"
#include "../inc/TIMER0_Interface.h"

//*****************************************************************************
//
// DRIVER IMPLEMENTATIONS
//
//*****************************************************************************

/************************************************************************************
* Function Name: TIMER0_Init
* Sync/Async: Synchronous
* Reentrancy: Non-reentrant
* Parameters (in): TimerConfig - Timer Configurations
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initialize timer 0 with given prescaler and preload values
************************************************************************************/

void TIMER0_O_P_Init(Timer0_ConfigType TimerConfig)
{
	/* Enable clock */
	GPTMCLOCK->BitField.R0=1;
	uint32_t delay=272395;
	/* Disable timer for configuration */
	GPTMCTL->BitField.TAEN=0;
	/* Set timer config */
	GPTMCFG->BitField.CFG=TimerConfig.Config;
	/* Write Mode to GPTMTAMR */ 
	if(TimerConfig.Mode==Timer0_OneShot)
	{
		GPTMTAMR->BitField.TAMR=Timer0_OneShot;
	}else if(TimerConfig.Mode==Timer0_Periodic)
	{
		GPTMTAMR->BitField.TAMR=Timer0_Periodic;
	}
	/* Load preload value */
	*GPTMTAILR=(uint32_t) TimerConfig.Preload;
	/* Set prescaler */
	*GPTMTAPR=(uint32_t) TimerConfig.Prescaler;
	/* Enable interrupt */
  GPTMIMR->BitField.TATOIM=1;
}

void Timer0_Start()
{
	GPTMCTL->BitField.TAEN=1;
}
	
void TIMER0_Callback(void (*ptrF) (void))
{
	ptrFCallback = ptrF;
}

void TIMER0A_Handler(void)
{
	if (ptrFCallback != NULL)
	{
		ptrFCallback();
	}
	GPTMICR->BitField.TATOCINT=1;
}
