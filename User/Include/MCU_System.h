/*!
\file MCU_System.h
\brief Header for a MCU_System module
\author Daniel Leonov
\date 01.08.2013
*/

#ifndef __MCU_SYSTEM_H
#define __MCU_SYSTEM_H

#include "stm32f10x.h"	
#include "MCU_Common.h"

#define TIME_CPU_CLK 64000000UL

void SYS_Delay(__IO uint32_t nTime); 
void SYS_InitRcc(void);


#endif // __MCU_SYSTEM_H
