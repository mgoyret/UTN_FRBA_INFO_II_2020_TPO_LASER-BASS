/**
 * \file            driversUART.h
 * \brief           TPO Informatica 2
 * \author          Grupo 7
 * \date            December, 2020
 */

#include <driversGPIO.h>
#include <funcUART.h>
#include <Regs_LPC176x.h>


#ifndef DRIVERSUART_H_
#define DRIVERSUART_H_
//DEFINES PUERTOS
#define TXUART0 0,2
#define RXUART0 0,3
//PROTOTIPOS DE FUNCIONES
void InitUART0(void);
void UART0_StartTx(void);
uint8_t PopTx(void);
void PushRx(uint8_t dato);

#endif /* DRIVERSUART_H_ */
