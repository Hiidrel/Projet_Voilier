#include "DriverVoiles.h"
#include "MyGPIO.h"
#include "MyTimer.h"
#include "DriverGirouette.h"
#include "plateau.h"
#include "voiles.h"
#include "Roulis.h"
#include "MySPI.h"


//declarer timer 
MyTimer_Struct_TypeDef Timer		= {TIM2, 9999, 143};
MyGPIO_Struct_TypeDef GPIOPWM		= {GPIOA, 1, AltOut_Ppull};// PWM : TIM 3 , PB0 ,channel 3
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
		set_pulse_pwm_CH2(Timer.Timer, floatValue);
	}else{
		MyGPIO_Set(GPIOSens.GPIO, GPIOSens.GPIO_Pin);
		set_pulse_pwm_CH2(Timer.Timer, floatValue*(-1));
	}
}

int main ( void ){
	RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4);
	init_Incrementation();
	initGPIOTimerPWM();
	plateau_Init(&Timer, &GPIOPWM, &GPIOSens, &GPIORcv, USART, updateRapport);
	//initRoulis();
	
	while (1) {
		updateRapport();
		controleVoiles();
	}

}



