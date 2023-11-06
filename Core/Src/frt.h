#pragma once

#include <stdint.h>
#include "main.h"

extern TIM_HandleTypeDef htim11;
#define frt_timer	(htim11)


#define frt_timer_val(x)	(((x)*7077*2)>>16)
#define frt_wait_ns3(x) frt_wait_ns2((x)>177?frt_timer_val((x)-177):0)	// this should optimize out the mul and shift as is const

void frt_start(void);
uint16_t frt_stop(void);
//void frt_wait_ns(uint16_t delay);
void frt_wait_ns(uint16_t delay) __attribute__((optimize("O3")));
void frt_wait_ns2(uint16_t delay) __attribute__((optimize("O3")));

void frt_wait_nops(uint32_t delay) __attribute__((optimize("O3")));
