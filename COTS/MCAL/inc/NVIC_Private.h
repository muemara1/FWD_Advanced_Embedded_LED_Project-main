#ifndef NVIC_PRIVATE_H
#define NVIC_PRIVATE_H
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
#define APINT_KEY_MASK  0x05FA
//*****************************************************************************
//
// DATATYPES
//
//*****************************************************************************
static uint8_t PRI_BIT_Offsets[]={5,13,21,29};

static volatile uint32_t *NVIC_EN_Regs[]={NVIC_EN0_R,
																	 NVIC_EN1_R,
																	 NVIC_EN2_R,
																	 NVIC_EN3_R,
																	 NVIC_EN4_R};

static volatile uint32_t *NVIC_DIS_Regs[]={NVIC_DIS0_R,
																 	 NVIC_DIS1_R,
															 		 NVIC_DIS2_R,
																 	 NVIC_DIS3_R,
																	 NVIC_DIS4_R};

static volatile uint32_t *NVIC_PRI_Regs[]={NVIC_PRI0_R,
                                    NVIC_PRI1_R ,
                                    NVIC_PRI2_R ,
																	  NVIC_PRI3_R ,
																	  NVIC_PRI4_R ,
																	  NVIC_PRI5_R ,
																	  NVIC_PRI6_R ,
																	  NVIC_PRI7_R ,
																	  NVIC_PRI8_R ,
																	  NVIC_PRI9_R ,
																	  NVIC_PRI10_R,
																	  NVIC_PRI11_R,
																	  NVIC_PRI12_R,
																	  NVIC_PRI13_R,
																	  NVIC_PRI14_R,
																	  NVIC_PRI15_R,
																	  NVIC_PRI16_R,
																	  NVIC_PRI17_R,
																	  NVIC_PRI18_R,
																	  NVIC_PRI19_R,
																	  NVIC_PRI20_R,
																	  NVIC_PRI21_R,
																	  NVIC_PRI22_R,
																	  NVIC_PRI23_R,
																	  NVIC_PRI24_R,
																	  NVIC_PRI25_R,
																	  NVIC_PRI26_R,
																	  NVIC_PRI27_R,
																	  NVIC_PRI28_R,
																	  NVIC_PRI29_R,
																	  NVIC_PRI30_R,
																	  NVIC_PRI31_R,
																	  NVIC_PRI32_R,
																	  NVIC_PRI33_R,
																	  NVIC_PRI34_R};

typedef enum
{
	NVIC_G_xxx=0x4,
	NVIC_G_xxy=0x5,
	NVIC_G_xyy=0x6,
	NVIC_G_yyy=0x7	
}NVIC_GroupType;

typedef enum
{
	NVIC_Priority_0,
	NVIC_Priority_1,
	NVIC_Priority_2,
	NVIC_Priority_3,
	NVIC_Priority_4,
	NVIC_Priority_5,
	NVIC_Priority_6,
	NVIC_Priority_7,
}NVIC_Priority;

typedef enum
{
	NVIC_GPIOA,
	NVIC_GPIOB,
	NVIC_GPIOC,
	NVIC_GPIOD,
	NVIC_GPIOE,
	NVIC_UART0,
	NVIC_UART1,
	NVIC_SSI0,
	NVIC_I2C0,
	NVIC_PWM0_FAULT,
	NVIC_PWM0_Generator0,
	NVIC_PWM0_Generator1,
	NVIC_PWM0_Generator2,
	NVIC_QEI0,
	NVIC_ADC0_Sequence0,
	NVIC_ADC0_Sequence1,
	NVIC_ADC0_Sequence2,
	NVIC_ADC0_Sequence3,
	NVIC_WATCHDOG_TIMERS0_1,
	NVIC_TIMER0A_16_32,
	NVIC_TIMER0B_16_32,
	NVIC_TIMER1A_16_32,
	NVIC_TIMER1B_16_32,
	NVIC_TIMER2A_16_32,
	NVIC_TIMER2B_16_32,
	NVIC_ANALOG_COMPARATOR0,
	NVIC_ANALOG_COMPARATOR1,
	NVIC_SYSTEM_CONTROL=28,
	NVIC_FLASH_MEMORY_EEPROM_CONTROL,
	NVIC_GPIOF,
	NVIC_UART2=33,
	NVIC_SSI1,
	NVIC_TIMER3A_16_32,
	NVIC_TIMER3B_16_32,
	NVIC_I2CI,
	NVIC_QEI1,
	NVIC_CAN0,
	NVIC_CAN1,
	NVIC_HIBERNATION_MODULE=43,
	NVIC_USB,
	NVIC_PWM_GENERATOR3,
	NVIC_DMA_SOFTWARE,
	NVIC_DMA_ERROR,
	NVIC_ADC1_Sequence,
	NVIC_ADC1_Sequence1,
	NVIC_ADC1_Sequence2,
	NVIC_ADC1_Sequence3,
}NVIC_InterruptType;

typedef struct NVIC_Interrupt_ConfigType
{
	NVIC_InterruptType  INT_Number;
	NVIC_GroupType      GroupScheme;
	NVIC_Priority       GroupPriority;
	NVIC_Priority       SubGroupPriority;
}NVIC_Int_CfgType;

#endif /* NVIC_PRIVATE_H */
