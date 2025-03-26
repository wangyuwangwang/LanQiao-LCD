#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "main.h"
#include "stdbool.h"
struct keys
{
	uchar judge_sta;//进行到哪一步
	bool key_sta;//识别按键是否被按下
	bool single_flag;//再次确认按键按下
	bool long_flag;
	uint key_time;
};

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif