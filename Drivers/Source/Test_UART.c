#include "Test_UART.h"

char * data = "hello";
int cmpt = 0;
char i_uart = 0;

void UART_Print ( void )
{
	
	UART_Send(USART1, *data);
		
	i_uart = UART_Receive(USART1);
		
	UART_Send_Str(USART1, "test\n");
	i_uart = UART_Receive(USART1);

}

//connexion telecommande