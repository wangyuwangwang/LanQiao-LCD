#include "interrupt.h"

struct keys key[4]={0,0,0};
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM3)//�ж����Զ�ʱ��3�Ķ�ʱ���ж�
	{
		//��ȡ����״̬
		key[0].key_sta=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0);//��ȡIO��״̬
		key[1].key_sta=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1);//��ȡIO��״̬
		key[2].key_sta=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2);//��ȡIO��״̬
		key[3].key_sta=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0);//��ȡIO��״̬
		
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
					//����
					if(key[i].key_sta==0)//�ٴ�ȷ�ϰ�������
					{
					key[i].judge_sta=2;
					
					}
					//����Bug
					else key[i].judge_sta=0;
				}
				break;
				case 2:
				{
					if(key[i].key_sta==1)//�����Ѿ��ɿ�
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