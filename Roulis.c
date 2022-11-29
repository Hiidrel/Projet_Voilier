#include <MySPI.h>
#include <math.h>
#include <Driver_GPIO.h>

#define ADXL345_MB 0x40
#define ADXL345_READ 0x80
#define ADXL345_POWER_CTL 0x2D
#define ADXL345_BW_RATE 0x2C
#define ADXL345_DATA_FORMAT 0x31
#define M_PI 3.1415
uint16_t mesx;
uint16_t mesy;
uint16_t mesz;
signed int accx;
signed int accy;
signed int accz;
int roll;
int redress;

int calculRoulis(){
		/* récup des valeurs sur les axes y et z */
		MySPI_Clear_NSS();
		MySPI_Send(0x32|ADXL345_MB|ADXL345_READ);
		mesx = MySPI_Read();
		mesx += MySPI_Read()<<8;
		mesx &=~(0xE000);
		mesy = MySPI_Read();
		mesy += MySPI_Read()<<8;
		mesx &=~(0xE000);
		mesz=MySPI_Read();
		mesz += MySPI_Read()<<8;
		mesx &=~(0xE000);
		MySPI_Set_NSS();
		/* calcul de l'angle de rotation du voilier */
		accx = (signed int)((mesx) * 3.9);
		accy = (signed int)((mesy) * 3.9);
		accz = (signed int)((mesz) * 3.9);
		roll = (180 * atan (accy/sqrt(accx*accx + accz*accz)))/M_PI;
		
		/** ci-après le code permettant d'appeler la fonction retourRoulis pour controleVoile (cf. programme voiles) --> pour redresser le voilier
		if (roll > seuil){ //seuil valeur empirique que nous n'avons pas pu déterminer
			redress=1;
		}
		else{
		**/
		redress=0; //renvoie toujours false (cf. pas de test roll > seuil)
		
		//}
		return redress;
}

void initRoulis (void){
	
	MySPI_Init(SPI1);
	MySPI_Clear_NSS();
	/* set de POWER_CTL tq Measure=1 */
	MySPI_Send(ADXL345_POWER_CTL& ~(ADXL345_READ));
	MySPI_Send(0x8);
	/* set de BW_RATE tq freq=100 */
	MySPI_Send(ADXL345_BW_RATE& ~(ADXL345_READ));
	MySPI_Send(0xA);
	/* set de DATA_FORMAT à 0 (right alignement of bytes)*/
	MySPI_Send(ADXL345_DATA_FORMAT& ~(ADXL345_READ));
	MySPI_Send(0x0);
	MySPI_Set_NSS();
}

int main (void){
	while(1){};
}
