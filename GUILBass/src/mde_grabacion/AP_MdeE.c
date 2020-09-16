/**
*	\file AP_MdeE.c
*	\brief Implementacion switch-case
*	\details Descripcion detallada del archivo
*	\author marcosgoyret
*	\date 15-09-2020 17:00:19
*/

/*********************************************************************************************************************************
 *** INCLUDES
**********************************************************************************************************************************/
#include "../../inc/mde_grabacion/AP_MdeE.h"
#include "../../inc/mde_grabacion/AP_FuncionesMdeE.h"

/* La variable flag es para que al estar dentro del intervalo de 250ms, se tome
	la primera nota tocada en caso de que se toquen dos sin que se termine el intervalo */
extern int flag;
extern int timer_0_25;
extern int notaTocada;
extern int contador;
extern int grabacion;

/**
*	\fn void maquina_grabador()
*	\brief Implementacion switch-case
*	\details 
*	\author marcosgoyret
*	\date 15-09-2020 17:00:19
*/
void maquina_grabador(FILE* fp)
{
	static int estado = LEYENDO;
	switch(estado)
	{
		case LEYENDO:
		
			/* notaRecibida() devuelve 0 solo si no hay nueva nota */
			if(notaRecibida() && (flag == FALSE))
			{
				#ifdef DEPURAR
					Log( 0 , 0 , 1 );
				#endif
				notaTocada = notaRecibida();
				flag = TRUE;

				estado = LEYENDO;	
			}

			if( timer_0_25 )
			{
				#ifdef DEPURAR
					Log( 0 , 0 , 0 );
				#endif
                guardarNota(fp);
				//contador++; en la mde esta aca, pero lo meti dentro de guardarNota()
				//Reseteo estas variables para la siguiente vuelta
				notaTocada = FALSE;
				flag = FALSE;

				estado = PROCESANDO;	
			}

			break;
		
		case PROCESANDO:
		
			if( notaTocada == FALSE ) //siempre se da, este estado en si es solo de paso
			{
				#ifdef DEPURAR
					Log( 0 , 1 , 0 );
				#endif
				iniciarTimer_0_25();

				estado = LEYENDO;	
			}

			break;
		
		default: reset();
			break;
	}
}


/*
void maquina_principal(FILE* fp)
{
	static int estado = ESPERANDO;
	switch (estado)
	{
	case ESPERANDO:

		if ( grabacion )
		{
			estado = GRABANDO;	
		}
		break;
	
	case GRABANDO:

		if( !grabacion )
		{
			estado = ESPERANDO;
		}else // aca convenia hacer un else, asi si justo precionaron el boton detener, no se mete en la mde_grabar
		{
            maquina_grabador(fp); //maquina compuesta
		}

		break;

	default: estado = ESPERANDO;
		break;
	}

}
*/
