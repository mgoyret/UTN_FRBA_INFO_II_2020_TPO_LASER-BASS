/**
 * \file            microLaserBass.c
 * \brief           TPO Informatica 2
 * \author          Grupo 7
 * \date            December, 2020
 */
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include "funciones.h"

int main(void) {
	uint8_t cuerda;
 	inicializacion();
	while(1){
		timerEvent();
		//recorremos las 4 cuerdas
		for(cuerda=0;cuerda<4;cuerda++)
			maquina_MdEGral(cuerda);
	 }
	    return 0 ;
}
