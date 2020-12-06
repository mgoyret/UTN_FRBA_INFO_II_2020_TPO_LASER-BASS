/*
 * driversUART.h
 *
 *  Created on: 8 Nov 2020
 *      Author: alejo
 */
#include <funcUART.h>
#include <driversGenerales.h>
#include <Regs_LPC176x.h>
//estas 2 ultimas las pongo solo por un para de registro que estan en estas
/*#include "driversPLL.h"
#include "driversSystick.h"*/
#ifndef DRIVERSUART_H_
#define DRIVERSUART_H_
//defines puertos
#define TXUART0 0,2
#define RXUART0 0,3
// prototipos de funciones
void InitUART0(void);
void UART0_StartTx(void);
uint8_t PopTx(void);
void PushRx(uint8_t dato);

#endif /* DRIVERSUART_H_ */
