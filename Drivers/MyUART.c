#include "Driver_UART.h"

void (*		IT_function_UART1)(void);
void (*		IT_function_UART2)(void);
void (*		IT_function_UART3)(void);


void UART_Init( USART_TypeDef * USART, int BaudRate){
	
	//Enable USART
	USART->CR1 |= USART_CR1_UE;
	
	//Word Length : 0: 1 Start bit, 8 Data bits, n Stop bit
	USART->CR1 &= ~(USART_CR1_M);
	
	//STOP bits : 1 stop bit
	USART->CR2 &= ~(USART_CR2_STOP);
	
	//Baud Rate and Clock Activation
	if (USART == USART1){
		RCC ->APB2ENR |= RCC_APB2ENR_USART1EN;
		USART->BRR = (int) (72000000/(BaudRate));
		USART->BRR = BaudRate;
	}
	else if (USART == USART2){
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
		USART->BRR |= (int) (36000000/(16*BaudRate));
	}
	else if (USART == USART3){
		RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
		USART->BRR |= (int) (36000000/(16*BaudRate));
	}
	
	//Transmitter Enable
	USART->CR1 |= USART_CR1_TE;
	
	//Receiver Enable
	USART->CR1 |= USART_CR1_RE;
	
}

void UART_Send (USART_TypeDef * USART, char Data){
	USART->DR = Data;
	
	while (!(USART->SR & USART_SR_TC)){
		
	}
}
char UART_Receive (USART_TypeDef * USART){
 return (signed char) USART->DR ;
}

void UART_ActiveIT (USART_TypeDef * USART, uint32_t Prio, void (*IT_function)(void)){
	
	USART->CR1 |= USART_CR1_RXNEIE;
	
	if (USART == USART1){
		NVIC_EnableIRQ(USART1_IRQn);
		NVIC_SetPriority(USART1_IRQn, Prio);
		IT_function_UART1=IT_function;
		
	}
	else if(USART == USART2){
		NVIC_EnableIRQ(USART2_IRQn);
		NVIC_SetPriority(USART2_IRQn, Prio);
		IT_function_UART2=IT_function;
	}
	else if(USART == USART3){
		NVIC_EnableIRQ(USART3_IRQn);
		NVIC_SetPriority(USART3_IRQn, Prio);
		IT_function_UART3=IT_function;
	}
	
}



