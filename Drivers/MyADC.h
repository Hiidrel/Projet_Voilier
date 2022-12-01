#ifndef MYADC_H
#define MYADC_H
#include "stm32f10x.h"



/*
*****************************************************************************************
* @brief

* @param -> 	- ADC_TypeDef * ADC: ADC Concerne
							- int channel : channel
							
* @Note -> Initialisation de l'ADC; proc�dure d'initialisation 
*************************************************************************************************
*/

void MyADC_Init ( ADC_TypeDef * ADC , int channel);


//R�cup�re la valeur brute donn�e par l'ADC
int ADC_Result(ADC_TypeDef * ADC);


#endif