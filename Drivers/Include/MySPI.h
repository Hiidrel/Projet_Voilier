
#ifndef INC_MYSPI_H_
#define INC_MYSPI_H_

#include "stm32f10x.h"

/*************************************************************************************
=====================    By Periph team 	INSA GEI	2022	 ===========================
*************************************************************************************/

/*
*************************************************************************************
=====================     I2C les IO STM32F103      =================================
*************************************************************************************
Les IO sont pris en charge par la lib, pas besoin de faire les configurations


Sur la Nucl�o , le SPI1 est perturb� par la LED2 (PA5), mais doit pouvoir subir les front SCK qd m�me (LED clignote vite..)
le SPI2 n'est pas utilisable car pin non connect�es par d�faut (sauf � modifier les SB). En fait la Nucl�o fait un choix entre SPI1 
et SPI2 par soudage jumper (SB).

-> Utiliser SPI1 avec la carte Nucl�o
  
 * 	**IO SPI 1**
	SPI1_NSS PA4
	SPI1_SCK PA5
	SPI1_MISO  PA6  
	SPI1_MOSI  PA7  

	**IO SPI 2**
	SPI2_NSS PB12
	SPI2_SCK PB13
	SPI2_MISO  PB14  
	SPI2_MOSI  PB15  





*************************************************************************************
==================== Fondamentaux SPI      ==========================================
*************************************************************************************
- Bus Synchrone, 4 fils (m�me si on peut l'utiliser en 3 fils)
- Transfert � l'octet
- Protocole entre un Master (contr�le SCK) et un Slave
- SCK permet de synchroniser les bits de chaque octet. Il se configure par :
	* son niveau de repos : ici niveau '1'
	* le front actif de synchronisation pour chaque bit : ici front montant (front up durant bit stable)
- /CS ou /NSS active le slave sur l'�tat bas
- MOSI : Master Out Slave In (donc data circulant du Master vers le Slave, donc �criture dans le Slave)
- MISO : Master In Slave Out (donc data circulant du Slave vers le Master, donc lecture du Slave)

Bien que la lib propose une fonction d'�criture et de lecture :
	* une �criture s'accompagne obligatoirement d'une lecture (bidon)
	* une lecture s'accompagne obligatoirement d'une �criture (bidon)
La gestion /CS = /NSS se fait "� la main". On peut alors lire toute une s�rie d'octets
en laissant /CS � l'�tat bas pendant toute la dur�e de circulation des octets.


*************************************************************************************
==================== La lib SPI            ==========================================
*************************************************************************************

fonctions essentielles :

MySPI_Init 
MySPI_Send 
MySPI_Read
MySPI_Set_NSS
MySPI_Clear_NSS


==========================================================================================*/




/*========================================================================================= 
														INITIALISATION SPI
========================================================================================= */

/**
	* @brief Configure le SPI sp�cifi� : FSCK = 281kHz, Repos SCK = '1', Front actif = up
					 Gestion /CS logicielle � part, configure les 4 IO
					 - SCK, MOSI : Out Alt push pull
					 - MISO : floating input
					 - /NSS (/CS) : Out push pull
	* @param SPI_TypeDef * SPI : SPI1 ou SPI2 
  */
void MySPI_Init(SPI_TypeDef * SPI);



/**
  * @brief Envoie un octet (/CS non g�r�, � faire logiciellement)
					 Plus en d�tail, �mission de l'octet souhait� sur MOSI
					 Lecture en m�me temps d'un octet poubelle sur MISO (non exploit�)
  * @param : char ByteToSend : l'octet � envoyer
  */
void MySPI_Send(char ByteToSend);


/**
  * @brief Re�oit un octet (/CS non g�r�, � faire logiciellement)
					 Plus en d�tail, �mission d'un octet bidon sur MOSI (0x00)
					 pour �laborer les 8 fronts sur SCK et donc piloter le slave en lecture 
					 qui r�pond sur MISO
	* @param : none
	* @retval : l'octet lu.
  */
char MySPI_Read(void);



/**
  * @brief Positionne /CS = /NSS � '1'. A utiliser pour borner les octets � transmettre/recevoir
	* @param : none
  */
void MySPI_Set_NSS(void);



/**
  * @brief Positionne /CS = /NSS � '0'.  A utiliser pour borner les octets � transmettre/recevoir
	* @param :none
  */
void MySPI_Clear_NSS(void);

#endif 
