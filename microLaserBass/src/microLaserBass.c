/*
===============================================================================
 Name        : microLaserBass.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include "funciones.h"

int main(void) {
	//uint8_t aux;
	uint8_t cuerda;
	//uint8_t ltwo,lthree,lfour;
 	inicializacion();
 	//prueba
 	/*PrenderLedRed();
  	ApagarLedRed();
 	PrenderLedBlue();
   ApagarLedBlue();
   PrenderLedGreen();
   ApagarLedGreen();
	    while(1) {
	    	aux=getPin(LDR1);
	    	if(aux==ON)
	    	{
	    		PrenderLedRed();
	    		ApagarLedBlue();

	    		ltwo=getPin(LDR2);
	    		while(ltwo==OFF){
	    			ltwo=getPin(LDR2);
	    		}
	    		ApagarLedBlue();
	    	   PrenderLedRed();
	    	   lthree=getPin(LDR3);
				while(lthree==OFF){
					lthree=getPin(LDR3);
				}
				PrenderLedRed();
				ApagarLedBlue();
				lfour=getPin(LDR4);
				while(lfour==OFF){
					lfour=getPin(LDR4);
				}

	    	}
	    	if(aux==OFF){
	    		PrenderLedBlue();
	    		ApagarLedRed();
	    		PrenderLedGreen();
	    	}*/
 	        while(1){
 	        	timerEvent();
 	        	for(cuerda=0;cuerda<4;cuerda++)
 	        		maquina_MdEGral(cuerda);
 	        		//maquina_Cserie(void);
 	         }
	   // }
	    return 0 ;
}
