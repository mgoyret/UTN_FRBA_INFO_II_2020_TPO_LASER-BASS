/*
 * drivers.h
 *
 *  Created on: 21 Sep 2020
 *      Author: alejo
 */
#ifndef DRIVERSGENERALES_H_
#define DRIVERSGENERALES_H_
#include <Regs_LPC176x.h>
//-----esto no es obligatorio pero facilita la programacion y uso de registros------------
//volatile para que no me fije una variable en una parte que no se modifica pero
//que se puede modificar en otro cpntexto esto pasa con las interrupciones o con los registros
//no si o si pasa que te lo fina pero por las dudas
#define     __R			volatile const
#define     __W     		volatile
#define     __RW	        volatile
typedef	unsigned int		uint32_t;
typedef	short unsigned int	uint16_t;
typedef	unsigned char		uint8_t;
//define registros
//UL le decis que tome al direccion como unsigned long podria funcionar igual
/*#define PINSEL ((__RW uint32_t*) 0x4002C000UL)
#define PINMODE ((__RW uint32_t*) 0x4002C040UL)
#define PINMODE_OD ((__RW uint32_t*) 0x4002C068UL)
#define GPIO ((__RW uint32_t*) 0x2009C000UL)*/
//define puerto y pines
#define LEDSTICK 0,22
#define LED_RED  2,3
#define LED_GREEN 2,2
#define LED_BLUE  2,1//correcto
#define SW1 2,10//EINT0
#define SW2 0,18
#define SW3 0,11
#define SW4 2,13//EINT3
//expansiones
#define EXP0  2,7
#define EXP1  1,29
#define EXP2  4,28
#define EXP3  1,23
#define EXP4  1,20
#define EXP5  0,19
#define EXP6  3,26
#define EXP7  1,25
#define EXP8  1,22
#define EXP9  1,19
#define EXP10 0,20
#define EXP11 3,25
#define EXP12 1,27
#define EXP13 1,24
#define EXP14 1,21
#define EXP15 1,18
//cuerdas
#define C1 EXP12
#define C2 EXP13
#define C3 EXP14
#define C4 EXP15
//ldrs
#define LDR1 EXP2
#define LDR2 EXP3
#define LDR3 EXP4
#define LDR4 EXP5
//PINSEL
#define	PINSEL_GPIO  0
#define	PINSEL_FUNC1 1
//SETDIR-SETMODE-SETMODE_OD
#define OUT 1
#define IN 0
#define MS_NORMAL 0
#define ME_PULLUP 0
#define ME_PULLDOWN 3
//otros(lo deberia catologar)
#define ON 1
#define OFF 0
#define TRUE 	1
#define FALSE	0
#define NO_TRASTE 0
#define NO_LDR 0
#define SI_LDR 1
// SWTraste
#define MAX_REBOTES 8
//Declaracion de estados
#define 	ESPERO	    0
#define 	CHEQUEO	    1
#define 	CHEQUEADO	2
//GneralsInit
void setPinsel(uint8_t puerto, uint8_t pin, uint8_t funcion);
void setPinMode(uint8_t puerto, uint8_t pin, uint8_t mode);
void setPinMode_OD(uint8_t puerto, uint8_t pin, uint8_t mode);
void setDir(uint8_t puerto,uint8_t pin,uint8_t estado);

//GeneralOthers
void setPin(uint8_t puerto, uint8_t pin, uint8_t estado);
uint8_t getPin(uint8_t puerto, uint8_t pin);

//inicializacion gpio
void init_gpio(void);
// drivers entradas
uint8_t barridoTrastes(int cuerda);
void SWTrastes(uint8_t,uint8_t);
void driverTrastes(void);
void driverLdrs(void);
#endif /* DRIVERSGENERALES_H_ */


