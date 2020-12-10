/*
 * funcUART.h
 *
 *  Created on: 8 Nov 2020
 *      Author: alejo
 */

#ifndef FUNCUART_H_
#define FUNCUART_H_

#include <driversGenerales.h>
#include <driversUART.h>
#include <Regs_LPC176x.h>

//Defines
#define BUFFER_TX_SIZE	200
#define BUFFER_RX_SIZE	5
#define NOTEON  1
#define NOTEOFF 0
#define CUERDAAIRE 0

void PushTx(uint8_t dato);
uint32_t PopRx(void);
void mandarnota(uint8_t tipo,uint8_t cuerda,uint8_t traste);

#endif /* FUNCUART_H_ */
