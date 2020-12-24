
#include "funcMaqTimer.h"


//BUFFER MAQUINARIA DE TIMER
//cuenta del timer
 __RW 	uint32_t TMR_Run[ N_TIMERS ];
//cuando se cumple el tiempo esta en 1
 __RW 	uint8_t  TMR_Events[ N_TIMERS ];
//handler asociado al timer
 void 	   (* TMR_Handlers [N_TIMERS]) (void);
//base de tiempo
 __RW  	uint8_t TMR_Base[ N_TIMERS ];

 //Buffer con el cual el handler identifica el evento que lo llamo
 extern __RW  uint8_t handlerEvent;
 //en handler a continuacion no las usamos en el TPO pero lo puse para practicar para el recuperatorio
 __RW uint8_t TMR_StandBy[ N_TIMERS ];

 /**
\fn 	  void TimerStart( uint8_t event, uint32_t time, void (*handler)(void) , uint8_t )
\brief 	  Inicia un timer
\details  Inicia el timer escribiendo en el buffer TMR_Run la cantidad de ciclos a
\details  contar , asignando una base y una funcion a la que llamar cuando finalize la cuenta
\param 	  event Numero de evento entre 0 y N_TIMERS
\param 	  time  tiempo del  timers en la base indicada
\param 	  handler funcion a llamar al finalizar la cuenta
\param 	  base base de tiempo
\return   void
*/

void timerStart(uint8_t event, uint32_t time, Timer_Handler handler ,uint8_t base ){
	TMR_Base[event]=base;
	if(time!=0){
		TMR_Run[event]=base*time;
		//Para asegurarnos que empieza distinto de 1
		TMR_Events[event]=0;
	}else{
		//vence atomaticamente
		TMR_Run[event]=0;
		TMR_Events[event]=1;
	}
	TMR_Handlers [event]=handler;
}

/**
\fn     void TimerStop( uint8_t event)
\brief 	Detiene el timer del evento ingresado
\details
\param  event
\return void
*/
void timerStop( uint8_t event ){
	TMR_Run[event]=0;
	TMR_Handlers [event]= NULL;
	TMR_Events[event]=0;
}


/**
\fn void TimerEvent( void )
\brief 	Chequeo de timers vencidos
\details 	Llama a los callbacks de los timers vencidos. Debe
\details 	llamarse desde el lazo principal del programa
\return 	void
*/
void timerEvent (void) {
	uint8_t i;
	for(i=0;i<N_TIMERS;i++){
		if( TMR_Events[i]){
			TMR_Events[i]=0;
			handlerEvent=i;
			TMR_Handlers[i]();
		}
	}
}
//las funciones a continuacion no las usamos en el TPO pero
//las puse para practicar para el recuperatorio
/**
\fn void TimerClose( void )
\brief 	Detiene los timers
\details 	Detiene todos los timers
\return void
*/
void TimerClose(void){
	uint8_t i;
	for(i=0;i<N_TIMERS;i++){
		timerStop(i);
	}
}
/**
	\fn  StandByTimer( uint8_t event , uint8_t accion)
	\brief Detiene/Arranca el timer, NO lo resetea
 	\details lo pone o lo saca de stand by
 	\param [in] event Numero de evento entre 0 y 31
 	\param [in] accion RUN lo arranca, PAUSE lo pone en stand by
 	\return void
*/
void StandByTimer( uint8_t event , uint8_t accion)
{
	TMR_StandBy[event] = accion;
}
/**
\fn void SetTimer( uint8_t event , uint32_t time )
\brief 	Inicia un timer
\details 	Reinicia el timer con el valor time (no lo resetea)
\param [in] 	event Numero de evento entre 0 y N_TIMERS
\param [in] 	time Tiempo del evento. Dependiente de la base de tiempos
\return 	void
*/
void SetTimer( uint8_t event , uint32_t time ){
	TMR_Run[event]=time*TMR_Base[event];
}

/**
\fn GetTimer( uint8_t event )
\brief 	Toma el valor al vuelo del timer en cuestión
\details 	Lee el timer
\param [in] 	event Numero de evento entre 0 y N_TIMERS
\return 	valor del timer
*/
uint32_t GetTimer( uint8_t event ){
	return TMR_Run[event]/TMR_Base[event];
}

