#ifndef ROULIS_H_
#define ROULIS_H_

/* Include */
#include <MySPI.h>
#include <math.h>
#include <MyGPIO.h>

/* Constantes, Define */
#define ADXL345_MB 0x40
#define ADXL345_READ 0x80
#define ADXL345_POWER_CTL 0x2D
#define ADXL345_BW_RATE 0x2C
#define ADXL345_DATA_FORMAT 0x31
#define DATA_START 0x32
#define M_PI 3.1415

/* structure contenant les accélarations sur x, y et z (short int car Data sur 2 octets par axe) */
typedef struct{
	short int accx;
	short int accy;
	short int accz;
}	Acc;

/* fonction main vide */
int main(void);
/* fonction d'initialisation du SPI / ADXL */
void initRoulis(void);
/* fonction de calcul de l'angle roulis (renvoie 0 ou 1) */
void calculRoulis(Acc * ptrAcc);

#endif