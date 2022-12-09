#include "plateau.h"



	
	void plateau_Init(MyTimer_Struct_TypeDef * Timer, MyGPIO_Struct_TypeDef * GPIOPWM, MyGPIO_Struct_TypeDef * GPIOSens, MyGPIO_Struct_TypeDef * GPIORcv, USART_TypeDef * USART, void (*IT_function ) ( void )){

	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	MyTimer_Base_Init(Timer);
	MyGPIO_Init(GPIOPWM);
	MyGPIO_Init(GPIOSens);
	MyGPIO_Init(GPIORcv);
	UART_Init(USART,9600);
	MyTimer_PWM(Timer->Timer,2);
	MyTimer_Base_Start(Timer);
		
	}

/*
	void updateRapport() {
	value = UART_Receive(USART);
	floatValue = (float) value;
	//floatValue = 10;
	
	
	if (floatValue >= 0) {
			MyGPIO_Reset(GPIOSens.GPIO, GPIOSens.GPIO_Pin);
		set_pulse_pwm_CH2(Timer4.Timer, floatValue);
		}
	else{
		MyGPIO_Set(GPIOSens.GPIO, GPIOSens.GPIO_Pin);
		set_pulse_pwm_CH2(Timer4.Timer, floatValue*(-1));
		}
	}
*/

/*#include "plateau.h"

	void plateau_Init(void){

	
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	MyTimer_Base_Init(&Timer4);
	MyGPIO_Init(&GPIOPWM);
	MyGPIO_Init(&GPIOSens);
	MyGPIO_Init(&GPIORcv);
	UART_Init(USART,9600);
	MyTimer_PWM(TIM4,1);
	MyTimer_Base_Start(&Timer4);
		
	}




	void updateRapport(MyTimer_Struct_TypeDef * Timer, MyGPIO_Struct_TypeDef * GPIOSens, USART_TypeDef * USART, void (*IT_function ) ( void )) {
	value = UART_Receive(USART);
	floatValue = (float) value;
	//floatValue = 10;
	
	
	if (floatValue >= 0) {
			MyGPIO_Reset(GPIOSens->GPIO, GPIOSens->GPIO_Pin);
		set_pulse_pwm_CH2(Timer->Timer, floatValue);
	}else{
		MyGPIO_Set(GPIOSens->GPIO, GPIOSens->GPIO_Pin);
		set_pulse_pwm_CH2(Timer->Timer, floatValue*(-1));
	}

*/
