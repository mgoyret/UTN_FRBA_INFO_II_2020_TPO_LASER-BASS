/**
 * \file            funcUART.c
 * \brief           TPO Informatica 2
 * \author          Grupo 7
 * \date            December, 2020
 */

#include "funcUART.h"

// Flag de TX en curso
uint8_t txEnCurso;

// Buffer de Transmisión
__RW uint8_t bufferTx[BUFFER_TX_SIZE];

// Índices de Transmisión
__RW uint8_t tx_in = 0, tx_out = 0;

/**
 *\fn     void PushTx(uint8_t dato)
 *\brief  Pone el dato a enviar en el buffer
 *\details ademas inicia la transmision TX sino hay niguna en transcurso
 *\param  dato dato a enviar
 *\return void
*/
void PushTx(uint8_t dato)
{

	bufferTx[tx_in] = dato;
	//aumento el indice y si pasa el
	//maximo sobrescribo la 1era posicion
	tx_in++;
	tx_in %= BUFFER_TX_SIZE;

	//si no había una TX en curso,fuerzo el inicio de la TX
	if (txEnCurso == 0) {
		txEnCurso = 1;
		UART0_StartTx();
	}
}


/**
 *\fn     void mandarnota(uint8_t tipo,uint8_t cuerda,uint8_t traste)
 *\brief  Manda el NOTEON o NOTEOFF
 *\details
 *\param  tipo  si es NOTEON o NOTEOFF
 *\param cuerda
 *\param traste
*\return void
*/
void mandarnota(uint8_t tipo,uint8_t cuerda,uint8_t traste){
	char nota;
	uint8_t aux=0;
	//modificamos el orden de los traste por un criterio musical
	/*
	 *       0     6 5 4 3 2 1
	 *  ---------
	 * |         |____________
	 * |  |   |                |
	 * |  |   |   _____________|
	 * |         |
	 *  ---------
	 * */
	if(traste==0)
	{
		nota=7*cuerda +1;
	}else
	{
		nota = 7*cuerda +7 -traste +1;
	}

	if(tipo == NOTEOFF)
	{
		nota=-nota;
	}
	//los primeros bit 1010
	aux|=(10<<4);
	aux|=(nota >> 4);
	PushTx(aux);
	//los primeros bit 0101
	aux=0;
	aux|=5;
	aux|=((nota & 15)<<4);
	PushTx(aux);
}
