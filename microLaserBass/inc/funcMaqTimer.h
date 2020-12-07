/*
 * funcMaqTImer.h
 *
 *  Created on: 28 Oct 2020
 *      Author: alejo
 */

#ifndef FUNCMAQTIMER_H_
#define FUNCMAQTIMER_H_
#define SEG 1000
#define MSEG 1
#define NULL ((void*)0)
#include <driversGenerales.h>
#include <driversSystick.h>
void timerStart(uint8_t event, uint32_t time, Timer_Handler handler ,uint8_t base );
void timerStop( uint8_t event );

#endif /* FUNCMAQTIMER_H_ */
