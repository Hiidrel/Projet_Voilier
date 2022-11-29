#include "plateau.h"



	void plateau_Init(MyTimer_Struct_TypeDef * Timer, MyGPIO_Struct_TypeDef * GPIOPWM, MyGPIO_Struct_TypeDef * GPIOSens, MyGPIO_Struct_TypeDef * GPIORcv, USART_TypeDef * USART, void (*IT_function ) ( void )){

	
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	MyTimer_Base_Init(Timer);
	MyGPIO_Init(GPIOPWM);
	MyGPIO_Init(GPIOSens);
	MyGPIO_Init(GPIORcv);
	UART_Init(USART,9600);
	MyTimer_PWM(Timer->Timer,3);
	MyTimer_Base_Start(Timer);
		
	}

		