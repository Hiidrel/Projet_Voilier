
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

/*#include "plateau.h"


	//declarer timer 
MyTimer_Struct_TypeDef Timer4		= {TIM4, 9999, 143};
MyGPIO_Struct_TypeDef GPIOPWM		= {GPIOB, 6, AltOut_Ppull};// PWM : TIM 2 , PA1 ,channel 2
MyGPIO_Struct_TypeDef GPIOSens	= {GPIOB, 5, Out_Ppull};// PB5
MyGPIO_Struct_TypeDef GPIORcv		= {GPIOA,10,In_Floating};// RX : PA10 
USART_TypeDef * USART						= USART1;


signed char value;
float floatValue; //value sous forme float


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
	
	
void updateRapport() {
	value = UART_Receive(USART);
	//floatValue = (float) value;
	//floatValue = 10;
	
	
	if (floatValue >= 0) {
			MyGPIO_Reset(GPIOSens.GPIO, GPIOSens.GPIO_Pin);
		set_pulse_pwm_CH1(Timer4.Timer, floatValue);
	}else{
		MyGPIO_Set(GPIOSens.GPIO, GPIOSens.GPIO_Pin);
		set_pulse_pwm_CH1(Timer4.Timer, floatValue*(-1));
	}
}
*/