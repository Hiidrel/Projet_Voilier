//ADC: pa1 ; tim2 ; ch2
//PWM/pa7 ; tim3,ch2
#include "MyADC.h"
#include "MyGPIO.h"
#include "stm32f10x.h"
#include "MyTimer.h"

MyTimer_Struct_TypeDef Timer3 = {TIM3   , 719 , 0};
MyGPIO_Struct_TypeDef GPIO_PWM =  {GPIOA, 7, AltOut_Ppull};
MyGPIO_Struct_TypeDef GPIOADC		= {GPIOA,1,In_Analog};// PA1


int main ( void ){
	
	int result=0;
	//Timer
	MyTimer_Base_Init(&Timer3);

		// Configuration GPIO PWM & ADC
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	MyGPIO_Init(&GPIO_PWM);	
	MyGPIO_Init(&GPIOADC);
	
	//PWM
	MyTimer_PWM(TIM3,2);
	set_pulse_pwm_CH2(TIM3,0);
	
	//ADC
	ADC1->CR2 |= ADC_CR2_CONT;//continuous mode
	MyADC_Init (ADC1,2) ;
	
	while (1)
	{
		result = ADC_Result (ADC1); //conversion 
		set_pulse_pwm_CH2(TIM3,100 * result / 0xFFF);
	
	}
	return 0 ; 
}