#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <driversGenerales.h>
#include <driversPLL.h>
#include <driversSystick.h>
#include <funcUART.h>
#include <funcMaqTimer.h>
//solo para la prueba
#include <string.h>
//!< Definicion de Estados
#define	INICIO		    0
#define	DETECTANDO		1
#define	TOCA_CAIRE		2
#define	TOCA_TRASTE		3
//eventos timers
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
//timers
#define TIMETAC 1000 //poner tiempo en mseg para cada uno
#define TIMETAT  100
#define TIMETDCA 100
//otros
#define SIN_TRASTE 0
//---PROTOTIPODEFUNCIONES-----------------


// Declaracion de la Maquina de MEstados
void maquina_MdEGral(uint8_t cuerda);
/*
void maquina_Cserie(void);*/
void inicializacion(void);
//LEDS PRUEBA (ESTO SE SACA DESPUES)
void ApagarLedBlue(void);
void PrenderLedBlue(void);
void PrenderLedRed(void);
void ApagarLedRed(void);
void PrenderLedGreen(void);
void ApagarLedGreen(void);
void enviarString(char * palabra);
//LECTURA HW
uint8_t getTrastes(uint8_t cuerda);
uint8_t getLdrs(uint8_t cuerda);
//TIMERS
void IniciarTimer(uint8_t evento);
void apagarTimers(uint8_t cuerda);
void funcTAC(void);
void funcTAT(void);
void funcTDCA(void);
#endif /* FUNCIONES_H_ */
