#include <MySPI.h>
#include <math.h>

#define ADXL345_MB 0x40
#define ADXL345_READ 0x80
#define ADXL345_POWER_CTL 0x2D
#define ADXL345_BW_RATE 0x2C
#define ADXL345_DATA_FORMAT 0x31
#define M_PI 3.1415
double mesx;
double mesy;
double mesz;
signed int accx;
signed int accy;
signed int accz;
int roll;


int main (void){
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
	do{
		/* récup des valeurs sur les axes y et z */
		MySPI_Clear_NSS();
		MySPI_Send(0x32|ADXL345_MB|ADXL345_READ);
		mesx = MySPI_Read()<<8;
		mesx += MySPI_Read();
		mesy = MySPI_Read()<<8;
		mesy += MySPI_Read();
		mesz = MySPI_Read()<<8;
		mesz += MySPI_Read();
		accx = (signed int)(((signed int)mesx) * 3.9);
		accy = (signed int)(((signed int)mesy) * 3.9);
		accz = (signed int)(((signed int)mesz) * 3.9);
		roll = 180 * atan (accy/sqrt(accx*accx + accz*accz))/M_PI;		
		MySPI_Set_NSS();
	}
	while(1);
}
