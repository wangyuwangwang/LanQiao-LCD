#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "main.h"
#include "stdbool.h"
struct keys
{
	uchar judge_sta;//���е���һ��
	bool key_sta;//ʶ�𰴼��Ƿ񱻰���
	bool single_flag;//�ٴ�ȷ�ϰ�������
	bool long_flag;
	uint key_time;
};

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif