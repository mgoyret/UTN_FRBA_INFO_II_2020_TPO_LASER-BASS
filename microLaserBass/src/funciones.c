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
//Buffer con el cual el handler identifica el evento que lo llamo
//Con este flag se evita hacer 9 handler que son similares
__RW  uint8_t handlerEvent;

//Flag con el cual la MdE sabe si el timer se disparo
static uint8_t timer[N_TIMERS]={};


/**
*	\fn 		void maquina_MdEGral(uint8_t cuerda)
*	\brief 	    Maquiana de estado del microcpntrolador
*	\details 	Hay una instancia por cada cuerda
*	\param 	    cuerda	cuerda a la que corresponde la isntancia de la MdE
*	\return 	void
*/
void maquina_MdEGral(uint8_t cuerda)
 {
		//Estado actual de las instancias
		static uint8_t estado[] = {INICIO,INICIO,INICIO,INICIO};
		//Valor del ultimo traste tocado
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
					apagarTimers(cuerda);
				}

				if( getLdrs(cuerda)==ON && getTrastes(cuerda)==SIN_TRASTE && timer[TDCA0+cuerda*3])
				{
					timer[TDCA0+cuerda*3] = FALSE;
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
					timer[TAC0+cuerda*3] = FALSE;
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
					timer[TAC0+cuerda*3] = FALSE;
					timer[TAT0+cuerda*3] = FALSE;
					mandarnota(NOTEOFF,cuerda,lastTraste[cuerda]);
					apagarTimers(cuerda);
					estado[cuerda] = INICIO;
				}
				break;

			default: estado[cuerda] = INICIO;

		}


}



/**
*	\fn 		void inicializacion(void)
*	\brief 	    Incializa registros y pines
*	\details
*	\param 	    void
*	\return 	void
*/
void inicializacion(void){
	 init_gpio();
	 // hay que poneslo xq utilizamos systick
     init_PLL();
     InitUART0();
	 init_systick();
	 setPin(C1,ON);
	 setPin(C2,ON);
	 setPin(C3,ON);
	 setPin(C4,ON);
}



//----------------CUERDAS Y TRASTES-------------------------------

/**
*	\fn 		uint8_t getTrastes(uint8_t cuerda)
*	\brief 	    devuelve el traste actual de la cuerda
*	\details
*	\param 	    cuerda
*	\return 	uint8_t traste tocado
*/
uint8_t getTrastes(uint8_t cuerda){
	uint8_t aux = NO_TRASTE;

	if(traste[cuerda]!= NO_TRASTE){
		aux=traste[cuerda];
	}
	return aux;
}
/**
*	\fn 		uint8_t getTrastes(uint8_t cuerda)
*	\brief 	    devuelve estado del ldr
*	\details	Si al ldr le llega el haz devuelve NO_LDR y sino
*	\details    devuelve un SI_LDR esto es asi xq se toca cuerda
*	\details    cuando se corta el haz
*	\param 	    cuerda
*	\return 	uint8_t si al ldr le llega el haz o no
*/
uint8_t getLdrs(uint8_t cuerda){
	// CQ A MI ME INTERESE CUANDO SE CORTA EL HAZ
	uint8_t aux = NO_LDR;

	if(ldrs[cuerda]== NO_LDR){
		aux=SI_LDR;
	}
	return aux;
}


//-----------------TIMERS--------------------


/**
*	\fn 		void apagarTimers(uint8_t cuerda)
*	\brief 	    apaga todos los timers de la cuerda indicada
*	\details
*	\param 	    cuerda
*	\return 	void
*/
void apagarTimers(uint8_t cuerda){
	uint8_t i;
	for(i=cuerda*3;i<(3+cuerda*3);i++){
			timerStop(i);
			timer[i]=0;
	}
}

/**
*	\fn 		void IniciarTimer(uint8_t evento)
*	\brief 	    inicia un timer
*	\details
*	\param 	    evento correspondiente al timer q se quiere iniciar
*	\return 	void
*/
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
/**
*	\fn 		void funcTAC(void)
*	\brief 	    handler de los TAC(Timers de Apagado de Cuerda)
*	\details
*	\param 	    void
*	\return 	void
*/
void funcTAC(void){
	timer[handlerEvent]=1;
}
/**
*	\fn 		void funcTAT(void)
*	\brief 	    handler de los TAT(Timers de Apagado de Traste)
*	\details
*	\param 	    void
*	\return 	void
*/
void funcTAT(void){
	timer[handlerEvent]=1;
}
/**
*	\fn 		void funcTDCA(void)
*	\brief 	    handler de los TDCA(Timers de Deteccion de Cuerda al Aire)
*	\details
*	\param 	    void
*	\return 	void
*/
void funcTDCA(void){
	timer[handlerEvent]=1;
}

