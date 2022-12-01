#include <MySPI.h>
#include <math.h>
#include <Driver_GPIO.h>
#include <Roulis.h>

void calculRoulis(Acc * ptrAcc){
	
		/* variables pour stocker DATA_X, DATA_Y et DATA_Z */
		int mesx0;
		int mesx1;
		int mesy0;
		int mesy1;
		int mesz0;
		int mesz1;
	
		/* récup des valeurs sur les axes x y et z */
		MySPI_Clear_NSS();
		MySPI_Send(DATA_START|ADXL345_MB|ADXL345_READ);
		mesx0=MySPI_Read();
		mesx1=MySPI_Read();
		mesy0=MySPI_Read();
		mesy1=MySPI_Read();
		mesz0=MySPI_Read();
		mesz1=MySPI_Read();
		MySPI_Set_NSS();
	
		/* reset puis mise à jour du pointeur d'accélération */
		ptrAcc->accx = ptrAcc->accx &~(0xFF);
		ptrAcc->accx = ptrAcc->accx &~(0xFF<<8);
		ptrAcc->accy = ptrAcc->accy &~(0xFF);
		ptrAcc->accy = ptrAcc->accy &~(0xFF<<8);
		ptrAcc->accz = ptrAcc->accz &~(0xFF);
		ptrAcc->accz = ptrAcc->accz &~(0xFF<<8);
		ptrAcc->accx = ptrAcc->accx | mesx0;
		ptrAcc->accx = ptrAcc->accx |(mesx1<<8);
		ptrAcc->accy = ptrAcc->accy | mesy0;
		ptrAcc->accy = ptrAcc->accy |(mesy1<<8);
		ptrAcc->accz = ptrAcc->accz | mesz0;
		ptrAcc->accz = ptrAcc->accz |(mesz1<<8);
}

void initRoulis (void){
	MySPI_Clear_NSS();
	/* set de POWER_CTL tq Measure=1 */
	MySPI_Send(ADXL345_POWER_CTL& ~(ADXL345_READ));
	MySPI_Send(0x8);
	/* set de BW_RATE tq freq=100Hz */
	MySPI_Send(ADXL345_BW_RATE& ~(ADXL345_READ));
	MySPI_Send(0xA);
	/* set de DATA_FORMAT à 0 (right alignement of bytes)*/
	MySPI_Send(ADXL345_DATA_FORMAT& ~(ADXL345_READ));
	MySPI_Send(0xB);
	MySPI_Set_NSS();
}

Acc acceleration; 
float X;
float Y;
float Z;
float roll;
int redress = 0;
int main (void){
	/*initialisation du roulis et des différentes variables */
	roll=0.0;
	acceleration.accx=0;
	acceleration.accy=0;
	acceleration.accz=0;
	MySPI_Init(SPI1);
	initRoulis();
	
	/* boucle infinie : récupération des données de l'accélération du voilier */
	while(1){
		calculRoulis(&acceleration);
		
		/* calcul de roll et mise à jour de redress -> notifier un redressement */
		X=acceleration.accx * 4e-3;
		Y=acceleration.accy * 4e-3;
		Z=acceleration.accz * 4e-3;
		if (Y*Z<0){
			roll=atan(-Y/Z);
		} else {
			roll=atan(Y/Z);
		}
		if (roll>=(40*2*M_PI/360)){ //limite de 40° en radians
			redress = 1;
		} else { 
			redress = 0;
		}
	};
}
