#include "MyADC.h"



void MyADC_Init ( ADC_TypeDef * ADC , int channel) 
{
	if (ADC == ADC1) {
	    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;// validation horloge ADC1
			
	} else if (ADC == ADC2) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN ; // validation horloge ADC2
	}


	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;// passage de l'horloge ADC à 12MHz
	ADC->CR2 |= ADC_CR2_ADON;// démarrage ADC
	ADC->SQR1 &= ADC_SQR1_L;// Fixe le nombre de conversion à 1
	ADC->SQR3|= channel;// indique la voie à convertir
	ADC->CR2 |= ADC_CR2_CAL; // début de la calibration
	while ((ADC->CR2 & ADC_CR2_CAL)); // attente de la fin de la calibration
}

//
int ADC_Result(ADC_TypeDef * ADC){
    ADC->CR2 |= ADC_CR2_ADON; // lancement de la conversion
    while(!(ADC->SR & ADC_SR_EOC)){} // attente de la fin de conversion
    ADC->SR &= ~ADC_SR_EOC; // validation de la conversion
    return ADC->DR & ~((0x0F) << 12); // retour de la conversion
}
