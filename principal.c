#include "DriverVoiles.h"
#include "MyGPIO.h"
#include "MyTimer.h"
#include "DriverGirouette.h"

#define ZERO 90

int angleServo;
int test_angle;

void girouetteToServomoteur(void)
{
	int angleG=angleGirouette();
	if ((angleG<45) || (angleG>315))
	{
		controleServoMoteur(ZERO);
	}
	else if ((angleG>=45) && (angleG<=180))
	{
		angleServo=90-(((angleG*2)/3)-30);
		controleServoMoteur(angleServo);
	}
	else if ((angleG>180) && (angleG<=315))
	{
		angleServo=(((angleG*2)/3)-120);
		controleServoMoteur(angleServo);
	}
}

void basculeRoulie(int angleR)
{
	if (angleR>=50)
	{
		controleServoMoteur(90);
	}
}





int main (void)
{
	//INIT
	RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4);
	init_Incrementation();
	initGPIOTimerPWM();
	
	while(1)
	{
		test_angle = angleGirouette();
		girouetteToServomoteur();
	}
		
}
