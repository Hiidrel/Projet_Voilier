#include "Driver_Timer.h"


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
	Timer->Timer->ARR = Timer->ARR;
	Timer->Timer->PSC = Timer->PSC;
	
}

void TIM1_CC_IRQHandler (void (*IT_function) (void)){
	TIM1->SR &= ~(TIM_SR_UIF);
	
	IT_function();
}

void TIM2_IRQHandler (void (*IT_function) (void)) {
	TIM2->SR &= ~(TIM_SR_UIF) ;
	IT_function();
}

void TIM3_IRQHandler (void (*IT_function) (void)) {
	TIM3->SR &= ~(TIM_SR_UIF);
	IT_function();
}

void TIM4_IRQHandler(void (*IT_function) (void)) {
	TIM4->SR &= ~(TIM_SR_UIF);
	IT_function();
}

void MyTimer_ActiveIT (TIM_TypeDef * Timer, uint32_t Prio,void (*IT_function ) ( void )){
	
	Timer->DIER |= TIM_DIER_UIE;
	
	if (Timer == TIM1){
			NVIC_EnableIRQ(TIM1_UP_IRQn);
			NVIC_SetPriority(TIM1_UP_IRQn, Prio);
		TIM1_CC_IRQHandler(IT_function );
	}
	else	if (Timer == TIM2){
			NVIC_EnableIRQ(TIM2_IRQn);
			NVIC_SetPriority(TIM2_IRQn, Prio);
			TIM2_IRQHandler(IT_function);
	}
	else if (Timer == TIM3){
		NVIC_EnableIRQ(TIM3_IRQn);
		NVIC_SetPriority(TIM3_IRQn, Prio);
		TIM3_IRQHandler(IT_function);
	}
	else if (Timer == TIM4){
		NVIC_EnableIRQ(TIM4_IRQn);
		NVIC_SetPriority(TIM4_IRQn, Prio);
		TIM4_IRQHandler(IT_function);
	}
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

	}
}

void set_pulse_pwm(TIM_TypeDef * Timer , int pulse ){
Timer->CCR1=(Timer->ARR*pulse)/100;
}
