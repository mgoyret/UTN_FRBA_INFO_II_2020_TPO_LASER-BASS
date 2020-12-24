/*
 * driversSystick.h
 *
 *  Created on: 17 Oct 2020
 *      Author: alejo
 */
#ifndef DRIVERSYSTICK_H_
#define DRIVERSYSTICK_H_
#include <driversCuerdasyTrastes.h>
#include <Regs_LPC176x.h>
typedef void (*Timer_Handler)(void);
#define N_TIMERS 12
#define N  10	//Si N=10, Systick interrumpe cada 1ms.
#define RUN   1
#define PAUSE 0
//---Prototipos de funciones
void init_systick(void);
void analizarTimers(void);
void timerEvent(void);
#endif /* DRIVERSYSTICK_H_ */

