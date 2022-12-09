#include "DriverVoiles.h"
#include "MyGPIO.h"
#include "MyTimer.h"
#include "DriverGirouette.h"
#include "plateau.h"
#include "voiles.h"
//#include "Roulis.h"
//#include "MySPI.h"


//declarer timer 
MyTimer_Struct_TypeDef Timer4		= {TIM2, 9999, 143};
MyGPIO_Struct_TypeDef GPIOPWM		= {GPIOA, 1, AltOut_Ppull};// PWM : TIM 3 , PB0 ,channel 3
MyGPIO_Struct_TypeDef GPIOSens	= {GPIOB, 5, Out_Ppull};// PB5
MyGPIO_Struct_TypeDef GPIORcv		= {GPIOA,10,In_Floating};// RX : PA10 
USART_TypeDef * USART						= USART1;


signed char value;
float floatValue; //value sous forme float

void updateRapport() {
	value = UART_Receive(USART);
	floatValue = (float) value;
	
	
	if (floatValue >= 0) {
			MyGPIO_Reset(GPIOSens.GPIO, GPIOSens.GPIO_Pin);
		set_pulse_pwm_CH2(Timer4.Timer, floatValue);
	}
	else{
		MyGPIO_Set(GPIOSens.GPIO, GPIOSens.GPIO_Pin);
		set_pulse_pwm_CH2(Timer4.Timer, floatValue*(-1));
	}
}

char * data = "hello";
int cmpt = 0;
char i_uart = 0;

void UART_Print ( void )
{
	
	UART_Send(USART1, *data);
		
	i_uart = UART_Receive(USART1);
		
	UART_Send_Str(USART1, "test\n");
	i_uart = UART_Receive(USART1);

}


///* roulis */
//Acc acceleration; 
//float X;
//float Y;
//float Z;
//float roll;
//int redress = 0;


int main ( void ){
	RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4);
	init_Incrementation();
	initGPIOTimerPWM();
	plateau_Init(&Timer4, &GPIOPWM, &GPIOSens, &GPIORcv, USART, updateRapport);
	UART_Init(USART1,9600);
	
//	/* init roulis */
//	roll=0.0;
//	acceleration.accx=0;
//	acceleration.accy=0;
//	acceleration.accz=0;
//	MySPI_Init(SPI1);
//	initRoulis();

	while (1) {
//		/* calcul roulis */
//		calculRoulis(&acceleration);
//		
//		/* calcul de roll et mise à jour de redress -> notifier un redressement */
//		X=acceleration.accx * 4e-3;
//		Y=acceleration.accy * 4e-3;
//		Z=acceleration.accz * 4e-3;
//		if (Y*Z<0){
//			roll=atan(-Y/Z);
//		} else {
//			roll=atan(Y/Z);
//		}
//		if (roll>=(40*2*M_PI/360)){ //limite de 40° en radians
//			redress = 1;
//		} else { 
//			redress = 0;
//		}
//		
		UART_Print();
		updateRapport();
		controleVoiles();
	}
	

}



