/*
 * funcMaqTImer.h
 *
 *  Created on: 28 Oct 2020
 *      Author: alejo
 */

#ifndef FUNCMAQTIMER_H_
#define FUNCMAQTIMER_H_

//HEADERS
#include <driversGPIO.h>
#include <driversSystick.h>
//DEFINES
#define SEG 1000
#define MSEG 1
#define NULL ((void*)0)

//PROTOTIPODEFUNCIONES
void timerStart(uint8_t event, uint32_t time, Timer_Handler handler ,uint8_t base );
void timerStop( uint8_t event );
void TimerClose( void );
void StandByTimer( uint8_t event , uint8_t accion);
void SetTimer( uint8_t event , uint32_t time );
uint32_t GetTimer( uint8_t event );
#endif /* FUNCMAQTIMER_H_ */
