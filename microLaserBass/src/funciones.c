/**
 * \file            funciones.c
 * \brief           TPO Informatica 2
 * \author          Grupo 7
 * \date            December, 2020
 */
#include "funciones.h"
//BUFFER TRASTES
//C1 es 0 , C2 es 1 , C3 es 2 y C4 es 3
__RW uint8_t  traste[4];
//BUFFER LDRS
//LDR1 es 0 .... y LDR es 3
__RW uint8_t ldrs[4];
//buffer para  que el handler identifique el evento
__RW  uint8_t handlerEvent;


static uint8_t timer[N_TIMERS]={};//son 12 timers



void maquina_MdEGral(uint8_t cuerda)
 {
		static uint8_t estado[] = {INICIO,INICIO,INICIO,INICIO};
		static uint8_t lastTraste[] = {SIN_TRASTE,SIN_TRASTE,SIN_TRASTE,SIN_TRASTE};
		switch(estado[cuerda])
		{
			case INICIO:

				if( getTrastes(cuerda) == SIN_TRASTE && getLdrs(cuerda) == ON )
				{
					IniciarTimer(TDCA0+cuerda*3);
					estado[cuerda] = DETECTANDO;
				}

				if(  getTrastes(cuerda) != SIN_TRASTE && getLdrs(cuerda) == ON)
				{
					IniciarTimer(TAT0+cuerda*3);
					lastTraste[cuerda] = getTrastes(cuerda) ;
					mandarnota(NOTEON,cuerda,lastTraste[cuerda]);
					estado[cuerda] = TOCA_TRASTE;
				}


				break;

			case DETECTANDO:

				if( getLdrs(cuerda) == OFF )
				{
					estado[cuerda] = INICIO;
					//apagar los timers y los mismo para los otros casos cuando vuelvo a incio
					apagarTimers(cuerda);
				}

				if( getLdrs(cuerda)==ON && getTrastes(cuerda)==SIN_TRASTE && timer[TDCA0+cuerda*3])
				{
					timer[TDCA0+cuerda*3] = 0;
					IniciarTimer(TAC0+cuerda*3);
					mandarnota(NOTEON,cuerda,CUERDAAIRE);
					estado[cuerda] = TOCA_CAIRE;
				}

				if( getTrastes(cuerda)!=SIN_TRASTE && getLdrs(cuerda)==ON)
				{
					IniciarTimer(TAT0+cuerda*3);
					IniciarTimer(TAC0+cuerda*3);
					lastTraste[cuerda]  = getTrastes(cuerda);
					mandarnota(NOTEON,cuerda,lastTraste[cuerda]);
					estado[cuerda] = TOCA_TRASTE;
				}


				break;

			case TOCA_CAIRE:

				if( getTrastes(cuerda) == SIN_TRASTE && getLdrs(cuerda) == ON && !timer[TAC0+cuerda*3])
				{
					IniciarTimer(TAC0+cuerda*3);
					estado[cuerda] = TOCA_CAIRE;
				}

				if( getTrastes(cuerda)  != SIN_TRASTE && getLdrs(cuerda) == ON && !timer[TAC0+cuerda*3])
				{
					IniciarTimer(TAT0+cuerda*3);
					IniciarTimer(TAC0+cuerda*3);
					mandarnota(NOTEOFF,cuerda,CUERDAAIRE);
					lastTraste[cuerda] = getTrastes(cuerda);
				    mandarnota(NOTEON,cuerda,lastTraste[cuerda]);
					estado[cuerda] = TOCA_TRASTE;
				}

				if( timer[TAC0+cuerda*3])
				{
					timer[TAC0+cuerda*3] = 0;
					mandarnota(NOTEOFF,cuerda,CUERDAAIRE);
					apagarTimers(cuerda);
					estado[cuerda] = INICIO;
				}


				break;

			case TOCA_TRASTE:



				if( !timer[TAT0+cuerda*3] && !timer[TAC0+cuerda*3] && getLdrs(cuerda)== ON)
				{
					IniciarTimer(TAC0+cuerda*3);
 					estado[cuerda] = TOCA_TRASTE;
				}

				if( getTrastes(cuerda) != lastTraste[cuerda]  && getTrastes(cuerda)!= SIN_TRASTE && !timer[TAC0+cuerda*3] && !timer[TAT0+cuerda*3])
				{
					IniciarTimer(TAT0+cuerda*3);
					mandarnota(NOTEOFF,cuerda,lastTraste[cuerda]);
					lastTraste[cuerda]  = getTrastes(cuerda);
					mandarnota(NOTEON,cuerda,lastTraste[cuerda]);

					estado[cuerda] = TOCA_TRASTE;
				}

				if( ! timer[TAC0+cuerda*3] && !timer[TAT0+cuerda*3] && getTrastes(cuerda)  == lastTraste[cuerda] )
				{
					IniciarTimer(TAT0+cuerda*3);
					estado[cuerda] = TOCA_TRASTE;
				}
				if( timer[TAT0+cuerda*3] || timer[TAC0+cuerda*3])
				{
					timer[TAC0+cuerda*3] = 0;
					timer[TAT0+cuerda*3] = 0;
					mandarnota(NOTEOFF,cuerda,lastTraste[cuerda]);
					apagarTimers(cuerda);
					estado[cuerda] = INICIO;
				}
				break;

			default: estado[cuerda] = INICIO;

		}


}




void inicializacion(void){
	 init_gpio();
     init_PLL();
     InitUART0();
	 init_systick();
	 setPin(C1,ON);
	 setPin(C2,ON);
	 setPin(C3,ON);
	 setPin(C4,ON);
}



//----------------Entradas-------------------------------
uint8_t getTrastes(uint8_t cuerda){
	uint8_t aux = NO_TRASTE;

	if(traste[cuerda]!= NO_TRASTE){
		aux=traste[cuerda];
	}
	return aux;
}
uint8_t getLdrs(uint8_t cuerda){
//LABURO AL REVEZ CQ A MI ME INTERESE CUANDO SE CORTA EL HAZ
	uint8_t aux = NO_LDR;

	if(ldrs[cuerda]== NO_LDR){
		aux=SI_LDR;
	}
	return aux;
}


//----TIMERS----(esto porai habria que pasarlo a maq de timers pero habria q pasar las varaibles tmb)
void apagarTimers(uint8_t cuerda){
	uint8_t i;
	for(i=cuerda*3;i<(3+cuerda*3);i++){
			timerStop(i);
			timer[i]=0;
	}
}

void IniciarTimer(uint8_t evento)
{
	if(evento==TAC0 || evento==TAC1 || evento==TAC2 || evento==TAC3){
		timerStart(evento,TIMETAC,funcTAC,MSEG);
	}
    if(evento==TAT0 || evento==TAT1 || evento==TAT2 || evento==TAT3){
    	timerStart(evento,TIMETAT,funcTAT,MSEG);
    }
    if(evento==TDCA0 || evento==TDCA1 || evento==TDCA2 || evento==TDCA3){
    	timerStart(evento,TIMETDCA,funcTDCA,MSEG);
    }
}
//use una variable globlal xq me pararecio q quedaba mas prolijo
// sino se puede usar una funcion por cada evento
void funcTAC(void){
	timer[handlerEvent]=1;
}
void funcTAT(void){
	timer[handlerEvent]=1;
}
void funcTDCA(void){
	timer[handlerEvent]=1;
}

