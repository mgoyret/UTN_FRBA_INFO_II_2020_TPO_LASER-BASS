/**
 * \file            funcUART.h
 * \brief           TPO Informatica 2
 * \author          Grupo 7
 * \date            December, 2020
 */

#ifndef FUNCUART_H_
#define FUNCUART_H_

#include <driversGPIO.h>
#include <driversUART.h>
#include <Regs_LPC176x.h>

//DEFINES
#define BUFFER_TX_SIZE	200
#define BUFFER_RX_SIZE	0
#define NOTEON  1
#define NOTEOFF 0
#define CUERDAAIRE 0
//PROTOTIPOS DE FUNCIONES
void PushTx(uint8_t dato);
uint32_t PopRx(void);
void mandarnota(uint8_t tipo,uint8_t cuerda,uint8_t traste);

#endif /* FUNCUART_H_ */
