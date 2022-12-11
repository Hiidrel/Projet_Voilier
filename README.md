La branche Jarttard contient principalement les documents Roulis.c, Roulis.h et MySPI.c (MySPI.h n'a pas été modifié).

# Roulis.h #
Comprend les définitions des fonctions développées dans Roulis.c et des #define pour le setup des registres du SPI.

# Roulis.c # 
Comprend les trois fonctions initRoulis, calculRoulis et un main.
### main ###
Exécute ce qui devra être mis dans un "main" général du voilier, soit la configuration et, indéfiniment, le calcul de l'angle.
### initRoulis ###
Permet d'initialiser le SPI via MySPI.c (ou la lib), le mapping est NSS -> PA4, SCK -> PA5, MISO -> PA6, MOSI -> PA7, BaudRate à 281,5 kHz, lecture du slave sur front montant.
### calculRoulis ###
Fonction récurrente permettant de calculer l'angle "roll" d'inclinaison du voilier avec demande de redressement lorsque ledit angle dépasse 40° (cf. variable _redress_).

# MySPI.c #
Développement des fonctions définies dans MySPI.h. Problème de remplissage de buffer à l'exécution, il semblerait qu'il faille vérifier que le buffer de lecture / d'écriture se vident lors du développement des fonctions MySPI_Read et MySPI_Send (cf. TXE et RXNE). Nous l'avons mis en place mais n'avons pas pu le vérifier en pratique.
