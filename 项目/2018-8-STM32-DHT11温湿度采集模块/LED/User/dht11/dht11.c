#include "dht11.h"
static uint8_t HTdata[5] = {0,0,0,0,0};
/**
*name:DHT11_delay_us(uint16_t us)
*fun :实现较为精确的us延时
*para:us：us数
*ret :void
**/
void DHT11_delay_us(uint16_t us)
{
	for(int i = 0;i<us;i++)
	{
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	}	
}
/**
*name:DHT11_delay_ms(uint16_t ms)
*fun :实现较为精确的ms延时
*para:ms：ms数
*ret :void
**/
void  DHT11_delay_ms(uint16_t ms)
{
	for(int i = 0;i<ms;i++)
	{
		DHT11_delay_us(1000);
	}

}
/**
*name:DHT11_GPIO_Mode_Out()
*fun :GPIO推挽输出模式
*para:void
*ret :void
**/
void DHT11_GPIO_Mode_Out()
{	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	DATA_CLKCMD(DATA_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = DATA_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DATA_PORT,&GPIO_InitStruct);
}
/**
*name:DHT11_GPIO_Mode_IN()
*fun :GPIO推输入模式
*para:void
*ret :void
**/
void DHT11_GPIO_Mode_IN()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	DATA_CLKCMD(DATA_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = DATA_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DATA_PORT,&GPIO_InitStruct);
}
/**
*name:DHT11_Read_Bit(void)
*fun :读取位
*para:void
*ret :位值
**/
uint8_t DHT11_Read_Bit()
{
    while (DATA == RESET);
    DHT11_delay_us(40);
    if (DATA == SET)
    {
        while (DATA == SET);
        return 1;
    }
    else
    {
        return 0;
    }
}
/**
*name:DHT11_Init()
*fun :DHT11初始化
*para:void
*ret :void
**/
void DHT11_Init()
{
	DHT11_GPIO_Mode_Out();
	DATAH;
	DHT11_delay_ms(1000);
}
/**
*name:DHT11_Read_Data()
*fun :DHT11读取数据，如果读出来的值一直为0，说明错误
*para:void
*ret :校验正确返回1，否则为0
**/
uint8_t DHT11_Read_Data()
{
	DHT11_GPIO_Mode_Out();
	DATAL;
	DHT11_delay_ms(18);
	DATAH;
	DHT11_delay_us(30);
	DHT11_GPIO_Mode_IN();
	if(DATA == Bit_RESET)
	{
		while(DATA == Bit_RESET);
		while(DATA == Bit_SET);
		for(int i = 0;i<5;i++)
		{
			for(int j = 0;j<8;j++)
			{
				HTdata[i] <<= 1;
				HTdata[i] |= DHT11_Read_Bit();
			}
		}
		while(DATA == Bit_RESET);
		DHT11_GPIO_Mode_Out();
		DATAH;
	}	
	if(HTdata[0]+HTdata[1]+HTdata[2]+HTdata[3] == HTdata[4])
	{
		return 1;
	}
	else 
	{
		HTdata[0] = 0;
		HTdata[1] = 0;
		HTdata[2] = 0;
		HTdata[3] = 0;
	}
	return 0;
}
/**
*name:DHT11_Read_Humidity()
*fun :返回湿度值
*para:void
*ret :校验正确返回1，否则为0
**/
float DHT11_Read_Humidity()
{
	float temp = HTdata[1]; //小数部分
	uint8_t i =0;
	while(HTdata[1] !=0)
	{
		HTdata[1]/=10;
		i++;
	}
	temp /= pow(10,i);
	return	HTdata[0]+temp;
}
float DHT11_Read_Temper()
{
	float temp = HTdata[3]; //小数部分
	uint8_t i =0;
	while(HTdata[3] !=0)
	{
		HTdata[3]/=10;
		i++;
	}
	temp /= pow(10,i);
	return	HTdata[2]+temp;
}


