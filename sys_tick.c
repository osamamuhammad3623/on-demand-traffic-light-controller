#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "sys_tick.h"
#include "common_macros.h"

static void volatile (*g_CallBackPtr)(void) = 0;

void SysTick_init(uint32_t value, void volatile (* callBackFunction )()){
	CLEAR_BIT(NVIC_ST_CTRL_R, 0); /* disable the timer */
	NVIC_ST_RELOAD_R = value-1; /* set compare value */
	NVIC_ST_CURRENT_R = 0; /* clear current ticks */
	SET_BIT(NVIC_ST_CTRL_R, 2);  /* set clock source to System Clock */
	SET_BIT(NVIC_ST_CTRL_R, 1);  /* enable sys tick interrupt */
	SET_BIT(NVIC_EN0_R, 15); /* enable NVIC interrupts for SysTick timer */
	g_CallBackPtr = callBackFunction; /* set the call-back function */
}

void SysTick_start(void){
	SET_BIT(NVIC_ST_CTRL_R, 0); /* enable timer [start counting] */
}

void SysTick_stop(void){
	CLEAR_BIT(NVIC_ST_CTRL_R, 0); /* disable sys tick timer */
}

void SysTick_Handler(void){
	if (g_CallBackPtr != 0){
		(*g_CallBackPtr)();
		NVIC_ST_CURRENT_R = 0; // clear the count flag
	}
}