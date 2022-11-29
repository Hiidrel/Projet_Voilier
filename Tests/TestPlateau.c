#include "plateau.h"

//declarer timer 
MyTimer_Struct_TypeDef Timer		= {TIM3, 9999, 143};
MyGPIO_Struct_TypeDef GPIOPWM		= {GPIOB, 0, AltOut_Ppull};// PWM : TIM 3 , PB0 ,channel 3
MyGPIO_Struct_TypeDef GPIOSens	= {GPIOB, 5, Out_Ppull};// PB5
MyGPIO_Struct_TypeDef GPIORcv		= {GPIOA,10,In_Floating};// RX : PA10 
USART_TypeDef * USART						= USART1;


signed char value;
float floatValue; //value sous forme float
	
void updateRapport() {
	value = UART_Receive(USART);
	floatValue = (float) value;
	//floatValue = 10;
	
	
	if (floatValue >= 0) {
			MyGPIO_Reset(GPIOSens.GPIO, GPIOSens.GPIO_Pin);
		set_pulse_pwm_CH3(Timer.Timer, floatValue);
	}else{
		MyGPIO_Set(GPIOSens.GPIO, GPIOSens.GPIO_Pin);
		set_pulse_pwm_CH3(Timer.Timer, floatValue*(-1));
	}
}

int main ( void ){
	
	plateau_Init(&Timer, &GPIOPWM, &GPIOSens, &GPIORcv, USART, updateRapport);
	
	while (1) {
		updateRapport();
	}

}