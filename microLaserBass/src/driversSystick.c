
#include <driversSystick.h>

//BUFFER MAQUINARIA DE TIMERtiempo
//cuenta del timer
extern __RW 	uint32_t TMR_Run[ N_TIMERS ];
//cuando se cumple el tiempo esta en 1
extern __RW 	uint8_t  TMR_Events[ N_TIMERS ];
//handler asociado al timer
extern void 	   (* TMR_Handlers [N_TIMERS]) (void);
//base de tiempo
extern __RW  	uint8_t TMR_Base[ N_TIMERS ];
//en handler a continuacion no las usamos en el TPO pero lo puse para practicar para el recuperatorio
extern __RW uint8_t TMR_StandBy[ N_TIMERS ];



/**
\fn     void SysTick_Handler(void)
\brief 	Handler del systick
\details Va entrar cada x tiempo
\param  void
\return void
*/
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
/**
\fn     void init_systick(void)
\brief 	Inicializa el systick
\details Va entrar cada x tiempo
\param  void
\return void
*/
void init_systick(void){
  STRELOAD=(STCALIB/N)-1;
  //habilita el systick
  ENABLE=1;
  //habilita la interrupcion
  TICKINT=1;
  //selecciono el CPU clock  como fuente del systick
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
		//el standBy no lo usamos en proyecto lo agrege cuando practicaba para el recup
		if(TMR_StandBy[i]==RUN){
			if(TMR_Run[i]>1){
				TMR_Run[i]=TMR_Run[i]-1;
			}else if(TMR_Run[i]==1){
				TMR_Run[i]=TMR_Run[i]-1;
				 TMR_Events[i]=1;
			}
		}
	}
}

