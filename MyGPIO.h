#ifndef MYGPIO_H
#define MYGPIO_H
#include "stm32f10x.h"
typedef struct
{
	GPIO_TypeDef * GPIO ;
	char GPIO_Pin ; // numero de 0 a 15
	char GPIO_Conf ; // voir ci dessous
} MyGPIO_Struct_TypeDef ;
#define In_Floating 0x4 // a c o m p l e t e r
#define In_PullDown 0x8 // a c o m p l e t e r
#define In_PullUp 0x8 // a c o m p l e t e r
#define In_Analog 0x0 // a c o m p l e t e r
#define Out_Ppull 0x2 // a c o m p l e t e r
#define Out_OD 0x6 // a c o m p l e t e r
#define AltOut_Ppull 0xA // a c o m p l e t e r
#define AltOut_OD 0xE // a c o m p l e t e r
void MyGPIO_Init ( MyGPIO_Struct_TypeDef * GPIOStructPtr ) ;
int MyGPIO_Read ( GPIO_TypeDef * GPIO , char GPIO_Pin ) ; // renvoie 0 ou autre chose different de 0
void MyGPIO_Set ( GPIO_TypeDef * GPIO , char GPIO_Pin ) ;
void MyGPIO_Reset ( GPIO_TypeDef * GPIO , char GPIO_Pin ) ;
void MyGPIO_Toggle ( GPIO_TypeDef * GPIO , char GPIO_Pin ) ;
#endif
