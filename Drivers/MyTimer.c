#include "MyTimer.h"

void (*	IT_function1)(void);
void (*	IT_function2)(void);
void (*	IT_function3)(void);
void (*	IT_function4)(void);

void MyTimer_Base_Init( MyTimer_Struct_TypeDef * Timer ){
	
	if (Timer->Timer == TIM1){
		RCC -> APB2ENR |= RCC_APB2ENR_TIM1EN;
	}else if (Timer->Timer == TIM2) {
		RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;
	}else if (Timer->Timer == TIM13) {
		RCC -> APB1ENR |= RCC_APB1ENR_TIM3EN;
	}else if (Timer->Timer == TIM4) {
		RCC -> APB1ENR |= RCC_APB1ENR_TIM4EN;
	}
	Timer->Timer->CR1 |= (0x01<<0);
	Timer->Timer->ARR &= ~(0xFFFF<<0);
	Timer->Timer->ARR |= (Timer->ARR<<0);
	Timer->Timer->PSC |= ~(0xFFFF<<0);
	Timer->Timer->PSC |= (Timer->PSC<<0);
	
}

void TIM1_CC_IRQHandler (void){
	TIM1->SR &= ~(TIM_SR_UIF);
	
	IT_function1();
}

void TIM2_IRQHandler  (void) {
	TIM2->SR &= ~(TIM_SR_UIF) ;
	IT_function2();
}

void TIM3_IRQHandler  (void) {
	TIM3->SR &= ~(TIM_SR_UIF);
	IT_function3();
}

void TIM4_IRQHandler (void) {
	TIM4->SR &= ~(TIM_SR_UIF);
	IT_function4();
}

void MyTimer_ActiveIT (TIM_TypeDef * Timer, uint32_t Prio,void (*IT_function ) ( void )){
	
	Timer->DIER |= TIM_DIER_UIE;
	
	if (Timer == TIM1){
			NVIC_EnableIRQ(TIM1_UP_IRQn);
			NVIC_SetPriority(TIM1_UP_IRQn, Prio);
		IT_function1= IT_function;
	}
	else	if (Timer == TIM2){
			NVIC_EnableIRQ(TIM2_IRQn);
			NVIC_SetPriority(TIM2_IRQn, Prio);
			IT_function2=IT_function;
	}
	else if (Timer == TIM3){
		NVIC_EnableIRQ(TIM3_IRQn);
		NVIC_SetPriority(TIM3_IRQn, Prio);
		IT_function3=IT_function;
	}
	else if (Timer == TIM4){
		NVIC_EnableIRQ(TIM4_IRQn);
		NVIC_SetPriority(TIM4_IRQn, Prio);
		IT_function4=IT_function;	}
}


//PWM

void MyTimer_PWM( TIM_TypeDef * Timer , int Channel ) {
	
	switch(Channel){
		case (1):
			Timer->CCMR1&=~(TIM_CCMR1_OC1M_0);
			Timer->CCMR1 |=TIM_CCMR1_OC1M_1|TIM_CCMR1_OC1M_2;
		  Timer->CCER|=TIM_CCER_CC1E;
		break;
		case (2):
			Timer->CCMR1&=~(TIM_CCMR1_OC1M_0);
			Timer->CCMR1 |=TIM_CCMR1_OC2M_1|TIM_CCMR1_OC2M_2;
			Timer->CCER|=TIM_CCER_CC2E;
				break;

		case (3):
			Timer->CCMR2&=~(TIM_CCMR2_OC3M_0);
			Timer->CCMR2 |=TIM_CCMR2_OC3M_1|TIM_CCMR2_OC3M_2;
			Timer->CCER|=TIM_CCER_CC3E;
				break;

		case (4):
			Timer->CCMR2&=~(TIM_CCMR2_OC4M_0);
			Timer->CCMR2 |=TIM_CCMR2_OC4M_1|TIM_CCMR2_OC4M_2;
			Timer->CCER|=TIM_CCER_CC4E;
				break;

	} //a revoir parce que ne l'enable pas tres bien, erreur de registre
}

void set_pulse_pwm_CH1(TIM_TypeDef * Timer , int rappCyclique ){
Timer->CCR1=(((Timer->ARR)+1)*rappCyclique)/100;
}

void set_pulse_pwm_CH2(TIM_TypeDef * Timer , int rappCyclique ){
Timer->CCR2=(((Timer->ARR)+1)*rappCyclique)/100;
}
void set_pulse_pwm_CH3(TIM_TypeDef * Timer , int rappCyclique ){
Timer->CCR3=(((Timer->ARR)+1)*rappCyclique)/100;
}
void set_pulse_pwm_CH4(TIM_TypeDef * Timer , int rappCyclique ){
Timer->CCR4=(((Timer->ARR)+1)*rappCyclique)/100;
}