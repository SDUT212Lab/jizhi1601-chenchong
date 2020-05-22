#include "led.h"
#include "systick.h"
/**
*名称：LED驱动函数
*作者：陈冲
*时间：2018年10月
*版本：1.0
*更新：1.0：无
**/

/**
*name:void LED_Init()  
*fun :LED初始化
*para:void
*ret :void
**/
void LED_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	LED_CLKCMD(LED_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = LED_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_PORT,&GPIO_InitStruct);
}
/**
*name:void LED_Wenkle(uint32_t ms)
*fun :LED闪烁函数
*para:uint32_t ms 闪烁的频率
*ret :void
**/
void LED_Wenkle(uint32_t ms)
{
	LED_ON;
	SysTick_delay_ms(ms);
	LED_OFF;
	SysTick_delay_ms(ms);
}

