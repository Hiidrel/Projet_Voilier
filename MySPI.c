#include <MySPI.h>
#include <Driver_GPIO.h>

/**
	* @brief Configure le SPI spécifié : FSCK = 281kHz, Repos SCK = '1', Front actif = up
					 Gestion /CS logicielle à part, configure les 4 IO
					 - SCK, MOSI : Out Alt push pull
					 - MISO : floating input
					 - /NSS (/CS) : Out push pull
	* @param SPI_TypeDef * SPI : SPI1 ou SPI2 
  */
	
	/* init des 4 sorties de l'ADXL */
	MyGPIO_Struct_TypeDef NSS={GPIOA, 4, Out_Ppull};
	MyGPIO_Struct_TypeDef SCK={GPIOA, 5, AltOut_Ppull};
	MyGPIO_Struct_TypeDef MISO={GPIOA, 6, In_Floating};
  MyGPIO_Struct_TypeDef MOSI={GPIOA, 7, AltOut_Ppull}; 

void MySPI_Init(SPI_TypeDef * SPI){
	SPI->CR1|=1<<2; //master mode 
	/* enable de la clock et remap de SPI1 */
	RCC->APB2ENR|=RCC_APB2ENR_SPI1EN;
	AFIO->MAPR&=~(AFIO_MAPR_SPI1_REMAP);
	/* init de BaudRate à FSCK=281kHz, replace NSS by SSI, SSI to determine NSS, SSM to manage slave, SPE to enable the SPI */
	SPI->CR1|=SPI_CR1_BR;
	SPI->CR1|=SPI_CR1_SSM;
	SPI->CR1|=SPI_CR1_SSI;
	SPI->CR1|=SPI_CR1_MSTR;
	SPI->CR1|=SPI_CR1_SPE;
	/* init de la lecture du slave sur front montant = transmission mode */
	SPI->CR1|=SPI_CR1_CPHA;
	SPI->CR1|=SPI_CR1_CPOL;
	
	
	SPI->CR1&=~(SPI_CR1_LSBFIRST);
	SPI->CR1&=~(SPI_CR1_RXONLY);
	SPI->CR1&=~(SPI_CR1_DFF);
	
	//	/* init du SR */
	//	SPI->SR&=~(SPI_SR_BSY); //not busy when it starts
	//	SPI->SR|=(SPI_SR_TXE); // transmission buffer empty
	//	SPI->SR&=~(SPI_SR_RXNE); //reception buffer empty
	
	/* config des modes des pins */
	RCC->APB2ENR|=RCC_APB2ENR_IOPAEN; //enable de la clock
	MyGPIO_Init(&NSS);
	MyGPIO_Init(&SCK);
	MyGPIO_Init(&MISO);
	MyGPIO_Init(&MOSI);	
}

void MySPI_Send(char ByteToSend){
	char data;
	while(!(SPI1->SR&(SPI_SR_TXE))){};
	SPI1->DR = ByteToSend;
	data = MySPI_Read();
}

char MySPI_Read(void){
	while(!(SPI1->SR&(SPI_SR_RXNE))){};
	while(!(SPI1->SR&(SPI_SR_TXE))){};
	return SPI1->DR;
}

void MySPI_Set_NSS(void){
	GPIOA->BSRR|=GPIO_BSRR_BS4;
	GPIOA->BSRR&=~(GPIO_BSRR_BR4);
}

void MySPI_Clear_NSS(void){
	GPIOA->BSRR&=~(GPIO_BSRR_BS4);
	GPIOA->BSRR|=GPIO_BSRR_BR4;
}
