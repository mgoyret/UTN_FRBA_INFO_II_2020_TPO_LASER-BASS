
#include <driversGenerales.h>
//buffers de las cuerdas y los trastes
extern __RW uint8_t traste[4];
extern __RW uint8_t ldrs[4];
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
/**
\fn 		void init_gpio(void)
\brief 	    Inicializo todas las entradas y salidas
\param 	    void
\return 	void
*/
void init_gpio(void)
{
	//placainterconexion (la EXP0 Y EXP1 no las usamos)
	setPinsel(LDR1,PINSEL_GPIO);
	setPinsel(LDR2,PINSEL_GPIO);
	setPinsel(LDR3,PINSEL_GPIO);
	setPinsel(LDR4,PINSEL_GPIO);
	setPinsel(EXP6,PINSEL_GPIO);
	setPinsel(EXP7,PINSEL_GPIO);
	setPinsel(EXP8,PINSEL_GPIO);
	setPinsel(EXP9,PINSEL_GPIO);
	setPinsel(EXP10,PINSEL_GPIO);
	setPinsel(EXP11,PINSEL_GPIO);
	setPinsel(C1,PINSEL_GPIO);
	setPinsel(C2,PINSEL_GPIO);
	setPinsel(C3,PINSEL_GPIO);
	setPinsel(C4,PINSEL_GPIO);
	//fiodir - LDRS
	setDir(LDR1,IN);
	setDir(LDR2,IN);
	setDir(LDR3,IN);
	setDir(LDR4,IN);
	//fiodir - Trastes
	setDir(EXP6,IN);
	setDir(EXP7,IN);
	setDir(EXP8,IN);
	setDir(EXP9,IN);
	setDir(EXP10,IN);
	setDir(EXP11,IN);
	//fiodir - Cuerdas
	setDir(C1,OUT);
	setDir(C2,OUT);
	setDir(C3,OUT);
	setDir(C4,OUT);
	//modO de las curdas
	setPinMode_OD (C1,MS_NORMAL);
	setPinMode_OD (C2,MS_NORMAL);
	setPinMode_OD (C3,MS_NORMAL);
	setPinMode_OD (C4,MS_NORMAL);
    //modo de las cuerdas y los trastes
	setPinMode(LDR1,ME_PULLDOWN);
	setPinMode(LDR2,ME_PULLDOWN);
	setPinMode(LDR3,ME_PULLDOWN);
	setPinMode(LDR4,ME_PULLDOWN);
	setPinMode(EXP6,ME_PULLUP);
	setPinMode(EXP7,ME_PULLUP);
	setPinMode(EXP8,ME_PULLUP);
	setPinMode(EXP9,ME_PULLUP);
	setPinMode(EXP10,ME_PULLUP);
	setPinMode(EXP11,ME_PULLUP);


	//Esto se saca despues era para la prueba q hice con los leds

	//pinsel para gpio
	setPinsel(LED_RED,PINSEL_GPIO);
	setPinsel(LED_BLUE,PINSEL_GPIO);
	setPinsel(LED_GREEN,PINSEL_GPIO);
    //fiodir
  	setDir(LED_RED,OUT);
  	setDir(LED_BLUE,OUT);
  	setDir(LED_GREEN,OUT);
  	//de las salidas, el tipo de salida setpinmode_od
	setPinMode_OD (LED_RED,MS_NORMAL);
  	setPinMode_OD (LED_BLUE,MS_NORMAL);
  	setPinMode_OD (LED_GREEN,MS_NORMAL);
  	//setea las cuerdas en ON
  	setPin(C4,ON);
	setPin(C3,ON);
	setPin(C2,ON);
	setPin(C1,ON);
}

/**
\fn 		uint8_t barridoTrastes(int cuerda)
\brief 	    Lee la cuerda pedida
\param 	    cuerda
\return		uint8_t Devuelve el valor de la cuerda pedida
*/
uint8_t barridoTrastes(int cuerda){

	uint8_t aux=NO_TRASTE;

	//Pone en OFF la cuerda que va a medir y
		//Espera que se establezca la tension
	if(cuerda==0){
		setPin(C1,OFF);
		while(getPin(C1)==ON);
	}else if(cuerda==1){
		setPin(C2,OFF);
		while(getPin(C2)==ON);
	}
	else if(cuerda==2){
		setPin(C3,OFF);
		while( getPin(C3)==ON);
	}
	if(cuerda==3){
		setPin(C4,OFF);
		while( getPin(C4)==ON);
	}
	//si hay 2 traste tocados tiene proridad
	//el traste que esta mas cerca del cuerpo(el mas chico)
	if(getPin(EXP6)==OFF){
		aux=1;
	}else if (getPin(EXP7)==OFF){
		aux=2;
	}else if (getPin(EXP8)==OFF){
		aux=3;
	}else if (getPin(EXP9)==OFF){
		aux=4;
	}else if (getPin(EXP10)==OFF){
		aux=5;
	}else if (getPin(EXP11)==OFF){
		aux=6;
	}
	//seteo todas las cuerdas nuevamente en ON para la siguiente medicion
	setPin(C1,ON);
	setPin(C2,ON);
	setPin(C3,ON);
	setPin(C4,ON);
	while(getPin(C1)==OFF || getPin(C2)==OFF || getPin(C3)==OFF || getPin(C4)==OFF);
	return aux;
}
/**
\fn 		void SWTrastes(uint8_t codigoActual,uint8_t cuerda)
\brief 	    Quita el rebote de la cuerda
\details 	Va haciendo mediciones y cuando se establece un
\details    valor lo pone en el buffer s traste[]
\param 	    codigoActual el valor de la cuerda
\param 	    cuerda
\return		void
*/
void SWTrastes(uint8_t codigoActual,uint8_t cuerda)
{
	//define las variables
	//valor anterior de las cuerdas
	static uint8_t  codigoAnterior[]={NO_TRASTE,NO_TRASTE,NO_TRASTE,NO_TRASTE};
	//cantidad de ciclos
	static uint8_t contador[]={0,0,0,0};
	static int estado[] ={ESPERO,ESPERO,ESPERO,ESPERO};

	switch(estado[cuerda])
	{

		case ESPERO:

			if(codigoActual!=codigoAnterior[cuerda])
			{
				codigoAnterior[cuerda]=codigoActual;
				estado[cuerda] = ESPERO;

			}
			if(codigoActual==codigoAnterior[cuerda])
			{
				contador[cuerda]=MAX_REBOTES;
				estado[cuerda] = CHEQUEO;

			}

			break;

		case CHEQUEO:

			if(codigoActual!=codigoAnterior[cuerda])
			{
				codigoAnterior[cuerda]=codigoActual;
				estado[cuerda] = ESPERO;

			}
			if(codigoActual==codigoAnterior[cuerda] && contador[cuerda]!=0 )
			{
				contador[cuerda]--;
				estado[cuerda] = CHEQUEO;

			}
			if(codigoActual==codigoAnterior[cuerda] && contador[cuerda]==0)
			{
				traste[cuerda]=codigoActual;
				estado[cuerda] = CHEQUEADO;
			}
			break;
		case CHEQUEADO:
			if(codigoActual!=codigoAnterior[cuerda])
			{
				codigoAnterior[cuerda]=codigoActual;
				estado[cuerda] = ESPERO;
			}else
				estado[cuerda] = CHEQUEADO;
			break;
		default: estado[cuerda]= ESPERO;
	}
}
/**
\fn 		void driverTrastes(void)
\brief 	    hace el barrido y el antirebote de las cuerdas
\param 	    void
\return		void
*/
void driverTrastes(void){
	uint8_t CodigoActual ;
	static uint8_t cuerda=0;
	CodigoActual = barridoTrastes(cuerda);
	SWTrastes(CodigoActual,cuerda);
	cuerda++;
	if(cuerda==4)
		cuerda=0;
}
/**
\fn 		void driverLdrs(void)
\brief 	    Mide el valor de los LDRS
\details    Pone el valor en el buffer ldrs[]
\param 	    void
\return		void
*/
void driverLdrs(void){
	int i;
	for(i=0;i<4;i++){
		ldrs[i]=0;
	}
	if(getPin(LDR1)==ON)
		ldrs[0]=1;
	if(getPin(LDR2)==ON)
		ldrs[1]=1;
	if(getPin(LDR3)==ON)
		ldrs[2]=1;
	if(getPin(LDR4)==ON)
		ldrs[3]=1;
}
