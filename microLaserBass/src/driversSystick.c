
#include <driversSystick.h>

//buffers de maquinaria de timers
extern __RW 	uint32_t TMR_Run[ N_TIMERS ];
extern __RW 	uint8_t  TMR_Events[ N_TIMERS ];
extern void 	   (* TMR_Handlers [N_TIMERS]) (void);
//__RW  	uint8_t TMR_StandBy[ N_TIMERS ]; por ahora no lo uso
extern __RW  	uint8_t TMR_Base[ N_TIMERS ];
//buffer para  que el handler identifique el evento
extern __RW  uint8_t handlerEvent;


void SysTick_Handler(void)
{
	__RW uint32_t dummy;
	static uint8_t aux=0;
  dummy = STCTRL;
  aux++;
  if(aux==10){
	  driverLdrs();
	  driverTrastes();
	  aux=0;
  }
  analizarTimers();
}

void init_systick(void){
  STRELOAD=(STCALIB/N)-1;
  ENABLE=1;
  TICKINT=1;
  CLKSOURCE=1;
}
/**
\fn void AnalizarTimers ( void )
\brief 	Decremento periódico de los contadores
\details 	Decrementa los contadores de los timers en ejecución.
\details 	Debe ser llamada periódicamente con la base de tiempos
\return 	void
*/
void analizarTimers ( void ){
	int i;
	for(i=0;i<N_TIMERS;i++){
		if(TMR_Run[i]>1){
			TMR_Run[i]=TMR_Run[i]-1;
		}else if(TMR_Run[i]==1){
			TMR_Run[i]=TMR_Run[i]-1;
			 TMR_Events[i]=1;
		}
	}
}
// ESTO NO SE si iria en primitivas en realidad,analizar timer va en drivers pero no se si timerevent
//me fije e irian los 2 en drivers eso hicieron el proyecto de adc
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
