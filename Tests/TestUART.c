#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyTimer.h"
#include "MyUART.h"
#include "Macros.h"




char * data = "hello";
int cmpt = 0;
char i_uart = 0;

int main ( void )
{
	
	
	RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4);
	
	

	
	UART_Init(USART1,9600);
	

	    UART_Send(USART1, *data);
	    
	while (1){
		UART_Send(USART1, *data);
		
		i_uart = UART_Receive(USART1);
		
		UART_Send_Str(USART1, "test");
		i_uart = UART_Receive(USART1);
	}
	return 0;
}

//connexion telecommande