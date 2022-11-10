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
* @brief UART_Active
* @param : 
* @Note : La fonction UART_Init doit avoir ete lancee au prealable
**************************************************************************************************
*/
void UART_Active (USART_TypeDef * USART, uint32_t Prio, void (*IT_function)(void)) ;


/*
**************************************************************************************************
* @brief UART_Send
* @param : 
* @Note : Envoi de données
**************************************************************************************************
*/
void UART_Send (USART_TypeDef * USART, char Data) ;

/*
**************************************************************************************************
* @brief UART_Receive
* @param : 
* @Note : Reception de données
**************************************************************************************************
*/
char UART_Receive (USART_TypeDef * USART) ;

#endif