#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H
//*****************************************************************************
//
// INCLUDES
//
//*****************************************************************************
#include "stdint.h"
#include "NVIC_Private.h"
#include "NVIC_Config.h"


//*****************************************************************************
//
// DRIVER PROTOTYPES
//
//*****************************************************************************

void NVIC_Init(NVIC_Int_CfgType NVIC_ConfigPtr);
void NVIC_EnableINT(NVIC_Int_CfgType NVIC_IntConfig);
void NVIC_DisableINT(NVIC_Int_CfgType NVIC_IntConfig);




#endif /*NVIC_INTERFACE_H */
