/**
 * \file            driversCuerdasyTrastes.c
 * \brief           TPO Informatica 2
 * \author          Grupo 7
 * \date            December, 2020
 */

#include <driversCuerdasyTrastes.h>

//BUFFER TRASTES
extern __RW uint8_t traste[4];
//BUFFER LDRS
extern __RW uint8_t ldrs[4];


/**
*\fn 		void init_gpio(void)
*\brief 	    Inicializo todas las entradas y salidas GPIO
*\details
*\param 	    void
*\return 	void
*/
void init_gpio(void)
{
	//Funcion que usan de los pines
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
	//Direccion de los LDRS
	setDir(LDR1,IN);
	setDir(LDR2,IN);
	setDir(LDR3,IN);
	setDir(LDR4,IN);
	//Direccion de los trastes de la matriz
	setDir(EXP6,IN);
	setDir(EXP7,IN);
	setDir(EXP8,IN);
	setDir(EXP9,IN);
	setDir(EXP10,IN);
	setDir(EXP11,IN);
	//Direccion de las cuerdas de la matriz
	setDir(C1,OUT);
	setDir(C2,OUT);
	setDir(C3,OUT);
	setDir(C4,OUT);
	//Modo de las cuerdas de la matriz
	setPinMode_OD (C1,MS_NORMAL);
	setPinMode_OD (C2,MS_NORMAL);
	setPinMode_OD (C3,MS_NORMAL);
	setPinMode_OD (C4,MS_NORMAL);
    //modo de los LDRS y los trastes de la matriz
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

  	//Setea las cuerdas en ON
  	setPin(C4,ON);
	setPin(C3,ON);
	setPin(C2,ON);
	setPin(C1,ON);
}

/**
*\fn 		uint8_t barridoTrastes(int cuerda)
*\brief 	    Lee la cuerda pedida
*\details
*\param 	    cuerda
*\return		uint8_t Devuelve el valor de la cuerda pedida
*/
uint8_t barridoTrastes(int cuerda){

	uint8_t aux=NO_TRASTE;

	//Pone en OFF la cuerda que va a medir y
	//espera que se establezca la tension
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
