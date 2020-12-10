
/************************************************************************************************************************************
 * La Redistribuci�n y uso en formas de fuente y objeto con o sin modificaci�n, est�n permitidos siempre que se cumplan las 
 * siguientes condiciones:
 *
 * 1. Las redistribuciones del c�digo fuente deben conservar el aviso de copyright anterior, esta lista de condiciones y el siguiente
 * descargo de responsabilidad.
 *
 * 2. Las redistribuciones en formato objeto deben reproducir el aviso de copyright anterior, esta lista de condiciones y la siguiente
 * exenci�n de responsabilidad en la documentaci�n y / u otros materiales proporcionados con la distribuci�n.
 *
 * 3. Ni el nombre del titular de los derechos de autor ni los nombres de sus los contribuyentes pueden ser utilizados para respaldar 
 * o promocionar productos derivados de este software sin permiso escrito previo espec�fico.
 *
 * ESTE SOFTWARE ES PROPORCIONADO POR LOS TITULARES DE LOS DERECHOS DE AUTOR Y SUS COLABORADORES de uModelFactor y Y SE RENUNCIA 
 * A CUALQUIER GARANT�A EXPRESA O IMPL�CITA, INCLUIDAS, ENTRE OTRAS, LAS GARANT�AS IMPL�CITAS DE COMERCIABILIDAD E IDONEIDAD PARA 
 * UN PROP�SITO DETERMINADO. EN NING�N CASO EL TITULAR DE LOS DERECHOS DE AUTOR O LOS COMERCIANTES SER�N RESPONSABLES DE DA�OS DIRECTOS,
 * INDIRECTOS, INCIDENTALES, ESPECIALES, EJEMPLARES O CONSECUENCIALES (INCLUIDOS, ENTRE OTROS, LA ADQUISICI�N DE BIENES O SERVICIOS 
 * SUSTITUTIVOS, LA P�RDIDA DE USO, LOS DATOS O LAS GANANCIAS; O INTERRUPCI�N DEL NEGOCIO) SIN EMBARGO Y EN CUALQUIER TEOR�A DE 
 * RESPONSABILIDAD, YA SEA POR CONTRATO, RESPONSABILIDAD ESTRICTA O AGRAVIO (INCLUIDA LA NEGLIGENCIA O CUALQUIER OTRO) QUE SURJA DE
 * CUALQUIER MODO DEL USO DE ESTE SOFTWARE, AUN CUANDO SE ESTEVIENDO LA POSIBILIDAD DE DICHO DA�o
 *	
 * El contenido de este archivo es generado en forma automatica a partir del modelo planteado. Cualquier cambio realizado sobre el modelo
 * generara un nuevo codigo que eliminara todos los cambios realizados por el desarrollador en el fuente previamente generado
**************************************************************************************************************************************/

/**
*	\file AP_MdeE.c
*	\brief Implementacion switch-case
*	\details Descripcion detallada del archivo
*	\author Alejo
*	\date 27-10-2020 20:23:28
*/

/*********************************************************************************************************************************
 *** INCLUDES
**********************************************************************************************************************************/
#include "AP_MdeE.h" 
#include "AP_FuncionesMdeE.h" 
#include "AP_Depuracion.h" 

/*********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
**********************************************************************************************************************************/

/*********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
**********************************************************************************************************************************/

/*********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
**********************************************************************************************************************************/

/*********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
**********************************************************************************************************************************/

/*********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
**********************************************************************************************************************************/
/*********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
**********************************************************************************************************************************/

/*********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
**********************************************************************************************************************************/

/*********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
**********************************************************************************************************************************/

/*********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
**********************************************************************************************************************************/
/**
*	\fn void maquina_MdEGral()
*	\brief Implementacion switch-case
*	\details 
*	\author Alejo
*	\date 27-10-2020 20:23:28
*/
void maquina_MdEGral()
{
		static int estado = INICIO;

		switch(estado)
		{
			case INICIO:
			
				if( cuerda == ON && traste == 0( ) )
				{
					#ifdef DEPURAR
						Log( 0 , 0 , 0 );
					#endif

					iniciarTDCA();
					estado = DETECTANDO;	
				}
 
				if( cuerda == ON && traste != 0( ) )
				{
					#ifdef DEPURAR
						Log( 0 , 0 , 1 );
					#endif

					lastTraste = traste;
					noteonCCT( );
					iniciarTAT( );
					
					estado = TOCA_TRASTE;	
				}
 

				break;
			
			case DETECTANDO:
			
				if( cuerda == OFF( ) )
				{
					#ifdef DEPURAR
						Log( 0 , 1 , 0 );
					#endif

					
					estado = INICIO;	
				}
 
				if( cuerda == ON && traste == 0 && TDCA( ) )
				{
					#ifdef DEPURAR
						Log( 0 , 1 , 1 );
					#endif

					iniciarTAC( );
					noteonCA( );
					
					estado = TOCA_CAIRE;	
				}
 
				if( traste != 0 && cuerda == ON( ) )
				{
					#ifdef DEPURAR
						Log( 0 , 1 , 2 );
					#endif

					iniciarTAT( );
					iniciarTAC( );
					noteoffCCT( );
					lastTraste = traste;

					estado = TOCA_TRASTE;	
				}
 

				break;
			
			case TOCA_CAIRE:
			
				if( traste == 0 && cuerda == ON && !TAC( ) )
				{
					#ifdef DEPURAR
						Log( 0 , 2 , 0 );
					#endif

					iniciarTAC();
					estado = TOCA_CAIRE;	
				}
 
				if( traste != 0 && cuerda == ON && !TAC( ) )
				{
					#ifdef DEPURAR
						Log( 0 , 2 , 1 );
					#endif

					noteonCCT( );
					iniciarTAT( );
					iniciarTAC( );
					noteoffCA( );
					
					estado = TOCA_TRASTE;	
				}
 
				if( TAC( ) )
				{
					#ifdef DEPURAR
						Log( 0 , 2 , 2 );
					#endif

					noteoffCA();
					estado = INICIO;	
				}
 

				break;
			
			case TOCA_TRASTE:
			
				if( TAT || TAC( ) )
				{
					#ifdef DEPURAR
						Log( 0 , 3 , 0 );
					#endif

					noteonCCT();
					estado = INICIO;	
				}
 
				if( !TAT && !TAC && cuerda == ON( ) )
				{
					#ifdef DEPURAR
						Log( 0 , 3 , 1 );
					#endif

					iniciarTAC();
					estado = TOCA_TRASTE;	
				}
 
				if( traste != lastTraste && traste != 0 && !TAC && !TAT( ) )
				{
					#ifdef DEPURAR
						Log( 0 , 3 , 2 );
					#endif

					iniciarTAT( );
					noteoffCCLT( );
					noteonCCT( );
					lastTraste = traste;

					estado = TOCA_TRASTE;	
				}
 
				if( !TAT && !TAC && traste == lastTraste( ) )
				{
					#ifdef DEPURAR
						Log( 0 , 3 , 3 );
					#endif

					iniciarTAT();
					estado = TOCA_TRASTE;	
				}
 

				break;
			
			default: estado = INICIO;
		}


}

