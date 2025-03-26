#include "interrupt.h"

struct keys key[4]={0,0,0};
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM3)//判断来自定时器3的定时器中断
	{
		//读取按键状态
		key[0].key_sta=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0);//读取IO口状态
		key[1].key_sta=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1);//读取IO口状态
		key[2].key_sta=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2);//读取IO口状态
		key[3].key_sta=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0);//读取IO口状态
		
		for(int i=0;i<4;i++)
		{
			switch(key[i].judge_sta)
			{
				case 0:
				{
					if(key[i].key_sta==0) 
					{
					key[i].judge_sta=1;
					key[i].key_time=0;
					}
				}
				break;
				case 1:
				{
					//消抖
					if(key[i].key_sta==0)//再次确认按键按下
					{
					key[i].judge_sta=2;
					
					}
					//消除Bug
					else key[i].judge_sta=0;
				}
				break;
				case 2:
				{
					if(key[i].key_sta==1)//按键已经松开
					{
						key[i].judge_sta=0;
						if(key[i].key_time<70) key[i].single_flag=1;
					}
					else 
					{
					key[i].key_time++;
					if(key[i].key_time>70)
					{
						key[i].long_flag=1;
					}
						
					}
				}
				break;
			}
		}
	}
}