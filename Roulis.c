#include <MySPI.h>

#define ADXL345_MB 0x40
#define ADXL345_WRITE 0x80
#define ADXL345_POWER_CTL 0x2D
#define ADXL345_BW_RATE 0x2C
#define ADXL345_DATA_FORMAT 0x31

int main (void){
	double mesy;
	double mesz;
	MySPI_Init(SPI1);
	MySPI_Clear_NSS();
	/* set de POWER_CTL tq Measure=1 */
	MySPI_Send(ADXL345_POWER_CTL|ADXL345_WRITE);
	MySPI_Send(0x8);
	/* set de BW_RATE tq freq=100 */
	MySPI_Send(ADXL345_BW_RATE|ADXL345_WRITE);
	MySPI_Send(0xA);
	/* set de DATA_FORMAT à 0 (right alignement of bytes)*/
	MySPI_Send(ADXL345_DATA_FORMAT|ADXL345_WRITE);
	MySPI_Send(0x0);
	MySPI_Set_NSS();
	do{
		/* récup des valeurs sur les axes x et y */
		MySPI_Clear_NSS();
		MySPI_Send(0x34|0x40);
		mesy = MySPI_Read()<<8;
		mesy += MySPI_Read();
		mesz = MySPI_Read()<<8;
		mesz += MySPI_Read();
		MySPI_Set_NSS();
	}
	while(1);
}
