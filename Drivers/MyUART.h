#ifndef DRIVER_UART
#define DRIVER_UART
#include "stm32f10x.h"

//On utilise le type USART_TypeDef

/*
*****************************************************************************************
* @brief

* @param -> 	- USART_TypeDef * USART : USART Concerne
							- int BaudRate : BaudRate
							
* @Note -> Initialisation de l'USART; procédure d'initialisation page 797  du manuel
*************************************************************************************************
*/
void UART_Init( USART_TypeDef * USART, int BaudRate) ;



/*
**************************************************************************************************
* @brief
* @param : 
* @Note : La fonction MyTimer_Base_Init doit avoir ete lancee au prealable
**************************************************************************************************
*/
void UART_Active (   ) ;

#endif