

#ifndef PLATEAU_H
#define PLATEAU_H

#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyTimer.h"
#include "MyUART.h"

void plateau_Init(MyTimer_Struct_TypeDef * Timer, MyGPIO_Struct_TypeDef * GPIOPWM, MyGPIO_Struct_TypeDef * GPIOSens, MyGPIO_Struct_TypeDef * GPIORcv, USART_TypeDef * USART, void (*IT_function ) ( void ));

#endif






/*#ifndef PLATEAU_H
#define PLATEAU_H

#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyTimer.h"
#include "MyUART.h"

void plateau_Init(void);

void updateRapport(void);

#endif*/