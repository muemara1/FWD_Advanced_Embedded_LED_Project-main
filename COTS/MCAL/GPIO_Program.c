#include "stdint.h"
//*****************************************************************************
//
// INCLUDES
//
//*****************************************************************************
#include "stdint.h"
#include "../inc/GPIO_Private.h"
#include "../inc/GPIO_Config.h"
#include "../Libraries/MCU_HW.h"
#include "../Libraries/Bit_Math.h"

//*****************************************************************************
//
// PORT DRIVER IMPLEMENTATIONS
//
//*****************************************************************************
/************************************************************************************
* Function Name: Port_Init
* Sync/Async: Synchronous
* Reentrancy: Non-reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initializes the Port Driver module
************************************************************************************/
void Port_Init(const Port_ConfigType* ConfigPtr)
{
	/* Variable to iterate through ConfigPtr instances */
	uint8_t Pin_Idx;
	/* Pointer to store base address */
	volatile uint32_t* Base_Address_Pointer;
	/* Looping through pins configs */
	for(Pin_Idx=0;Pin_Idx<GPIO_Ports_Pin_Number;Pin_Idx++)
	{
		/*Get Port and Pin Numbers*/
		uint8_t Current_Port=ConfigPtr[Pin_Idx].PinNum / 10;;
		uint8_t Current_Pin=ConfigPtr[Pin_Idx].PinNum % 10;
		/*Base Address check*/
		switch(Current_Port)
		{
			case  0: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
				 break; 
			case  1: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
				 break;
			case  2: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
				 break;
			case  3: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
				 break;
			case  4: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
				 break;
			case  5: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
				 break;
		}
		
		/* GPIO Clock Run Mode */
		Set_Bit(SYSCTL_RCGCGPIO_REG,Current_Port);
		/* Wait for peripheral ready flag */
		//while(!Get_Bit(SYSCTL_PRGPIO_REG,Current_Port));
		uint32_t delay = 123456;
		/* Unlocking Commit Register */
		if(ConfigPtr[Pin_Idx].PinNum==PC7||ConfigPtr[Pin_Idx].PinNum == PF0) 	/* If PD7 or PF0,then unlocking is required */
		{
			/* Insert Lock Key */
			*((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_LOCK_REG_OFFSET))=LOCK_KEY_MASK;
			/* Set commit bit for pin */
			Set_Bit(((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_COMMIT_REG_OFFSET)),Current_Pin);
		}else if(ConfigPtr[Pin_Idx].PinNum==PC0||ConfigPtr[Pin_Idx].PinNum==PC1||ConfigPtr[Pin_Idx].PinNum==PC2||ConfigPtr[Pin_Idx].PinNum==PC3)
		{
			/* Skip Pins PC0 to PC3, JTAG pins */
			continue;
		}
		
		
		/* Direction and attach type */
		if(ConfigPtr[Pin_Idx].PinDir==OUTPUT)
		{
			Set_Bit((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_DIR_REG_OFFSET),Current_Pin);
			/* Pin Initial Value */
			if(ConfigPtr[Pin_Idx].PinLevelValue==HIGH)
			{
				/* Set HIGH Initial value for pin */
				Set_Bit((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_DATA_REG_OFFSET),Current_Pin);
			}
			else
			{
				/* Set LOW Initial value for pin */
				Clear_Bit((volatile uint32_t*)( Base_Address_Pointer+PORT_DATA_REG_OFFSET),Current_Pin);
			}
		}
		else if(ConfigPtr[Pin_Idx].PinDir==INPUT)
		{
			/* Set INPUT state for current pin */
			Clear_Bit((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_DIR_REG_OFFSET),Current_Pin);
			/* Check Pin Attach Type:  Pullup or Pulldown */
			if(ConfigPtr[Pin_Idx].PinAttachType==PULLUP)
			{
				/* Set pull up bit in pull up register */
				Set_Bit((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_PULL_UP_REG_OFFSET),Current_Pin);
			}
			else if(ConfigPtr[Pin_Idx].PinAttachType==PULLDOWN)
			{
				/* Set pull down bit in pull down register */
				Set_Bit((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_PULL_DOWN_REG_OFFSET),Current_Pin);				
			}
			else
			{
				/* Clear Pull Up and Pull Down registers */
				Clear_Bit((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_PULL_UP_REG_OFFSET),Current_Pin);
				Clear_Bit((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_PULL_DOWN_REG_OFFSET),Current_Pin);
			}
		}	
		
		/* Mode Select */
		if(ConfigPtr[Pin_Idx].PinMode==PIN_GPIO)
		{
			/* Clear Analoge mode select register bit */
			Clear_Bit((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_ANALOG_MODE_SEL_REG_OFFSET),Current_Pin);
			/* Clear alternate function register bit */
			Clear_Bit((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_ALT_FUNC_REG_OFFSET),Current_Pin);
			/* Clear control select register bits */
			*(volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_CTL_REG_OFFSET)&=~(CTRL_REG_CLEAR_MASK <<(ConfigPtr[Pin_Idx].PinNum*4));
			/* Set digital enable bit for current pin*/
			Set_Bit((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_DIGITAL_ENABLE_REG_OFFSET),Current_Pin);
		}
		else if(ConfigPtr[Pin_Idx].PinMode==PIN_ANALOG)
		{
			/* Set Analoge mode select register bit */
			Set_Bit((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_ANALOG_MODE_SEL_REG_OFFSET),Current_Pin);
			/* Clear alternate function register bit */
			Clear_Bit((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_ALT_FUNC_REG_OFFSET),Current_Pin);
			/* Clear control select register bits */
			*(volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_CTL_REG_OFFSET)&=~(CTRL_REG_CLEAR_MASK <<(ConfigPtr[Pin_Idx].PinNum*4));
			/* Clear digital enable bit for current pin*/
			Clear_Bit((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_DIGITAL_ENABLE_REG_OFFSET),Current_Pin);
		}
		else
		{
			/* Clear Analoge mode select register bit */
			Clear_Bit((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_ANALOG_MODE_SEL_REG_OFFSET),Current_Pin);
			/* Clear alternate function register bit */
			Set_Bit((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_ALT_FUNC_REG_OFFSET),Current_Pin);
			/* Set control register bits */
			*(volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_CTL_REG_OFFSET)&=~(ConfigPtr[Pin_Idx].PinMode <<(ConfigPtr[Pin_Idx].PinNum*4));
			/* Set digital enable bit for current pin*/
			Set_Bit((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_DIGITAL_ENABLE_REG_OFFSET),Current_Pin);
		}
		
		
		/* Check and set current level */
		if(ConfigPtr[Pin_Idx].PinCurrent == Current_2_mA)
		{
			Set_Bit((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_DR2_REG_OFFSET),Current_Pin);
			Clear_Bit((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_DR4_REG_OFFSET),Current_Pin);
			Clear_Bit((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_DR8_REG_OFFSET),Current_Pin);
		}
		else if(ConfigPtr[Pin_Idx].PinCurrent == Current_4_mA)
		{
			Clear_Bit((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_DR2_REG_OFFSET),Current_Pin);
			Set_Bit((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_DR4_REG_OFFSET),Current_Pin);
			Clear_Bit((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_DR8_REG_OFFSET),Current_Pin);
		}
		else if(ConfigPtr[Pin_Idx].PinCurrent == Current_8_mA)
		{
			Clear_Bit((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_DR2_REG_OFFSET),Current_Pin);
			Clear_Bit((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_DR4_REG_OFFSET),Current_Pin);
			Set_Bit((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_DR8_REG_OFFSET),Current_Pin);
		}		
		if(ConfigPtr[Pin_Idx].IntEN==INT_Enable)
		{
			 Clear_Bit((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_GPIOM_OFFSET),Current_Pin);
			 Clear_Bit((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_GPIOIS_OFFSET),Current_Pin);
			 Clear_Bit((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_GPIOIBE_OFFSET),Current_Pin);
			 Set_Bit((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_GPIOM_OFFSET),Current_Pin);
		}
	}		
}

/************************************************************************************
* Function Name: DIO_ReadPort
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Port_ID - ID of Port.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to read a port value.
************************************************************************************/
DIO_PortLevelType DIO_ReadPort(DIO_PortType Port_ID)
{
		/*Pointer to store base address */
		volatile uint32_t * Base_Address_Pointer;
		/*Base Address check*/
		switch(Port_ID)
		{
			case  0: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
				 break; 
			case  1: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
				 break;
			case  2: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
				 break;
			case  3: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
				 break;
			case  4: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
				 break;
			case  5: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
				 break;
		}
		/* Read Port value */
		DIO_PortLevelType Return_Value=*(volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_DATA_REG_OFFSET);
		/* Return Read port value */
		return Return_Value;
}
/************************************************************************************
* Function Name: DIO_WritePort
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Port_ID - ID of Port.
									 Level   - Level of Port.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set a port value.
************************************************************************************/
void DIO_WritePort(DIO_PortType Port_ID,DIO_PortLevelType Level)
{
		/*Pointer to store base address */
		volatile uint32_t * Base_Address_Pointer;
		/*Base Address check*/
		switch(Port_ID)
		{
			case  0: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
				 break; 
			case  1: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
				 break;
			case  2: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
				 break;
			case  3: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
				 break;
			case  4: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
				 break;
			case  5: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
				 break;
		}
		/* Write Port value */
		*(volatile uint32_t*)( (volatile uint8_t*) Base_Address_Pointer+PORT_DATA_REG_OFFSET)=Level;
}

//*****************************************************************************
//
// DIO DRIVER IMPLEMENTATION
//
//*****************************************************************************
/************************************************************************************
* Function Name: DIO_ReadChannel
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Channel_ID - ID of DIO channel.
* Parameters (inout): None
* Parameters (out): None
* Return value: DIO_LevelType
* Description: Function to return the value of the specified DIO channel.
************************************************************************************/
DIO_LevelType DIO_ReadChannel(DIO_ChannelType Channel_ID)
{
		/*Pointer to store base address */
		volatile uint32_t * Base_Address_Pointer;
		/*Get Port and Pin Numbers*/
		uint8_t Current_Port=Channel_ID / 10;;
		uint8_t Current_Pin=Channel_ID % 10;
		/*Base Address check*/
		switch(Current_Port)
		{
			case  0: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
				 break; 
			case  1: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
				 break;
			case  2: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
				 break;
			case  3: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
				 break;
			case  4: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
				 break;
			case  5: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
				 break;
		}
		/* Get bit value */
		uint8_t Return_Value = Get_Bit((volatile uint32_t*)( (volatile uint8_t*) Base_Address_Pointer+PORT_DATA_REG_OFFSET),Current_Pin);
		/* Return read value */
		return Return_Value;
}
/************************************************************************************
* Function Name: DIO_WriteChannel
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Channel_ID - ID of DIO channel.
*                  Level - Value to be written.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set a level of a channel.
************************************************************************************/
void DIO_WriteChannel(DIO_ChannelType Channel_ID,DIO_LevelType Level)
{
		/*Pointer to store base address */
		volatile uint32_t * Base_Address_Pointer;
		/*Get Port and Pin Numbers*/
		uint8_t Current_Port=Channel_ID / 10;;
		uint8_t Current_Pin=Channel_ID % 10;
		/*Base Address check*/
		switch(Current_Port)
		{
			case  0: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
				 break; 
			case  1: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
				 break;
			case  2: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
				 break;
			case  3: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
				 break;
			case  4: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
				 break;
			case  5: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
				 break;
		}
		if(Level == HIGH)
		{
			/* Set bit in Data register */ 
			Set_Bit((volatile uint32_t*)( (volatile uint8_t*) Base_Address_Pointer+PORT_DATA_REG_OFFSET),Current_Pin);
		}else if (Level == LOW)
		{
			/* Clear bit in Data register */ 
			Clear_Bit((volatile uint32_t*)( (volatile uint8_t*) Base_Address_Pointer+PORT_DATA_REG_OFFSET),Current_Pin);
		}
}
/************************************************************************************
* Function Name: DIO_FlipChannel
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Channel_ID - ID of DIO channel.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to flip a level of a channel.
************************************************************************************/
void DIO_FlipChannel(DIO_ChannelType Channel_ID)
{
			/*Pointer to store base address */
		volatile uint32_t * Base_Address_Pointer;
		/*Get Port and Pin Numbers*/
		uint8_t Current_Port=Channel_ID / 10;;
		uint8_t Current_Pin=Channel_ID % 10;
		/*Base Address check*/
		switch(Current_Port)
		{
			case  0: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
				 break; 
			case  1: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
				 break;
			case  2: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
				 break;
			case  3: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
				 break;
			case  4: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
				 break;
			case  5: Base_Address_Pointer = (volatile uint32_t *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
				 break;
		}
		/* Toggle bit value */
		Toggle_Bit((volatile uint32_t*)((volatile uint8_t*)Base_Address_Pointer+PORT_DATA_REG_OFFSET),Current_Pin);
}

	
void GPIOF0_Callback(void (*ptrF) (void))
{
	ptrFCallback_PF0 = ptrF;
}

void GPIOF4_Callback(void (*ptrF) (void))
{
	ptrFCallback_PF4 = ptrF;
}

/*External Interrupt handler*/
void GPIOF_Handler()
{
	if(Get_Bit((volatile uint32_t*)((volatile uint8_t*)GPIO_PORTF_BASE_ADDRESS+PORT_GPIOMIS_OFFSET),0))
	{
		if (ptrFCallback_PF0 != NULL)
		{
			ptrFCallback_PF0();
		}
		Set_Bit((volatile uint32_t*)((volatile uint8_t*)GPIO_PORTF_BASE_ADDRESS+PORT_GPIOICR_OFFSET),0);

	}
	else if (Get_Bit((volatile uint32_t*)((volatile uint8_t*)GPIO_PORTF_BASE_ADDRESS+PORT_GPIOMIS_OFFSET),4))
	{
		if (ptrFCallback_PF4 != NULL)
		{
			ptrFCallback_PF4();
		}
	  Set_Bit((volatile uint32_t*)((volatile uint8_t*)GPIO_PORTF_BASE_ADDRESS+PORT_GPIOICR_OFFSET),4);
	}
}
