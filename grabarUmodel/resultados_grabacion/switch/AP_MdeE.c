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
#include "AP_MdeE.h" 
#include "AP_FuncionesMdeE.h" 
#include "AP_Depuracion.h" 

/* La variable flag es para que al estar dentro del intervalo de 250ms, se tome
	la primera nota tocada en caso de que se toquen dos sin que se termine el intervalo */
extern int flag;
extern int timer_0_25;
extern int notaTocada;
extern int contador;

/**
*	\fn void maquina_principal()
*	\brief Implementacion switch-case
*	\details 
*	\author marcosgoyret
*	\date 15-09-2020 17:00:19
*/
void maquina_principal()
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
				guardarNota( );
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
		
		default: estado = LEYENDO;
	}
}

