#include "DriverVoiles.h"
#include "MyGPIO.h"
#include "MyTimer.h"


MyGPIO_Struct_TypeDef GPIO_B8={GPIOB, 8, AltOut_Ppull};
MyTimer_Struct_TypeDef TIMER4={TIM4, 9999, 143};

void initGPIOTimerPWM(void)
{
	MyGPIO_Init(&GPIO_B8);
	MyTimer_Base_Init(&TIMER4);
	MyTimer_PWM(TIM4,3);
}


int angleToRapportCyclique(int angle)
{
	return (((angle/18)+5)*10);
}

void controleServoMoteur(int angle)
{
	set_pulse_pwm_CH3(TIM4,angleToRapportCyclique(angle));
}
