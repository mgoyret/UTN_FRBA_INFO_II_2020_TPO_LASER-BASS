/**
 * 	Regs_LPC176x.h
 *
 *	Created on:
 *		Author:
 */

#ifndef REGS_LPC176X_H_
#define REGS_LPC176X_H_

#define		__R			volatile const
#define		__W			volatile
#define		__RW		volatile

typedef 	unsigned int 		uint32_t;
typedef 	unsigned short 		uint16_t;
typedef 	unsigned char 		uint8_t;

typedef 	__RW uint32_t 		registro; //!< defino un tipo 'registro' (volatile uint32_t)

//!< ////////////////Registros PINSEL//////////////////////////////
//!< 0x4002C000UL : Dirección de inicio de los registros PINSEL
#define		PINSEL		( ( registro  * ) 0x4002C000UL )

#define		PINSEL0		PINSEL[0]	//!< PINSEL0------>P0[15:0] 		(0x4002C000)
#define		PINSEL1		PINSEL[1]	//!< PINSEL1------>P0[31:16] 		(0x4002C004)
#define		PINSEL2		PINSEL[2]	//!< PINSEL2------>P1[15:0] 		(0x4002C008)
#define		PINSEL3		PINSEL[3]	//!< PINSEL3------>P1[31:16] 		(0x4002C00C)
#define		PINSEL4		PINSEL[4]	//!< PINSEL4------>P2[15:0] 		(0x4002C010)
#define		PINSEL5		PINSEL[5]	//!< PINSEL5------>P2[31:16] 		NOT USED
#define		PINSEL6		PINSEL[6]	//!< PINSEL6------>P3[15:0]			NOT USED
#define		PINSEL7		PINSEL[7]	//!< PINSEL7------>P3[31:16] 		(0x4002C01C)
#define		PINSEL8		PINSEL[8]	//!< PINSEL8------>P4[15:0]			NOT USED
#define		PINSEL9		PINSEL[9]	//!< PINSEL9------>P4[31:16] 		(0x4002C024)

//!< ----------- Nro. de PUERTOS
#define 	P0			0
#define 	P1			1
#define 	P2			2
#define 	P3			3
#define 	P4			4

//!< //////////////////Registros PINMODE ///////////////////////////
//!< 0x4002C040UL : Dirección de inicio de los registros de modo de los pines del GPIO
#define	PINMODE		( ( registro  * ) 0x4002C040UL )

#define		PINMODE0	PINMODE[0]		//!< 0x4002C040
#define		PINMODE1	PINMODE[1]		//!< 0x4002C044
#define		PINMODE2	PINMODE[2]		//!< 0x4002C048
#define		PINMODE3	PINMODE[3]		//!< 0x4002C04C
#define		PINMODE4	PINMODE[4]		//!< 0x4002C050
#define		PINMODE5	PINMODE[5]		//!< 0x4002C054
#define		PINMODE6	PINMODE[6]		//!< 0x4002C058
#define		PINMODE7	PINMODE[7]		//!< 0x4002C05C
#define		PINMODE8	PINMODE[8]		//!< 0x4002C060
#define		PINMODE9	PINMODE[9]		//!< 0x4002C064

//!< ///////////////// REGISTROS PINMODE_OD ///////////////////////////
//!< 0x4002C068UL : Dirección de inicio de los registros de control del modo OPEN DRAIN
#define		PINMODE_OD		( ( registro  * ) 0x4002C068UL )

#define		PINMODE_OD0		PINMODE_OD[0]
#define		PINMODE_OD1		PINMODE_OD[1]
#define		PINMODE_OD2		PINMODE_OD[2]
#define		PINMODE_OD3		PINMODE_OD[3]
#define		PINMODE_OD4		PINMODE_OD[4]

//!< ////////////////// REGISTROS GPIOs //////////////////////////////
//!< 0x2009C000UL : Dirección de inicio (base) de los registros de GPIO
#define		GPIO_BASE		( ( registro  * ) 0x2009C000UL )

#define 	GPIO0_BASE		(GPIO_BASE + 0x00000)	//!< 0x2009C000
#define 	GPIO1_BASE 		(GPIO_BASE + 0x00020)	//!< 0x2009C020
#define 	GPIO2_BASE 		(GPIO_BASE + 0x00040)	//!< 0x2009C040
#define 	GPIO3_BASE 		(GPIO_BASE + 0x00060)	//!< 0x2009C060
#define 	GPIO4_BASE 		(GPIO_BASE + 0x00080)	//!< 0x2009C080

#define 	PORT0			GPIO0_BASE		//!< 0x2009C000
#define 	PORT1			GPIO1_BASE		//!< 0x2009C020
#define 	PORT2			GPIO2_BASE		//!< 0x2009C040
#define 	PORT3			GPIO3_BASE		//!< 0x2009C060
#define 	PORT4			GPIO4_BASE		//!< 0x2009C080

/*	*			*
	*************************
	*	FIODIR		*	0x2009C000
	*************************
	*	RESERVED	*	0x2009C004
	*************************
	*	RESERVED	*	0x2009C008
	*************************
	*	RESERVED	*	0x2009C00C
	*************************
	*	FIOMASK		*	0x2009C010
	*************************
	*	FIOPIN		*	0x2009C014
	*************************
	*	FIOSET		*	0x2009C018
	*************************
	*	FIOCLR		*	0x2009C01C
	*************************
	*			*
*/
#define		FIO0DIR		GPIO_BASE[0]	//!< 0x2009C000
#define		FIO1DIR		GPIO_BASE[8]	//!< 0x2009C020
#define		FIO2DIR		GPIO_BASE[16]	//!< 0x2009C040
#define		FIO3DIR		GPIO_BASE[24]	//!< 0x2009C060
#define		FIO4DIR		GPIO_BASE[32]	//!< 0x2009C080

#define		FIO0MASK	GPIO_BASE[4]	//!< 0x2009C010
#define		FIO1MASK	GPIO_BASE[12]	//!< 0x2009C030
#define		FIO2MASK	GPIO_BASE[20]	//!< 0x2009C050
#define		FIO3MASK	GPIO_BASE[28]	//!< 0x2009C070
#define		FIO4MASK	GPIO_BASE[36]	//!< 0x2009C090

#define		FIO0PIN		GPIO_BASE[5]	//!< 0x2009C014
#define		FIO1PIN		GPIO_BASE[13]	//!< 0x2009C034
#define		FIO2PIN		GPIO_BASE[21]	//!< 0x2009C054
#define		FIO3PIN		GPIO_BASE[29]	//!< 0x2009C074
#define		FIO4PIN		GPIO_BASE[37]	//!< 0x2009C094

#define		FIO0SET		GPIO_BASE[6]	//!< 0x2009C018
#define		FIO1SET		GPIO_BASE[14]	//!< 0x2009C038
#define		FIO2SET		GPIO_BASE[22]	//!< 0x2009C058
#define		FIO3SET		GPIO_BASE[30]	//!< 0x2009C078
#define		FIO4SET		GPIO_BASE[38]	//!< 0x2009C098

#define		FIO0CLR		GPIO_BASE[7]	//!< 0x2009C01C
#define		FIO1CLR		GPIO_BASE[15]	//!< 0x2009C03C
#define		FIO2CLR		GPIO_BASE[23]	//!< 0x2009C05C
#define		FIO3CLR		GPIO_BASE[31]	//!< 0x2009C07C
#define		FIO4CLR		GPIO_BASE[39]	//!< 0x2009C09C

//////////////Registros del CLOCK y de sistema/////////////////
//0x400FC1A0UL: Registro de control de sistema y registro de status:
#define		DIR_SCS			( (uint32_t *) 0x400FC1A0UL)
//0x400FC104UL: Registro de configuración del clock:
#define		DIR_CCLKCFG		( (uint32_t *) 0x400FC104UL)
//0x400FC10CUL: Registro de selección del clock:
#define		DIR_CLKSRCSEL	( (uint32_t *) 0x400FC10CUL)
//0x400FC1C8UL: Clock Output Config register:
#define		DIR_CLKOUTCFG	( (uint32_t *) 0x400FC1C8UL)
//0x400FC000UL: Flash access configuration:
#define		DIR_FLASHCFG	( (uint32_t *) 0x400FC000UL)

/////////////////Registros de los PLL///////////////////////////
//0x400FC080UL: Registro de control del PLL0:
#define		DIR_PLL0CON		( (uint32_t *) 0x400FC080UL)
//0x400FC084UL: Registro de configuración del PLL0:
#define		DIR_PLL0CFG		( (uint32_t *) 0x400FC084UL)
//0x400FC088UL: Registro de estado del PLL0:
#define		DIR_PLL0STAT	( (uint32_t *) 0x400FC088UL)
//0x400FC08CUL: Registro de control del PLL0:
#define		DIR_PLL0FEED	( (uint32_t *) 0x400FC08CUL)
//0x400FC0A0UL: Registro de control del PLL1:
#define		DIR_PLL1CON		( (uint32_t *) 0x400FC0A0UL)
//0x400FC0A4UL: Registro de configuración del PLL1:
#define		DIR_PLL1CFG		( (uint32_t *) 0x400FC0A4UL)
//0x400FC0A8UL: Registro de estado del PLL1:
#define		DIR_PLL1STAT	( (uint32_t *) 0x400FC0A8UL)
//0x400FC0ACUL: Registro de control del PLL1:
#define		DIR_PLL1FEED	( (uint32_t *) 0x400FC0ACUL)

//Valores para configuración del PLL:
#define 	CLOCK_SETUP_Value 	    1
#define 	SCS_Value				0x00000020
#define 	CLKSRCSEL_Value         0x00000001
#define 	PLL0_SETUP_Value        1
#define 	PLL0CFG_Value           0x00050063
#define 	PLL1_SETUP_Value        1
#define 	PLL1CFG_Value           0x00000023
#define 	CCLKCFG_Value           0x00000003
#define 	USBCLKCFG_Value         0x00000000
#define 	PCLKSEL0_Value          0x00000000
#define 	PCLKSEL1_Value          0x00000000
#define 	PCONP_Value             0x042887DE
#define 	CLKOUTCFG_Value         0x00000000
#define		FLASHCFG_Value			0x00004000

//Registro de status y configuración del sistema:
#define		SCS			DIR_SCS[0]
#define 	FLASHCFG	DIR_FLASHCFG[0]

//Registros de control del CLOCK:
#define		CCLKCFG		DIR_CCLKCFG[0]
#define		CLKSRCSEL	DIR_CLKSRCSEL[0]
#define		CLKOUTCFG	DIR_CLKOUTCFG[0]

//PLL0:
#define		PLL0CON		DIR_PLL0CON[0]
#define		PLL0CFG		DIR_PLL0CFG[0]
#define		PLL0STAT	DIR_PLL0STAT[0]
#define		PLL0FEED	DIR_PLL0FEED[0]

//PLL1:
#define		PLL1CON		DIR_PLL1CON[0]
#define		PLL1CFG		DIR_PLL1CFG[0]
#define		PLL1STAT	DIR_PLL1STAT[0]
#define		PLL1FEED	DIR_PLL1FEED[0]

//!< /////////////		SYSTICK		///////////////////////////
//!< Tipo de dato específico para manejar el SYSTICK
typedef struct
{
	union{
		registro _STCTRL;
		struct{
			registro _ENABLE:1;
			registro _TICKINT:1;
			registro _CLKSOURCE:1;
			registro _RESERVED0:12;
			registro _COUNTFLAG:1;
			registro _RESERVED1:16;
		}bits;
	};
	registro _STRELOAD;
	registro _STCURR;
	__R uint32_t  _STCALIB;
}SysTick_t;

//!< 0xE000E010UL: Registro de control del SysTick:
#define 	SYSTICK_BASE		( (SysTick_t *) 0xE000E010UL )

#define		STCTRL		SYSTICK_BASE->_STCTRL
	#define	ENABLE			SYSTICK_BASE->bits._ENABLE
	#define	TICKINT			SYSTICK_BASE->bits._TICKINT
	#define	CLKSOURCE		SYSTICK_BASE->bits._CLKSOURCE
	#define	COUNTFLAG		SYSTICK_BASE->bits._COUNTFLAG
#define		STRELOAD	SYSTICK_BASE->_STRELOAD
#define		STCURR		SYSTICK_BASE->_STCURR
#define		STCALIB		SYSTICK_BASE->_STCALIB

#define		ST_ENABLE			0
#define		ST_TICKINT			1
#define		ST_CLKSOURCE		2
#define		ST_COUNTFLAG		16

//!< ///////////////////   TIMERS   /////////////////////////////
//!< 0x40004000UL : Dirección de inicio de los registros del Timer0
#define		TIMER0		( ( registro  * ) 0x40004000UL )
//!< 0x40008000UL : Dirección de inicio de los registros del Timer1
#define		TIMER1		( ( registro  * ) 0x40008000UL )
//!< 0x40090000UL : Dirección de inicio de los registros del Timer2
#define		TIMER2		( ( registro  * ) 0x40090000UL )
//!< 0x40094000UL : Dirección de inicio de los registros del Timer3
#define		TIMER3		( ( registro  * ) 0x40094000UL )

//Registros de timers:
#define		T0IR		TIMER0[0]
#define		T0TCR		TIMER0[1]
#define		T0TC		TIMER0[2]
#define		T0PR		TIMER0[3]
#define		T0PC		TIMER0[4]
#define		T0MCR		TIMER0[5]
#define		T0MR0		TIMER0[6]
#define		T0MR1		TIMER0[7]
#define		T0MR2		TIMER0[8]
#define		T0MR3		TIMER0[9]
#define		T0CCR		TIMER0[10]
#define		T0CR0		TIMER0[11]
#define		T0CR1		TIMER0[12]

#define		T1IR		TIMER1[0]
#define		T1TCR		TIMER1[1]
#define		T1TC		TIMER1[2]
#define		T1PR		TIMER1[3]
#define		T1PC		TIMER1[4]
#define		T1MCR		TIMER1[5]
#define		T1MR0		TIMER1[6]
#define		T1MR1		TIMER1[7]
#define		T1MR2		TIMER1[8]
#define		T1MR3		TIMER1[9]
#define		T1CCR		TIMER1[10]
#define		T1CR0		TIMER1[11]
#define		T1CR1		TIMER1[12]

#define		T2IR		TIMER2[0]
#define		T2TCR		TIMER2[1]
#define		T2TC		TIMER2[2]
#define		T2PR		TIMER2[3]
#define		T2PC		TIMER2[4]
#define		T2MCR		TIMER2[5]
#define		T2MR0		TIMER2[6]
#define		T2MR1		TIMER2[7]
#define		T2MR2		TIMER2[8]
#define		T2MR3		TIMER2[9]
#define		T2CCR		TIMER2[10]
#define		T2CR0		TIMER2[11]
#define		T2CR1		TIMER2[12]

#define		T3IR		TIMER3[0]
#define		T3TCR		TIMER3[1]
#define		T3TC		TIMER3[2]
#define		T3PR		TIMER3[3]
#define		T3PC		TIMER3[4]
#define		T3MCR		TIMER3[5]
#define		T3MR0		TIMER3[6]
#define		T3MR1		TIMER3[7]
#define		T3MR2		TIMER3[8]
#define		T3MR3		TIMER3[9]
#define		T3CCR		TIMER3[10]
#define		T3CR0		TIMER3[11]
#define		T3CR1		TIMER3[12]
//!< EMR y CTCR no han sido definidos. (no están en posiciones contiguas)


//!< ///////////////////   NVIC   //////////////////////////
//!< Nested Vectored Interrupt Controller (NVIC)
//!< 0xE000E100UL : Direccion de inicio de los registros de habilitación (set) de interrupciones en el NVIC:
#define		ISER		( ( registro  * ) 0xE000E100UL )
//!< 0xE000E180UL : Direccion de inicio de los registros de deshabilitacion (clear) de interrupciones en el NVIC:
#define		ICER		( ( registro  * ) 0xE000E180UL )

//!< Registros ISER:
#define		ISER0		ISER[0]
#define		ISER1		ISER[1]

//!< Registros ICER:
#define		ICER0		ICER[0]
#define		ICER1		ICER[1]

//!<  Specific Interrupt Numbers:
#define  	TIMER0_IRQn		1        /*!< Timer0 Interrupt                                 */
#define  	TIMER1_IRQn		2        /*!< Timer1 Interrupt                                 */
#define  	TIMER2_IRQn		3        /*!< Timer2 Interrupt                                 */
#define  	TIMER3_IRQn		4        /*!< Timer3 Interrupt                                 */
#define  	UART0_IRQn		5        /*!< UART0 Interrupt                                  */
#define  	UART1_IRQn		6        /*!< UART1 Interrupt                                  */
#define  	UART2_IRQn		7        /*!< UART2 Interrupt                                  */
#define  	UART3_IRQn		8        /*!< UART3 Interrupt                                  */
#define  	RTC_IRQn		17       /*!< Real Time Clock Interrupt                        */
#define  	EINT0_IRQn		18       /*!< External Interrupt 0 Interrupt                   */
#define  	EINT1_IRQn		19       /*!< External Interrupt 1 Interrupt                   */
#define  	EINT2_IRQn		20       /*!< External Interrupt 2 Interrupt                   */
#define  	EINT3_IRQn		21       /*!< External Interrupt 3 Interrupt                   */
#define  	ADC_IRQn		22       /*!< A/D Converter Interrupt                          */

//!< ///////////////////   PCONP   //////////////////////////
//!<  Power Control for Peripherals register (PCONP - 0x400F C0C4) [pag. 62 user manual LPC1769]
//!< 0x400FC0C4UL : Dirección de inicio del registro de habilitación de dispositivos:
#define 	PCONP	(* ( ( registro  * ) 0x400FC0C4UL ))

//!< //////////   INTERRUPCIONES EXTERNAS   /////////////////
//!< 0x400FC140UL : Dirección de inicio de los registros de configuración de las interrupciones externas
#define		EXTINT			*( ( registro * ) 0x400FC140UL)
#define	    EXTMODE 		*( ( registro * ) 0x400FC148UL)
#define	    EXTPOLAR 		*( ( registro * ) 0x400FC14CUL)

//!< ///////////////////   PCLKSEL   //////////////////////////
//!< Peripheral Clock Selection registers 0 and 1 (PCLKSEL0 -0x400F C1A8 and PCLKSEL1 - 0x400F C1AC) [pag. 56 user manual]
//!< 0x400FC1A8UL : Dirección de inicio de los registros de selección de los CLKs de los dispositivos:
#define		PCLKSEL		( ( registro  * ) 0x400FC1A8UL )

//!< Registros PCLKSEL
#define		PCLKSEL0	PCLKSEL[0]
#define		PCLKSEL1	PCLKSEL[1]

//!< ///////////////////   UART0   //////////////////////////
//!< 0x4000C000UL : Registro de control de la UART0:
#define		UART0	( ( registro  * ) 0x4000C000UL )

//!< Registros de la UART0:
#define		U0THR		UART0[0]
#define		U0RBR		UART0[0]
#define		U0DLL		UART0[0]

#define		U0DLM		UART0[1]
#define		U0IER		UART0[1]

#define		U0IIR		((__R registro *)UART0)[2]
#define		U0FCR		((__W registro *)UART0)[2]

#define		U0LCR		UART0[3]
//!< posición 4 no definida [consultar pag. 300 user manual LPC1769]
#define		U0LSR		UART0[5]
//!< posición 6 no definida [consultar pag. 300 user manual LPC1769]
#define		U0SCR		UART0[7]

//!< ///////////////////   UART1   //////////////////////////
//!< 0x40010000UL : Registro de control de la UART1:
#define		UART1	( ( registro  * ) 0x40010000UL )

//!< Registros de la UART1:
#define		U1THR		UART1[0]
#define		U1RBR		UART1[0]
#define		U1DLL		UART1[0]

#define		U1DLM		UART1[1]
#define		U1IER		UART1[1]

#define		U1IIR		UART1[2]
#define		U1FCR		UART1[2]

#define		U1LCR		UART1[3]
#define		U1MCR		UART1[4]
#define		U1LSR		UART1[5]
#define		U1MSR		UART1[6]
#define		U1SCR		UART1[7]

//!< //////////BITS DE ANALISIS para todas las UARTs   ////////////////////
#define 	IER_RBR		0x01
#define 	IER_THRE	0x02
#define 	IER_RLS		0x04

#define 	IIR_PEND	0x01
#define 	IIR_RLS		0x06
#define 	IIR_RDA		0x04
#define 	IIR_CTI		0x0C
#define 	IIR_THRE	0x02

#define 	LSR_RDR		0x01
#define 	LSR_OE		0x02
#define 	LSR_PE		0x04
#define 	LSR_FE		0x08
#define 	LSR_BI		0x10
#define 	LSR_THRE	0x20
#define 	LSR_TEMT	0x40
#define 	LSR_RXFE	0x80

//!< macros útiles para UARTs
#define		U0RDR		(U0LSR & LSR_RDR)
#define		U0THRE		((U0LSR & LSR_THRE) >> 5)
#define		U1RDR		(U1LSR & LSR_RDR)
#define		U1THRE		((U1LSR & LSR_THRE) >> 5)

//!< ///////////////////   DAC /////////////////////////////
//!< 0x4008C000UL : Registro de conversion del DAC:
#define		DACR		(* ( ( registro  * ) 0x4008C000UL ))
//!< 0x4008C004UL : Registro de control del DAC:
#define		DACCTRL		(* ( ( registro  * ) 0x4008C004UL ))
//!< 0x4008C008UL : Registro de contador del DAC:
#define		DACCNTVAL 	(* ( ( registro  * ) 0x4008C008UL ))

//!< ///////////////////   ADC   /////////////////////////////
//!< 0x40034000UL: Registro de control del ADC:
#define		AD0CR		(* ( ( registro  * ) 0x40034000UL ))
//!< 0x40034004UL: Registro de estado del ADC:
#define		AD0GDR		(* ( ( registro  * ) 0x40034004UL ))
//!< 0x4003400CUL: Registro de interrupcion del ADC
#define		AD0INTEN 	(* ( ( registro  * ) 0x4003400CUL ))

//!< 0x40034010UL: Dirección de comienzo de los registros de estado de los ADCx
#define		AD0DR			( ( registro  * ) 0x40034010UL )

//!< Registros de los estados de cada canal del ADC:
#define		AD0DR0		AD0DR[0]
#define		AD0DR1		AD0DR[1]
#define		AD0DR2		AD0DR[2]
#define		AD0DR3		AD0DR[3]
#define		AD0DR4		AD0DR[4]
#define		AD0DR5		AD0DR[5]
#define		AD0DR6		AD0DR[6]
#define		AD0DR7		AD0DR[7]

//!< ///////////////////   RTC   /////////////////////////////
//!< 0x40034000UL: Registro de configuracion y estado del RTC y registros de backup:
#define		RTC 			( ( registro  * ) 0x40024000UL )

//!< Miscellaneous registers
#define		ILR			RTC[0]
#define		CCR			RTC[2]
#define		CIIR		RTC[3]
#define		AMR			RTC[4]
#define		RTC_AUX		RTC[23]
#define		RTC_AUXEN	RTC[22]
#define		CTIME0		RTC[5]
#define		CTIME1		RTC[6]
#define		CTIME2		RTC[7]

//!< Time counter registers
#define		SEC			RTC[8]
#define		MIN			RTC[9]
#define		HOUR		RTC[10]
#define		DOM			RTC[11]
#define		DOW			RTC[12]
#define		DOY			RTC[13]
#define		MONTH		RTC[14]
#define		YEAR		RTC[15]
#define		CALIBRATION	RTC[16]

//!< General purpose registers
#define		GPREG0		RTC[17]
#define		GPREG1		RTC[18]
#define		GPREG2		RTC[19]
#define		GPREG3		RTC[20]
#define		GPREG4		RTC[21]

//!< Alarm register group
#define		ALSEC		RTC[24]
#define		ALMIN		RTC[25]
#define		ALHOUR		RTC[26]
#define		ALDOM		RTC[27]
#define		ALDOW		RTC[28]
#define		ALDOY		RTC[29]
#define		ALMON		RTC[30]
#define		ALYEAR		RTC[31]

#endif /* REGS_LPC176X_H_ */
