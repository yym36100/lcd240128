#include "frt.h"

void frt_start(void) {
	frt_timer.Instance->CNT = 0;
	__HAL_TIM_ENABLE(&frt_timer);
}

uint16_t frt_stop(void) {
	__HAL_TIM_DISABLE(&frt_timer);
	return frt_timer.Instance->CNT;
}

/*
 timer clock 108MHz 9.25ns not clear what timer clock is
 7077>>16 = 1/9.25

 */

void frt_wait_nops(uint32_t delay){
	 for(uint32_t i=0;i<delay;i++){
		 __asm("nop");
	 }
}

void frt_wait_ns2(uint16_t delay) {
	 LD1_GPIO_Port->BSRR = LD1_Pin;
	frt_timer.Instance->CNT = 0;
	__HAL_TIM_ENABLE(&frt_timer);

	while (frt_timer.Instance->CNT < delay) ;
	LD1_GPIO_Port->BSRR = LD1_Pin<<16;
	__HAL_TIM_DISABLE(&frt_timer);

}

void frt_wait_ns(uint16_t delay) {
	if(delay>150)delay-=150; else delay=0;
	uint16_t t = frt_timer_val(delay);
	 asm volatile ("": :"r"(t) : "memory"); // "local var barrier" Memory barrier calc t beforehand
	 LD1_GPIO_Port->BSRR = LD1_Pin;
	frt_timer.Instance->CNT = 0;
	__HAL_TIM_ENABLE(&frt_timer);

	while (frt_timer.Instance->CNT < t) ;
	LD1_GPIO_Port->BSRR = LD1_Pin<<16;
	__HAL_TIM_DISABLE(&frt_timer);

}
