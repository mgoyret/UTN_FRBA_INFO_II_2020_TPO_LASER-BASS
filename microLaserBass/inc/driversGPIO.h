/**
 * \file            driversGPIO.h
 * \brief           TPO Informatica 2
 * \author          Grupo 7
 * \date            December, 2020
 */
#ifndef DRIVERSGPIO_H_
#define DRIVERSGPIO_H_
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

//GneralsInit
void setPinsel(uint8_t puerto, uint8_t pin, uint8_t funcion);
void setPinMode(uint8_t puerto, uint8_t pin, uint8_t mode);
void setPinMode_OD(uint8_t puerto, uint8_t pin, uint8_t mode);
void setDir(uint8_t puerto,uint8_t pin,uint8_t estado);

//GeneralOthers
void setPin(uint8_t puerto, uint8_t pin, uint8_t estado);
uint8_t getPin(uint8_t puerto, uint8_t pin);


#endif /* DRIVERSGPIO_H_ */


