#pragma once

#include <stdint.h>
#include "main.h"

extern TIM_HandleTypeDef htim11;
#define frt_timer	(htim11)


void frt_start(void);
uint16_t frt_stop(void);
//void frt_wait_ns(uint16_t delay);
void frt_wait_ns(uint16_t delay) __attribute__((optimize("O3")));
