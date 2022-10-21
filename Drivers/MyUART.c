#include "Driver_UART.h"

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
		USART->BRR |= (int) (72000000/(16*BaudRate));
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

