/**
*	\file AP_FuncionesMdeE.h
*	\brief Resumen del archivo
*	\details Descripcion detallada del archivo
*	\author marcosgoyret
*	\date 15-09-2020 17:00:19
*/
/*********************************************************************************************************************************
*** MODULO
**********************************************************************************************************************************/
#ifndef INC_AP_FUNCIONESMDEE_H_
#define INC_AP_FUNCIONESMDEE_H_

/*********************************************************************************************************************************
*** PROTOTIPOS DE FUNCIONES GLOBALES
**********************************************************************************************************************************/
//!< Prototipos de Inicializacion
void inicializar(void);
void reset(void);

//!< Prototipos de Timers
void iniciarTimer_0_25( void );
void timer_0_25_handler(void);

int notaRecibida( void );
void guardarNota( void );

#endif /* INC_AP_FUNCIONESMDEE_H_ */
