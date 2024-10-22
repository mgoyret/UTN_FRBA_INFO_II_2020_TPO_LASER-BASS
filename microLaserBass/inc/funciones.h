/**
 * \file            funciones.h
 * \brief           TPO Informatica 2
 * \author          Grupo 7
 * \date            December, 2020
 */
#ifndef FUNCIONES_H_
#define FUNCIONES_H_

//Headers
#include <driversCuerdasyTrastes.h>
#include <driversPLL.h>
#include <funcUART.h>
#include <funcMaqTimer.h>

//!< Definicion de Estados de MdeGeneral
#define	INICIO		    0
//corresponde a la deteccion de la cuerda al aire
#define	DETECTANDO		1
#define	TOCA_CAIRE		2
#define	TOCA_TRASTE		3
//Definicion de eventos de Maq de timers
//TDCA(Timers de Deteccion de Cuerda al Aire)
//TAC(Timers de Apagado de Cuerda)
//TAT(Timers de Apagado de Traste)
#define TDCA0 0
#define TAT0  1
#define TAC0  2
#define TDCA1 3
#define TAT1  4
#define TAC1  5
#define TDCA2 6
#define TAT2  7
#define TAC2  8
#define TDCA3 9
#define TAT3  10
#define TAC3  11
//tiempo de timers (mseg)
#define TIMETAC 1000
#define TIMETAT  100
#define TIMETDCA 100
//OTROS DEFINES
#define SIN_TRASTE 0
//---PROTOTIPOS DE FUNCIONES-----------------

void maquina_MdEGral(uint8_t cuerda);
void inicializacion(void);

//LECTURA ENTRADAS
uint8_t getTrastes(uint8_t cuerda);
uint8_t getLdrs(uint8_t cuerda);
//TIMERS
void IniciarTimer(uint8_t evento);
void apagarTimers(uint8_t cuerda);
void funcTAC(void);
void funcTAT(void);
void funcTDCA(void);
#endif /* FUNCIONES_H_ */
