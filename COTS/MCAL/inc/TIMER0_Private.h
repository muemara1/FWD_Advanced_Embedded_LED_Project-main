#ifndef TIMER0_PRIVATE_H
#define TIMER0_PRIVATE_H



//*****************************************************************************
//
// INCLUDES
//
//*****************************************************************************
#include "stdint.h"
#include "../Libraries/MCU_HW.h"

//*****************************************************************************
//
// MACROS
//
//*****************************************************************************
#define NULL (void *)0
#define GPTMCFG_CLEAR_MASK 0x00000000

//*****************************************************************************
//
// DATATYPES
//
//*****************************************************************************
static volatile  GPTMCTL_Union  *GPTMCTL   = (volatile GPTMCTL_Union*)GPTM_CTL_REG;
static volatile  GPTMCFG_Union  *GPTMCFG   = (volatile GPTMCFG_Union*)GPTM_CFG_REG;
static volatile  GPTMTAMR_Union *GPTMTAMR  = (volatile GPTMTAMR_Union*)GPTM_TAMR_REG;
static volatile  GPTMIMR_Union  *GPTMIMR   = (volatile GPTMIMR_Union*)GPTM_IMR_REG;
static volatile  GPTMRIS_Union  *GPTMRIS   = (volatile GPTMRIS_Union*)GPTM_RIS_REG;
static volatile  GPTMICR_Union  *GPTMICR   = (volatile GPTMICR_Union*)GPTM_ICR_REG;
static volatile  GPTMCLOCK_Union  *GPTMCLOCK   = (volatile GPTMCLOCK_Union*)GPTM_RCGCTIMER_REG;

static volatile  uint32_t       *GPTMTAILR = GPTM_TAILR_REG;
static volatile  uint32_t       *GPTMTAPR  = GPTM_TAPR_REG;

typedef uint32_t Timer0_DelayType;
typedef uint16_t Timer0_PrescaleType;
typedef uint16_t Timer0_PreloadType;

static void (*ptrFCallback) (void) = NULL;
#define NULL (void *)0
typedef enum 
{
	Timer0_OneShot=0x1,
	Timer0_Periodic=0x2,
	Timer0_RTC,
	Timer0_InputEdgeCount,
	Timer0_InputEdgeTime,
	Timer0_PWM,
	Timer0_WaitForTrigger,
	}Timer0_ModeType;
	
typedef enum
{
	Timer0_16Bit=0x4,
	Timer0_32Bit=0x0
}Timer0_CfgType;

typedef struct 
{
	Timer0_DelayType    Delay;
	Timer0_PrescaleType Prescaler;
	Timer0_PreloadType  Preload;
	Timer0_ModeType     Mode;
	Timer0_CfgType      Config;
}Timer0_ConfigType;


#endif /* TIMER0_PRIVATE_H */
