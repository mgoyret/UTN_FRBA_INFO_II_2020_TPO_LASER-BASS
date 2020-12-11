/**
 * \file            driversGPIO.c
 * \brief           TPO Informatica 2
 * \author          Grupo 7
 * \date            December, 2020
 */
#include <driversGPIO.h>

/**
*	\fn 		void setPinsel(uint8_t puerto, uint8_t pin, uint8_t funcion)
*	\brief 	    Define la funcion del pin
*	\details 	Cada pin tiene cuatro funciones para elegir
*	\details 	Cada puerto tiene asignado 2 PINSEL
*	\param 	    puerto	puerto del pin
*	\param 	    pin
*	\param  	funcion funcion elegida para el pin
*	\return 	void
*/
void setPinsel(uint8_t puerto, uint8_t pin, uint8_t funcion)
{
	uint8_t offset = 0 ;

    if(pin >= 16)
    {
        pin = pin - 16;
        offset = 1 ;
    }
    PINSEL[2*puerto + offset] &= ( ~( 3 << (2*pin) ) );
    PINSEL[2*puerto +offset] |=  ( funcion << (2*pin) );

}
/**
\fn 		void setPinMode(uint8_t puerto, uint8_t pin, uint8_t mode)
\brief 	    Define el tipo de entrada asociada
\details 	Cada pin tiene cuatro tipo de entrada para elegir
\details 	Cada puerto tiene asignado 2 PINMODE
\param 	    puerto	puerto del pin
\param 	    pin
\param  	mode 	modo de la entrada elegido para el pin
\return 	void
*/
void setPinMode(uint8_t puerto, uint8_t pin, uint8_t mode){
	uint8_t offset = 0 ;

	if(pin >= 16)
	{
		pin = pin - 16;
		offset = 1 ;
	}
	PINMODE[2*puerto + offset] &= ( ~( 3 << (2*pin) ) );
	PINMODE[2*puerto +offset] |=( mode << (2*pin) );
}
/**
\fn 		void setPinMode(uint8_t puerto, uint8_t pin, uint8_t mode)
\brief 	    Define el tipo de salida asociada
\details 	Cada pin tiene cuatro tipo de entrada para elegir
\details 	Cada puerto tiene asignado un PINMODE_OD
\param 	    puerto	puerto del pin
\param 	    pin
\param  	mode 	modo de la salida elegido para el pin
\return 	void
*/
void setPinMode_OD(uint8_t puerto, uint8_t pin, uint8_t mode){
	PINMODE_OD[puerto] &= ( ~( 1 << pin));
	PINMODE_OD[puerto] |=( mode << (pin) );
}
/**
\fn 		uint8_t getPin(uint8_t puerto, uint8_t pin)
\brief 	    Leo el estado del pin
\param 	    puerto	puerto del pin
\param 	    pin
\return 	uint8_t devuelve el estado del pin
*/
uint8_t getPin(uint8_t puerto, uint8_t pin)
{

	return (uint8_t) ( (GPIO_BASE[8*puerto + 5] >> pin) & 1 );
}

/**
\fn 		void setPin(uint8_t puerto, uint8_t pin, uint8_t estado)
\brief 	    Define el estado del pin
\param 	    puerto	puerto del pin
\param 	    pin
\return 	void
*/
void setPin(uint8_t puerto, uint8_t pin, uint8_t estado)
{
    if(estado == ON)
    {
        //accedo al puerto y me desplaza a FIOxPIN
    	GPIO_BASE[puerto*8 + 5] |= (1 << pin) ;
    }
    else
    {
        int aux = ~(1 << pin) ;
        GPIO_BASE[puerto*8 + 5]&=   aux  ;
    }

}
/**
\fn 		void setDir(uint8_t puerto,uint8_t pin,uint8_t estado)
\brief 	    Define la direccion del pin (entrada o salida)
\param 	    puerto	puerto del pin
\param 	    pin
\return 	void
*/
void setDir(uint8_t puerto,uint8_t pin,uint8_t estado)
{
	GPIO_BASE[puerto*8]&= ~(1 << pin);
	GPIO_BASE[puerto*8]|= estado << pin;
}
