
#include "funciones.h"

//buffer de traste
//C1 es 0 , C2 es 1 , C3 es 2 y C4 es 3
__RW uint8_t  traste[4];
//LDR1 es 0 .....
__RW uint8_t ldrs[4];
//buffer para  que el handler identifique el evento
__RW  uint8_t handlerEvent;


static uint8_t timer[N_TIMERS]={};//son 12 timers
/*variables para notas compuestas
static uint8_t enviarNota[4]={};
static uint8_t modoNota[4]={};
*/
void maquina_MdEGral(uint8_t cuerda)
 {
		static uint8_t estado[] = {INICIO,INICIO,INICIO,INICIO};
		static uint8_t lastTraste[] = {NO_TRASTE,NO_TRASTE,NO_TRASTE,NO_TRASTE};
		switch(estado[cuerda])
		{
			case INICIO:

				if( getLdrs(cuerda) == ON && getTrastes(cuerda) == 0)
				{
					IniciarTimer(TDCA0+cuerda*3);
					estado[cuerda] = DETECTANDO;
					//PushTx(48+cuerda);
  					//enviarString("DETECT_");
				}

				if( getLdrs(cuerda)== ON && getTrastes(cuerda) != 0)
				{
					lastTraste[cuerda] = getTrastes(cuerda) ;
					mandarnota(NOTEON,cuerda,lastTraste[cuerda]);
					IniciarTimer(TAT0+cuerda*3);
					estado[cuerda] = TOCA_TRASTE;
					//PushTx(48+cuerda);
					//enviarString("T_TRASTE");
					//PushTx(48+lastTraste[cuerda]);
				}


				break;

			case DETECTANDO:

				if( getLdrs(cuerda) == OFF )
				{
					estado[cuerda] = INICIO;
					//PushTx(48+cuerda);
					//enviarString("INICIO_");
					apagarTimers(cuerda);
					//apagar los timers y los mismo para los otros casos cuando vuelvo a incio
				}

				if( getLdrs(cuerda) == ON && getTrastes(cuerda)  == 0 && timer[TDCA0+cuerda*3] == 1)
				{
					timer[TDCA0+cuerda*3] = 0;
					IniciarTimer(TAC0+cuerda*3);
					mandarnota(NOTEON,cuerda,CUERDAAIRE);
					estado[cuerda] = TOCA_CAIRE;
					//PushTx(48+cuerda);
					//enviarString("TCAIRE_");
				}

				if( getTrastes(cuerda)  != 0 && getLdrs(cuerda) == ON)
				{
					IniciarTimer(TAT0+cuerda*3);
					lastTraste[cuerda]  = getTrastes(cuerda) ;
					mandarnota(NOTEON,cuerda,lastTraste[cuerda]);
					estado[cuerda] = TOCA_TRASTE;
					//PushTx(48+cuerda);
					//enviarString("TTRASTE_");
					//PushTx(48+lastTraste[cuerda]);
				}


				break;

			case TOCA_CAIRE:

				if( getTrastes(cuerda) == 0 && getLdrs(cuerda) == ON && timer[TAC0+cuerda*3] == 0)
				{
					IniciarTimer(TAC0+cuerda*3);
					estado[cuerda] = TOCA_CAIRE;
					//enviarString(cuerda);
					//enviarString("REINICOTAC");
				}

				if( getTrastes(cuerda)  != 0 && getLdrs(cuerda) == ON && timer[TAC0+cuerda*3] == 0)
				{
					IniciarTimer(TAT0+cuerda*3);
					IniciarTimer(TAC0+cuerda*3);
					mandarnota(NOTEOFF,cuerda,CUERDAAIRE);
					lastTraste[cuerda] = getTrastes(cuerda);
				    mandarnota(NOTEON,cuerda,lastTraste[cuerda]);
					estado[cuerda] = TOCA_TRASTE;
					//PushTx(48+cuerda);
					//enviarString("TTRASTE_");
					//PushTx(48+lastTraste[cuerda]);
				}

				if( timer[TAC0+cuerda*3] == 1)
				{
					timer[TAC0+cuerda*3] = 0;
					mandarnota(NOTEOFF,cuerda,CUERDAAIRE);
					estado[cuerda] = INICIO;
					//PushTx(48+cuerda);
					//enviarString("INICIO_");
					apagarTimers(cuerda);
				}


				break;

			case TOCA_TRASTE:



				if( timer[TAT0+cuerda*3] == 0 && timer[TAC0+cuerda*3] == 0 && getLdrs(cuerda)== ON)
				{
					IniciarTimer(TAC0+cuerda*3);
 					estado[cuerda] = TOCA_TRASTE;
					//enviarString(cuerda);
					//enviarString("REINICIOTAC");
				}

				if( getTrastes(cuerda) != lastTraste[cuerda]  && getTrastes(cuerda)!= 0 && timer[TAC0+cuerda*3] == 0 && timer[TAT0+cuerda*3] == 0 )
				{
					IniciarTimer(TAT0+cuerda*3);
					mandarnota(NOTEOFF,cuerda,lastTraste[cuerda]);
					lastTraste[cuerda]  = getTrastes(cuerda);
					mandarnota(NOTEON,cuerda,lastTraste[cuerda]);

					estado[cuerda] = TOCA_TRASTE;
					//PushTx(48+cuerda);
					//enviarString("cambiodeTraste_");
				}

				if( timer[TAC0+cuerda*3] == 0 && timer[TAT0+cuerda*3] == 0 && getTrastes(cuerda)  == lastTraste[cuerda] )
				{
					IniciarTimer(TAT0+cuerda*3);
					estado[cuerda] = TOCA_TRASTE;
					//enviarString(cuerda);
					//enviarString("reinicoTAT");
				}
				if( timer[TAT0+cuerda*3] == 1 || timer[TAC0+cuerda*3] == 1)
				{
					timer[TAC0+cuerda*3] = 0;
					timer[TAT0+cuerda*3] = 0;
					mandarnota(NOTEOFF,cuerda,lastTraste[cuerda]);
					estado[cuerda] = INICIO;
					//PushTx(48+cuerda);
					//enviarString("INICIO_");
					apagarTimers(cuerda);
				}
				break;

			default: estado[cuerda] = INICIO;
				     //PushTx(48+cuerda);
					 //enviarString("RESET");
		}


}
/*maquina para enviar notas compuestas
maq_Cserie(void){
	static uint8_t estado=REPOSO;
	uint8_t i,aux=0;
	enviarNota[4]={};
	modoNota[4]={};
	switch(estado)
	{
		case REPOSO:
		for(i=0;i<4;i++){
			if(modoNota[i]==NOTEON)
				aux+=1;
		}
		if(aux==0){
			estado=REPOSO;
		}else if(aux==1){
			for(i=0;i<4;i++){
				if(modoNota[i]==NOTEON)
					mandarnota(NOTEON,i,enviarNota[i]);
			}
			estado=NOTASIMPLE;
		}else{
			//por el momento solo usamos notas simples
			for(i=0;i<4;i++){
				if(modoNota[i]==NOTEON)
					mandarnota(NOTEON,i,enviarNota[i]);
			}
			estado=NOTACOMPUESTA;
		}
		break;
		case NOTASIMPLE:
			for(i=0;i<4;i++){
				if(modoNota[i]==NOTEOFF)
					mandarnota(NOTEOFF,i,enviarNota[i]);
				}
			}
		break;
		default: estado[cuerda] = REPOSO;

}


*/





void inicializacion(void){
	 init_gpio();
     init_PLL();
     InitUART0();
	 init_systick();
	 ApagarLedGreen();
	 ApagarLedBlue();
	 ApagarLedRed();
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

//LEDS(ESTOY SE SACA DESPUES)


void ApagarLedRed(void) {
  setPin(LED_RED,OFF);
}
void PrenderLedRed(void) {
  setPin(LED_RED,ON);
}
void ApagarLedGreen(void) {
  setPin(LED_GREEN,OFF);
}
void PrenderLedGreen(void) {
  setPin(LED_GREEN,ON);
}
void ApagarLedBlue(void) {
  setPin(LED_BLUE,OFF);
}
void PrenderLedBlue(void) {
  setPin(LED_BLUE,ON);
}

void enviarString(char * palabra){
	uint32_t i;
	for(i=0;i<strlen(palabra);i++)
		PushTx(palabra[i]);
}
