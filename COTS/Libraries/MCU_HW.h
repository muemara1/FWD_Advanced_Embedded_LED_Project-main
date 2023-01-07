#ifndef MCU_HW_H
#define MCU_HW_H
//*****************************************************************************
//
// INCLUDES
//
//*****************************************************************************
#include "stdint.h"



//*****************************************************************************
//
// Timer0 Registers
//
//*****************************************************************************
#define GPTM_CFG_REG       (volatile uint32_t *)0x40030000
#define GPTM_CTL_REG       (volatile uint32_t *)0x4003000C
#define GPTM_TAMR_REG      (volatile uint32_t *)0x40030004
#define GPTM_TAILR_REG     (volatile uint32_t *)0x4003001C
#define GPTM_IMR_REG       (volatile uint32_t *)0x40030018
#define GPTM_ICR_REG       (volatile uint32_t *)0x40030024
#define GPTM_RIS_REG       (volatile uint32_t *)0x4003001C
#define GPTM_TAPR_REG      (volatile uint32_t *)0x40030038
#define GPTM_RCGCTIMER_REG (volatile uint32_t *)0x400FE604

/* Registers */
typedef union
{
	volatile uint32_t Register;
	struct GPTMCTL_REG
	{
		volatile uint32_t TAEN   :1;
		volatile uint32_t TASTALL:1;
		volatile uint32_t TAEVENT:2;
		volatile uint32_t RTCEN  :1;
		volatile uint32_t TAOTE  :1;
		volatile uint32_t TAPWML :1;
	} BitField;
}GPTMCTL_Union;

typedef union
{
	volatile uint32_t Register;
	struct GPTMCFG_REG
	{
		volatile uint32_t CFG:2;
	} BitField;
}GPTMCFG_Union;

typedef union
{
	volatile uint32_t Register;
	struct GPTMTAMR_REG
	{
		volatile uint32_t TAMR   :2;
		volatile uint32_t TACMR  :1;
		volatile uint32_t TAAMS  :1;
		volatile uint32_t TACDIR :1;
		volatile uint32_t TAMIE  :1;
		volatile uint32_t TAWOT  :1;
		volatile uint32_t TASNAPS:1;
		volatile uint32_t TAILD  :1;
		volatile uint32_t TAPWMIE:1;
		volatile uint32_t TAMRSU :1;
		volatile uint32_t TAPLO  :1;
	} BitField;
}GPTMTAMR_Union;

typedef union
{
	volatile uint32_t Register;
	struct GPTMIMR_REG
	{
		volatile uint32_t TATOIM:1;
		volatile uint32_t CAMIM :1;
		volatile uint32_t CAEIM :1;
		volatile uint32_t RTCIM :1;
		volatile uint32_t TAMIM :1;
		volatile uint32_t       :3;
		volatile uint32_t TBTOIM:1;
		volatile uint32_t CBMIM :1;
		volatile uint32_t CBEIM :1;
		volatile uint32_t TBMIM :1;
		volatile uint32_t       :4;
		volatile uint32_t WUEIM :1;
	} BitField;
}GPTMIMR_Union;

typedef union
{
	volatile uint32_t Register;
	struct GPTMRIS_REG
	{
		volatile uint32_t TATORIS :1;
		volatile uint32_t CAMRIS  :1;
		volatile uint32_t CAERIS  :1;
		volatile uint32_t RTCRIS  :1;
		volatile uint32_t TAMRIS  :1;
		volatile uint32_t         :3;
		volatile uint32_t TBTORIS :1;
		volatile uint32_t CBMRIS  :1;
		volatile uint32_t CBERIS  :1;
		volatile uint32_t TBMRIS  :1;
 		volatile uint32_t         :4;
 		volatile uint32_t WUERIS  :1;
	} BitField;
}GPTMRIS_Union;

typedef union
{
	volatile uint32_t Register;
	struct GPTMICR_REG
	{
		volatile uint32_t TATOCINT :1;
		volatile uint32_t CAMCINT  :1;
		volatile uint32_t CAECINT  :1;
		volatile uint32_t RTCCINT  :1;
		volatile uint32_t TAMCINT  :1;
		volatile uint32_t          :3;
		volatile uint32_t TBTOCINT :1;
		volatile uint32_t CBMCINT  :1;
		volatile uint32_t CBECINT  :1;
		volatile uint32_t TBMCINT  :1;
 		volatile uint32_t          :4;
 		volatile uint32_t WUECINT  :1;
	} BitField;
}GPTMICR_Union;

typedef union
{
	volatile uint32_t Register;
	struct GPTMCLOCK_REG
	{
		volatile uint32_t R0  :1;
		volatile uint32_t R1  :1;
		volatile uint32_t R2  :1;
		volatile uint32_t R3  :1;
		volatile uint32_t R4  :1;
		volatile uint32_t R5  :1;
	} BitField;
}GPTMCLOCK_Union;
//*****************************************************************************
//
// NVIC and SYS Registers
//
//*****************************************************************************
#define SYSCTL_RCGCGPIO_REG     (volatile uint32_t *)0x400FE608
#define SYSCTL_PRGPIO_REG       (volatile uint32_t *)0x400FEA08
#define SYSTICK_CTRL_R          (volatile uint32_t *)0xE000E010
#define SYSTICK_RELOAD_R        (volatile uint32_t *)0xE000E014
#define SYSTICK_CURRENT_R       (volatile uint32_t *)0xE000E018
#define NVIC_ACTLR_R            (volatile uint32_t *)0xE000E008
#define NVIC_EN0_R              (volatile uint32_t *)0xE000E100
#define NVIC_EN1_R              (volatile uint32_t *)0xE000E104
#define NVIC_EN2_R              (volatile uint32_t *)0xE000E108
#define NVIC_EN3_R              (volatile uint32_t *)0xE000E10C
#define NVIC_EN4_R              (volatile uint32_t *)0xE000E110
#define NVIC_DIS0_R             (volatile uint32_t *)0xE000E180
#define NVIC_DIS1_R             (volatile uint32_t *)0xE000E184
#define NVIC_DIS2_R             (volatile uint32_t *)0xE000E188
#define NVIC_DIS3_R             (volatile uint32_t *)0xE000E18C
#define NVIC_DIS4_R             (volatile uint32_t *)0xE000E190
#define NVIC_APINT_R            (volatile uint32_t *)0xE000ED0C

#define NVIC_PEND0_R            (volatile uint32_t *)0xE000E200
#define NVIC_PEND1_R            (volatile uint32_t *)0xE000E204
#define NVIC_PEND2_R            (volatile uint32_t *)0xE000E208
#define NVIC_PEND3_R            (volatile uint32_t *)0xE000E20C
#define NVIC_PEND4_R            (volatile uint32_t *)0xE000E210
#define NVIC_UNPEND0_R          (volatile uint32_t *)0xE000E280
#define NVIC_UNPEND1_R          (volatile uint32_t *)0xE000E284
#define NVIC_UNPEND2_R          (volatile uint32_t *)0xE000E288
#define NVIC_UNPEND3_R          (volatile uint32_t *)0xE000E28C
#define NVIC_UNPEND4_R          (volatile uint32_t *)0xE000E290
#define NVIC_ACTIVE0_R          (volatile uint32_t *)0xE000E300
#define NVIC_ACTIVE1_R          (volatile uint32_t *)0xE000E304
#define NVIC_ACTIVE2_R          (volatile uint32_t *)0xE000E308
#define NVIC_ACTIVE3_R          (volatile uint32_t *)0xE000E30C
#define NVIC_ACTIVE4_R          (volatile uint32_t *)0xE000E310
#define NVIC_PRI0_R             (volatile uint32_t *)0xE000E400
#define NVIC_PRI1_R             (volatile uint32_t *)0xE000E404
#define NVIC_PRI2_R             (volatile uint32_t *)0xE000E408
#define NVIC_PRI3_R             (volatile uint32_t *)0xE000E40C
#define NVIC_PRI4_R             (volatile uint32_t *)0xE000E410
#define NVIC_PRI5_R             (volatile uint32_t *)0xE000E414
#define NVIC_PRI6_R             (volatile uint32_t *)0xE000E418
#define NVIC_PRI7_R             (volatile uint32_t *)0xE000E41C
#define NVIC_PRI8_R             (volatile uint32_t *)0xE000E420
#define NVIC_PRI9_R             (volatile uint32_t *)0xE000E424
#define NVIC_PRI10_R            (volatile uint32_t *)0xE000E428
#define NVIC_PRI11_R            (volatile uint32_t *)0xE000E42C
#define NVIC_PRI12_R            (volatile uint32_t *)0xE000E430
#define NVIC_PRI13_R            (volatile uint32_t *)0xE000E434
#define NVIC_PRI14_R            (volatile uint32_t *)0xE000E438
#define NVIC_PRI15_R            (volatile uint32_t *)0xE000E43C
#define NVIC_PRI16_R            (volatile uint32_t *)0xE000E440
#define NVIC_PRI17_R            (volatile uint32_t *)0xE000E444
#define NVIC_PRI18_R            (volatile uint32_t *)0xE000E448
#define NVIC_PRI19_R            (volatile uint32_t *)0xE000E44C
#define NVIC_PRI20_R            (volatile uint32_t *)0xE000E450
#define NVIC_PRI21_R            (volatile uint32_t *)0xE000E454
#define NVIC_PRI22_R            (volatile uint32_t *)0xE000E458
#define NVIC_PRI23_R            (volatile uint32_t *)0xE000E45C
#define NVIC_PRI24_R            (volatile uint32_t *)0xE000E460
#define NVIC_PRI25_R            (volatile uint32_t *)0xE000E464
#define NVIC_PRI26_R            (volatile uint32_t *)0xE000E468
#define NVIC_PRI27_R            (volatile uint32_t *)0xE000E46C
#define NVIC_PRI28_R            (volatile uint32_t *)0xE000E470
#define NVIC_PRI29_R            (volatile uint32_t *)0xE000E474
#define NVIC_PRI30_R            (volatile uint32_t *)0xE000E478
#define NVIC_PRI31_R            (volatile uint32_t *)0xE000E47C
#define NVIC_PRI32_R            (volatile uint32_t *)0xE000E480
#define NVIC_PRI33_R            (volatile uint32_t *)0xE000E484
#define NVIC_PRI34_R            (volatile uint32_t *)0xE000E488
#define NVIC_CPUID_R            (volatile uint32_t *)0xE000ED00
#define NVIC_INT_CTRL_R         (volatile uint32_t *)0xE000ED04
#define NVIC_VTABLE_R           (volatile uint32_t *)0xE000ED08
#define NVIC_SYS_CTRL_R         (volatile uint32_t *)0xE000ED10
#define NVIC_CFG_CTRL_R         (volatile uint32_t *)0xE000ED14
#define NVIC_SYS_PRI1_R         (volatile uint32_t *)0xE000ED18
#define NVIC_SYS_PRI2_R         (volatile uint32_t *)0xE000ED1C
#define NVIC_SYS_PRI3_R         (volatile uint32_t *)0xE000ED20
#define NVIC_SYS_HND_CTRL_R     (volatile uint32_t *)0xE000ED24
#define NVIC_FAULT_STAT_R       (volatile uint32_t *)0xE000ED28
#define NVIC_HFAULT_STAT_R      (volatile uint32_t *)0xE000ED2C
#define NVIC_DEBUG_STAT_R       (volatile uint32_t *)0xE000ED30
#define NVIC_MM_ADDR_R          (volatile uint32_t *)0xE000ED34
#define NVIC_FAULT_ADDR_R       (volatile uint32_t *)0xE000ED38
#define NVIC_CPAC_R             (volatile uint32_t *)0xE000ED88
#define NVIC_MPU_TYPE_R         (volatile uint32_t *)0xE000ED90
#define NVIC_MPU_CTRL_R         (volatile uint32_t *)0xE000ED94
#define NVIC_MPU_NUMBER_R       (volatile uint32_t *)0xE000ED98
#define NVIC_MPU_BASE_R         (volatile uint32_t *)0xE000ED9C
#define NVIC_MPU_ATTR_R         (volatile uint32_t *)0xE000EDA0
#define NVIC_MPU_BASE1_R        (volatile uint32_t *)0xE000EDA4
#define NVIC_MPU_ATTR1_R        (volatile uint32_t *)0xE000EDA8
#define NVIC_MPU_BASE2_R        (volatile uint32_t *)0xE000EDAC
#define NVIC_MPU_ATTR2_R        (volatile uint32_t *)0xE000EDB0
#define NVIC_MPU_BASE3_R        (volatile uint32_t *)0xE000EDB4
#define NVIC_MPU_ATTR3_R        (volatile uint32_t *)0xE000EDB8
#define NVIC_DBG_CTRL_R         (volatile uint32_t *)0xE000EDF0
#define NVIC_DBG_XFER_R         (volatile uint32_t *)0xE000EDF4
#define NVIC_DBG_DATA_R         (volatile uint32_t *)0xE000EDF8
#define NVIC_DBG_INT_R          (volatile uint32_t *)0xE000EDFC
#define NVIC_SW_TRIG_R          (volatile uint32_t *)0xE000EF00
#define NVIC_FPCC_R             (volatile uint32_t *)0xE000EF34
#define NVIC_FPCA_R             (volatile uint32_t *)0xE000EF38
#define NVIC_FPDSC_R            (volatile uint32_t *)0xE000EF3C


//*****************************************************************************
//
// GPIO registers 
//
//*****************************************************************************
/* GPIO Registers base addresses */
#define GPIO_PORTA_BASE_ADDRESS           0x40004000
#define GPIO_PORTB_BASE_ADDRESS           0x40005000
#define GPIO_PORTC_BASE_ADDRESS           0x40006000
#define GPIO_PORTD_BASE_ADDRESS           0x40007000
#define GPIO_PORTE_BASE_ADDRESS           0x40024000
#define GPIO_PORTF_BASE_ADDRESS           0x40025000

/* GPIO Registers offset addresses */
#define PORT_DATA_REG_OFFSET              0x3FC
#define PORT_DIR_REG_OFFSET               0x400
#define PORT_ALT_FUNC_REG_OFFSET          0x420
#define PORT_PULL_UP_REG_OFFSET           0x510
#define PORT_PULL_DOWN_REG_OFFSET         0x514
#define PORT_DIGITAL_ENABLE_REG_OFFSET    0x51C
#define PORT_LOCK_REG_OFFSET              0x520
#define PORT_COMMIT_REG_OFFSET            0x524
#define PORT_ANALOG_MODE_SEL_REG_OFFSET   0x528
#define PORT_CTL_REG_OFFSET               0x52C

#define PORT_DR2_REG_OFFSET               0x500
#define PORT_DR4_REG_OFFSET               0x504
#define PORT_DR8_REG_OFFSET               0x508
#define PORT_GPIOIS_OFFSET                0x404
#define PORT_GPIOM_OFFSET                 0x410
#define PORT_OPEN_DRAIN_OFFSET       			0x50C
#define PORT_GPIOIBE_OFFSET               0x408
#define PORT_GPIOMIS_OFFSET               0x418
#define PORT_GPIOICR_OFFSET               0x41C
#endif /*MCU_HW.H*/
