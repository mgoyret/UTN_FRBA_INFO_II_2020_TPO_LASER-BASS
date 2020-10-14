/*******************************************************************************************************************************//**
 *
 * @file		DR_gpioInt.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		23 de jul. de 2017
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef DRIVERLPC_DR_GPIOINT_H_
#define DRIVERLPC_DR_GPIOINT_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "DR_tipos.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/
#define		IOINTSTATUS		(*( ( __RW uint32_t  * ) 0x40028080UL ))//!< overall Interrupt Status register
#define		P0IOINT			( ( IOInt_t  * ) 0x40028084UL )
#define		P2IOINT			( ( IOInt_t  * ) 0x400280A4UL )

#define		IO0INTSTATR 	P0IOINT->IOINTSTATR	//!< GPIO Interrupt Status for port 0 Rising Edge Interrupt
#define		IO0INTSTATF 	P0IOINT->IOINTSTATF //!< GPIO Interrupt Status for port 0 Falling Edge Interrupt
#define		IO0INTCLR	 	P0IOINT->IOINTCLR 	//!< GPIO Interrupt Clear register for port 0
#define		IO0INTENR 		P0IOINT->IOINTENR 	//!< GPIO Interrupt Enable for port 0 Rising Edge
#define		IO0INTENF	 	P0IOINT->IOINTENF  	//!< GPIO Interrupt Enable for port 0 Falling Edge

#define		IO2INTSTATR 	P2IOINT->IOINTSTATR	//!< GPIO Interrupt Status for port 2 Rising Edge Interrupt
#define		IO2INTSTATF 	P2IOINT->IOINTSTATF //!< GPIO Interrupt Status for port 2 Falling Edge Interrupt
#define		IO2INTCLR	 	P2IOINT->IOINTCLR 	//!< GPIO Interrupt Clear register for port 2
#define		IO2INTENR 		P2IOINT->IOINTENR  	//!< GPIO Interrupt Enable for port 2 Rising Edge
#define		IO2INTENF	 	P2IOINT->IOINTENF  	//!< GPIO Interrupt Enable for port 2 Falling Edge


/** Overall Interrupt Status register bits
 *		0 There are no pending interrupts on Port 0 - Port 2.
 *		1 There is at least one pending interrupt on Port 0 - Port 2.
 * 31:2 Reserved.
 */
#define		P0INT			( IOINTSTATUS & 1)
#define		P2INT			(( IOINTSTATUS >> 1) & 1)

#define		RISING_EDGE				0
#define		FALLINF_EDGE			1
#define		RISING_FALLINF_EDGE		2

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/
/** Registros de interrupcion de GPIO
 * Port 0 y Port 2
 * Comparte la Interrupcion externa 3 (EINT3).
  */
typedef struct
{
	__RW uint32_t	IOINTSTATR;
	__RW uint32_t 	IOINTSTATF;
	__RW uint32_t 	IOINTCLR;
	__RW uint32_t 	IOINTENR;
	__RW uint32_t 	IOINTENF;

} IOInt_t;
/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void GPIOINT_Inicializacion ( uint8_t , uint8_t , uint8_t );

#endif /* DRIVERLPC_DR_GPIOINT_H_ */
