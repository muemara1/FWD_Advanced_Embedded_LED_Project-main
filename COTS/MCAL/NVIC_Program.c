#include "stdint.h"
//*****************************************************************************
//
// INCLUDES
//
//*****************************************************************************
#include "stdint.h"
#include "../inc/NVIC_Private.h"
#include "../inc/NVIC_Config.h"
#include "../Libraries/MCU_HW.h"
#include "../Libraries/Bit_Math.h"

//*****************************************************************************
//
// DRIVER IMPLEMENTATIONS
//
//*****************************************************************************
/************************************************************************************
* Function Name: NVIC_SetGrouping
* Sync/Async: Synchronous
* Reentrancy: Non-reentrant
* Parameters (in): Group - Group Priority control type
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Set priority grouping for interrupts priority
************************************************************************************/
void NVIC_Init(NVIC_Int_CfgType NVIC_IntConfig)
{
	/* Initialize some needed variables */
	volatile uint32_t *Pri_Reg;
	uint8_t Pri_Bit_Offset;
	uint8_t Priority;
	/* Insert key in vectkey field and Set group priority scheme */
	*NVIC_APINT_R|=(uint32_t)0x05FA0000|(NVIC_IntConfig.GroupScheme<<8);
	/* Get interrupt priority register */
  Pri_Reg=NVIC_PRI_Regs[NVIC_IntConfig.INT_Number/4];
	/* Get interrupt priority bit offset */
	Pri_Bit_Offset=PRI_BIT_Offsets[NVIC_IntConfig.INT_Number%4];
	/* Determine interrupt priorities */
	if (NVIC_IntConfig.GroupScheme==NVIC_G_xxx)
	{
		Priority = NVIC_IntConfig.GroupPriority;
	}else if (NVIC_IntConfig.GroupScheme==NVIC_G_xxy)
	{
		Priority = NVIC_IntConfig.GroupPriority<<1;
		Priority |= NVIC_IntConfig.SubGroupPriority;
	}else if (NVIC_IntConfig.GroupScheme==NVIC_G_xyy)
	{	
		Priority = NVIC_IntConfig.GroupPriority<<2;
		Priority |= NVIC_IntConfig.SubGroupPriority;
	} else if (NVIC_IntConfig.GroupScheme==NVIC_G_yyy)
	{
		Priority = NVIC_IntConfig.SubGroupPriority;
	}
	/* Set interrupt priority */
	*Pri_Reg|=(Priority<<Pri_Bit_Offset);
}

void NVIC_EnableINT(NVIC_Int_CfgType NVIC_IntConfig)
{
	volatile uint32_t *EN_Reg;
	uint8_t EN_Bit_Offset;
	/* Get interrupt enable register */
	EN_Reg=NVIC_EN_Regs[NVIC_IntConfig.INT_Number/32];
	/* Get interrupt enable register bit offset */
	EN_Bit_Offset=NVIC_IntConfig.INT_Number%32;
	/* Enable interrupt */ 
	Set_Bit(EN_Reg,EN_Bit_Offset);
}

void NVIC_DisableINT(NVIC_Int_CfgType NVIC_IntConfig)
{
	volatile uint32_t *DIS_Reg;
	uint8_t DIS_Bit_Offset;
	/* Get interrupt enable register */
	DIS_Reg=NVIC_DIS_Regs[NVIC_IntConfig.INT_Number/32];
	/* Get interrupt enable register bit offset */
	DIS_Bit_Offset=NVIC_IntConfig.INT_Number%32;
	/* Enable interrupt */ 
	Set_Bit(DIS_Reg,DIS_Bit_Offset);
}
