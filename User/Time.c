#include "Time.h"

void TIME_Delay_ms(__IO uint32_t nTime){
	/*!
	\brief Задержка.
	\param nTime Длительность задержки в мс.
	*/	
	 
	uint32_t nTicks=(TIME_CPU_CLK/4000)*nTime;
	for(; nTicks != 0; nTicks--);
} 
