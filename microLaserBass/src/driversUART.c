/**
 * \file            driversUART.c
 * \brief           TPO Informatica 2
 * \author          Grupo 7
 * \date            December, 2020
 */

#include "driversUART.h"


// Flag de TX en curso
extern __RW uint8_t txEnCurso;
// Índices de Transmisión
extern __RW uint8_t tx_in, tx_out;
// Buffer de Transmisión
extern __RW uint8_t bufferTx[BUFFER_TX_SIZE];


/**
 *\fn     void UART0_IRQHandler (void)
 *\brief  handler de UART
 *\details
 *\param  void
 *\return void
*/
void UART0_IRQHandler (void)
{
	uint8_t iir, dato;
	do {
		//Para limpiar los flags de IIR hay que leerlo, una vez que lo leí se resetea.
		iir = U0IIR;
		//THRE (Interrupción por TX) --THR disponible -> b1=1
		if (iir & 0x02) {
			dato=PopTx();
			if(dato>0){
				U0THR=dato;
			}else {
				// si no hay más datos a enviar, limpio el flag
				txEnCurso = 0;
			}
		}
	} while(!(iir & 0x01));	/* me fijo si cuando entre a la ISR habia otra
						    int. pendiente de atencion: b0=0 */
}
/**
*\fn     void UART0_StartTx(void)
*\brief  Pongo dato para transmitir en U0THR
*\details Esto lo hago porque la interrupcion se
*\details hace cuando se manda el dato , entonces si no
*\details pongo ningun dato en U0THR no va interrupir nunca
*\param  void
*\return void
*/
void UART0_StartTx(void)
{
	uint8_t dato;

	dato = bufferTx[tx_out];
	tx_out++;
	tx_out %= BUFFER_TX_SIZE;
	// transmito el dato
	U0THR = dato;
}
/**
*\fn     void InitUART0 (void)
*\brief  Inicializo el UART0
*\details Esto lo hago porque la interrupcion se
*\param  void
*\return void
*/
void InitUART0 (void)
{
	//1.- Registro PCONP - bit 3 en 1 habilita la UART0
	PCONP |= 0x01<<3;
	//2.- Registro PCLKSEL0 - bits 6 y 7 en 0 seleccionan que el clk de la UART0 sea 25MHz
	PCLKSEL0 &= ~(0x03<<6);
	//3.- Registro U0LCR - trama 8 bits, 1 bit stop, sin paridad, sin break cond. (bit DLAB = 1)
	U0LCR = 0x83;
	//4.- Registros U1DLL (0x40010000) y U1DLM (0x40010004) - 9600 baudios
	U0DLM = 0;
	U0DLL = 0xA3;
	//5.- Habilito las funciones especiales de los pines TX y RX
	//TX0D : PIN ??	-> 	P0[2]
	setPinsel( TXUART0, PINSEL_FUNC1);
	//RX0D : PIN ??	-> 	P0[3]
	setPinsel( RXUART0, PINSEL_FUNC1);
	//6.- Registro U1LCR, pongo DLAB en 0
	U0LCR = 0x03;
	//7. Habilito las interrupciones de RX y TX en la UART0 (Registro U0IER)
	U0IER = 0x03;
	//8. Habilito la interrupción de la UART0 en el NVIC (Registro ISER0)
	ISER0 |= (1<<5);
}

/**
 *\fn     uint8_t PopTx(void)
 *\brief  Saco el dato a enviar en el buffer
 *\details ademas inicia la transmision TX sino hay niguna en transcurso
 *\param  dato dato a enviar
 *\return void
*/
uint8_t PopTx(void)
{
	int aux=0;
	if(tx_in!=tx_out){
		aux = bufferTx[tx_out];
		tx_out++;
		tx_out %= BUFFER_TX_SIZE;
	}
	return aux;
}
