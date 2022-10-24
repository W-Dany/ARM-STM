#include "led.h"


//��ʼ��PB1Ϊ���.��ʹ��ʱ��	    
//LED IO��ʼ��
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOH_CLK_ENABLE();           //����GPIOBʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12; //PH10,11,12
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);
	
    HAL_GPIO_WritePin(GPIOH,GPIO_PIN_10,GPIO_PIN_SET);	//PH10��1��Ĭ�ϳ�ʼ�������
    HAL_GPIO_WritePin(GPIOH,GPIO_PIN_11,GPIO_PIN_SET);	//PH11��1��Ĭ�ϳ�ʼ�������
		HAL_GPIO_WritePin(GPIOH,GPIO_PIN_12,GPIO_PIN_SET);	//PH12��1��Ĭ�ϳ�ʼ�������
}
