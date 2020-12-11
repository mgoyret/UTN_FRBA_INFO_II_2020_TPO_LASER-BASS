/**
 * \file            driversCuerdasyTrastes.h
 * \brief           TPO Informatica 2
 * \author          Grupo 7
 * \date            December, 2020
 */
#ifndef DRIVERSCUERDASYTRASTES_H_
#define DRIVERSCUERDASYTRASTES_H_

#include <driversGPIO.h>
//DEFINES
#define NO_TRASTE 0
#define NO_LDR 0
#define SI_LDR 1
#define MAX_REBOTES 8
//Declaracion de estados
#define 	ESPERO	    0
#define 	CHEQUEO	    1
#define 	CHEQUEADO	2

//PROTOTIPOS DE FUNCIONES
//inicializacion gpio
void init_gpio(void);
uint8_t barridoTrastes(int cuerda);
void SWTrastes(uint8_t,uint8_t);
void driverTrastes(void);
void driverLdrs(void);
#endif /* DRIVERSCUERDASYTRASTES_H_ */
