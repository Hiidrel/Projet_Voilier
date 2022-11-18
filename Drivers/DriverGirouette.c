#include "DriverGirouette.h"
#include "MyGPIO.h"
#include "MyTimer.h"

MyGPIO_Struct_TypeDef GPIO_A6={GPIOA, 6, In_Floating}; //A
MyGPIO_Struct_TypeDef GPIO_A7={GPIOA, 7, In_Floating}; //B
MyGPIO_Struct_TypeDef GPIO_B2={GPIOB, 2, In_Floating}; //I
MyTimer_Struct_TypeDef TIMER3={TIM3, 1440, 0};



void Init_Incrementation(void)
{
	RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4);
	MyGPIO_Init(&GPIO_A6);
	MyGPIO_Init(&GPIO_A7);
	MyGPIO_Init(&GPIO_B2);
	MyTimer_Base_Init(&TIMER3);
	//init Timer en encodeur sur 2 channels
	TIM3->SMCR &= ~(0x7<<0);
	TIM3->SMCR |= (0x3<<0);
	while (MyGPIO_Read(GPIOB, 2)==0)
	{	
		TIM3->CNT =0;
	}
}

int angleGirouette(void)
{
	return ((TIM3->CNT)/4);
}
