#ifndef ROULIS_H_
#define ROULIS_H_

/* Include */
#include <MySPI.h>
#include <math.h>
#include <Driver_GPIO.h>

/* Constantes, Define */
#define ADXL345_MB 0x40
#define ADXL345_READ 0x80
#define ADXL345_POWER_CTL 0x2D
#define ADXL345_BW_RATE 0x2C
#define ADXL345_DATA_FORMAT 0x31
#define M_PI 3.1415

/* fonction main vide */
int main();
/* fonction d'initialisation du SPI / ADXL */
void initRoulis();
/* fonction de calcul de l'angle roulis (renvoie 0 ou 1) */
int calculRoulis();

#endif
