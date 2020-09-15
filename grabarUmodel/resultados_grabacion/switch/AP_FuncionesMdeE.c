/**
*	\file AP_FuncionesMde.c
*	\brief Implementacion switch-case
*	\details Descripcion detallada del archivo
*	\author marcosgoyret
*	\date 15-09-2020 17:00:19
*/

/*********************************************************************************************************************************
 *** INCLUDES
**********************************************************************************************************************************/
#include "AP_FuncionesMdeE.h" 
#include "AP_Depuracion.h" 

extern int flag;
extern int timer_0_25;
extern int notaTocada;
extern int contador;

void inicializar(void)
{
	reset();
}
void reset(void)
{
	notaTocada = FALSE;
	flag = FALSE;
	contador = 0;
	timer_0_25 = FALSE;
}

/**
*	\fn void iniciarTimer_0_25(void)
*	\brief inicializa un timer de 250ms
*	\details Detalles
*	\author marcosgoyret
*	\date 15-09-2020 17:00:19
*/
void iniciarTimer_0_25( void )
{
	//!< Codigo propio de la funcion
}

/**
*	\fn void timer_0_25_handler(void)
*	\brief Se ejecuta al "sonar" el timer de 250ms, y actualiza la variable
*	\details Detalles
*	\author marcosgoyret
*	\date 15-09-2020 17:00:19
*/
void timer_0_25_handler( void )
{
	timer_0_25 = TRUE;
}

/**
*	\fn int notaRecibida(void)
*	\brief Devuelve false si no hay ninguna nota tocada, y en caso contrario devuelve la nota
*	\details Detalles
*	\author marcosgoyret
*	\date 15-09-2020 17:00:19
*/
int notaRecibida( void )
{
	int res = FALSE;

	//!< Codigo propio de la funcion
	/* Si hay algo para leer del puerto, va a ser la nota tocada,
		la asigno a res */

	return res;
}


/**
*	\fn void guardarNota(void)
*	\brief guarda la nota tocada en el archivo
*	\details Detalles
*	\author marcosgoyret
*	\date 15-09-2020 17:00:19
*/
void guardarNota( void )
{
	//!< Codigo propio de la funcion
	addNote(contador, notaTocada);
	contador++;
}

