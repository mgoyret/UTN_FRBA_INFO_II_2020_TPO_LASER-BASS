
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
	TMR_Run[event]=base*time;
	//Para asegurarnos que empieza distinto de 1
	TMR_Events[event]=0;
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
}

/**
\fn void TimerEvent( void )
\brief 	Chequeo de timers vencidos
\details 	Llama a los callbacks de los timers vencidos. Debe
\details 	llamarse desde el lazo principal del programa
\return 	void
*/
void timerEvent (void) {
    int i;
	for(i=0;i<N_TIMERS;i++){
		if(TMR_Run[i]==0 && TMR_Events[i]==1){
			TMR_Events[i]=0;
			handlerEvent=i;
			TMR_Handlers[i]();
		}
	}
}
