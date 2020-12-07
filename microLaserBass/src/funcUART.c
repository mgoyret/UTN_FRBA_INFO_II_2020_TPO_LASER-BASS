/*
 * funcUART.c
 *
 *  Created on: 8 Nov 2020
 *      Author: alejo
 */

#include "funcUART.h"

// Flag de TX en curso
uint8_t txEnCurso;

// Buffer de Transmisión
__RW uint8_t bufferTx[BUFFER_TX_SIZE];
// Buffer de Recepción
__RW uint8_t bufferRx[BUFFER_RX_SIZE];

// Índices de Transmisión
__RW uint8_t tx_in = 0, tx_out = 0;
// Índices de Recepción
__RW uint8_t rx_in = 0, rx_out = 0;

void PushTx(uint8_t dato)
{
	bufferTx[tx_in] = dato;
	tx_in++;
	tx_in %= BUFFER_TX_SIZE;

	if (txEnCurso == 0) {
		txEnCurso = 1;		//si no había una TX en curso,
		UART0_StartTx();	//fuerzo el inicio de la TX
	}
}

uint32_t PopRx(void)
{
	uint32_t dato = -1; // devuelvo -1 si no hay dato

	if(rx_out != rx_in) {
		// si hay un dato disponible, lo saco del bufferRx
		dato = bufferRx[rx_out];
		rx_out++;
		rx_out %= BUFFER_RX_SIZE;
	}

	return dato;
}
void mandarnota(uint8_t tipo,uint8_t cuerda,uint8_t traste){
	char nota;
	uint8_t aux=0;
	/*
	 *        0    6 5 4 3 2 1
	 *  ---------
	 * |         |____________
	 * |                      |
	 * |         _____________|
	 * |         |
	 *  ---------
	 * */
        if (traste==0){
		nota=7*cuerda+1;
	}else{
		nota=7*cuerda +7-traste+1;
	}
	if(tipo == NOTEOFF){
		nota= -nota;
	}
	aux|=(10<<4);//los primeros bit 1010
	aux|=(nota >> 4);
	PushTx(aux);
	aux=0;
	aux|=5;//los primeros bit 0101
	aux|=((nota & 15)<<4);
	PushTx(aux);
}
