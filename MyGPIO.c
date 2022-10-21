#include <Driver_GPIO.h>
#include <string.h>

void MyGPIO_Init ( MyGPIO_Struct_TypeDef * GPIOStructPtr ){
	if (GPIOStructPtr->GPIO_Pin <8){
		GPIOStructPtr->GPIO->CRL &= ~(0xF << ((GPIOStructPtr->GPIO_Pin)*4-1));
		GPIOStructPtr->GPIO->CRL |= (GPIOStructPtr->GPIO_Conf << ((GPIOStructPtr->GPIO_Pin)*4-1));
	}
	else{
		GPIOStructPtr->GPIO->CRH &= ~(0xF << ((GPIOStructPtr->GPIO_Pin-8)*4-1));
		GPIOStructPtr->GPIO->CRH |= (GPIOStructPtr->GPIO_Conf << ((GPIOStructPtr->GPIO_Pin-8)*4-1));
	}
}
int MyGPIO_Read ( GPIO_TypeDef * GPIO , char GPIO_Pin ){
	uint32_t masque = (0xFFFFFFFF);
	masque &= ~(0x1 << (GPIO_Pin));
	return (GPIO->IDR & ~(masque))>0;
}
void MyGPIO_Set ( GPIO_TypeDef * GPIO , char GPIO_Pin ){
	GPIO->ODR |= 0x1 << (GPIO_Pin);
}
void MyGPIO_Reset ( GPIO_TypeDef * GPIO , char GPIO_Pin ){
	GPIO->ODR &= ~(0x1 << (GPIO_Pin));
}
void MyGPIO_Toggle ( GPIO_TypeDef * GPIO , char GPIO_Pin ){
	if (MyGPIO_Read(GPIO,GPIO_Pin)==0){
		MyGPIO_Set(GPIO,GPIO_Pin);
	}
	else{
		MyGPIO_Reset(GPIO,GPIO_Pin);
	}
}
