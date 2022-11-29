#ifndef DRIVER_CLK
#define DRIVER_CLK
#include "stm32f10x.h"
typedef struct
{
TIM_TypeDef * Timer ; // TIM1 à TIM4
unsigned short ARR ;
unsigned short PSC ;
} MyTimer_Struct_TypeDef ;

/*
*****************************************************************************************
* @brie f
* @param -> Paramè t r e sous forme d ’ une s t r u c t u r e ( son a d re s se ) con ten an t l e s
i n f o rm a ti o n s de base
* @Note -> F onc ti on à l a n c e r s y s t ématiquement avan t d ’ a l l e r pl u s en dé t a i l dans l e s
con f pl u s f i n e s (PWM, codeur i n c . . . )
*************************************************************************************************
*/
void MyTimer_Base_Init( MyTimer_Struct_TypeDef * Timer ) ;

/*
**************************************************************************************************
* @brief
* @param : -TIM_TypeDef * Timer : Timer concerne
- char Prio : de 0 a 15
* @Note : La fonction MyTimer_Base_Init doit avoir ete lancee au prealable
Page 2 of 4
Activité 2 : Utilisation des Timer et gestion des Interruptions
**************************************************************************************************
*/
void MyTimer_ActiveIT ( TIM_TypeDef * Timer , uint32_t Prio , void (*IT_function ) ( void )  ) ;

//PMW

void MyTimer_PWM( TIM_TypeDef * Timer , int Channel ) ;
void set_pulse_pwm_CH1(TIM_TypeDef * Timer , int pulse );
void set_pulse_pwm_CH2(TIM_TypeDef * Timer , int pulse );
void set_pulse_pwm_CH3(TIM_TypeDef * Timer , int pulse );
void set_pulse_pwm_CH4(TIM_TypeDef * Timer , int pulse );

#define MyTimer_Base_Start(ptrTimer) ((ptrTimer)->Timer->CR1 |= (1<<0))
#define MyTimer_Base_Stop(ptrTimer) ((ptrTimer)->Timer->CR1 |= (0<<0))
#endif


