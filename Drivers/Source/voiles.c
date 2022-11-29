#include "voiles.h"
#include "Roulis.h"
#include "MySPI.h"


#define ZERO 90

	void controleVoiles(void)
	{
		/*if (calculRoulis() == 0){
			
			int angleServo;
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
		else {
			controleServoMoteur(0);
		}*/
		int angleServo;
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
		
