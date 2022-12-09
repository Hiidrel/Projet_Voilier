#include "DriverGirouette.h"
#include "MyGPIO.h"
#include "MyTimer.h"

MyGPIO_Struct_TypeDef GPIO_A={GPIOC, 6, In_Floating}; //A
MyGPIO_Struct_TypeDef GPIO_B={GPIOC, 7, In_Floating}; //B
MyGPIO_Struct_TypeDef GPIO_I={GPIOB, 2, In_Floating}; //I
MyTimer_Struct_TypeDef TIMER3={TIM3, 1440, 0};




void init_Incrementation(void)
{
	RCC -> APB2ENR |= RCC_APB2ENR_AFIOEN;
	AFIO->MAPR |= (0x3<<10);
	MyGPIO_Init(&GPIO_A);
	MyGPIO_Init(&GPIO_B);
	MyGPIO_Init(&GPIO_I);
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
	return ((TIM3->CNT) >> 2);
}
