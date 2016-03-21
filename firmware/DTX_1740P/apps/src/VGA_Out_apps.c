/**
  ******************************************************************************
  * @file     VGA_Out_apps.c
  * @author   Spas Spasov
  * @version  V1.1.0
  * @date     10.2014
  * @brief    This file provides firmware functions necessary for management of
  *           the VGA Out supported processes.
  *
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "chip.h"                        /* SAM4S definitions                */
#include "LED.h"
#include "VGA_Out_apps.h"

/* Private typedef -----------------------------------------------------------*/
/* None */

/* Private define ------------------------------------------------------------*/
/** TC0 pins */
#define PIN_TIOA0 {PIO_PA0, PIOA, ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_TIOB0 {PIO_PA1, PIOA, ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_TIOA1 {PIO_PA15, PIOA, ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_TIOB1 {PIO_PA16, PIOA, ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}

/** HSMCI pins */
#define PIN_MCDA0 {PIO_PA30, PIOA, ID_PIOA, PIO_PERIPH_C, PIO_DEFAULT}
#define PIN_MCDA1 {PIO_PA31, PIOA, ID_PIOA, PIO_PERIPH_C, PIO_DEFAULT}
#define PIN_MCDA2 {PIO_PA26, PIOA, ID_PIOA, PIO_PERIPH_C, PIO_DEFAULT}
#define PIN_MCDA3 {PIO_PA27, PIOA, ID_PIOA, PIO_PERIPH_C, PIO_DEFAULT}
#define PIN_MCCK  {PIO_PA29, PIOA, ID_PIOA, PIO_PERIPH_C, PIO_DEFAULT}
#define PIN_MCCDA {PIO_PA28, PIOA, ID_PIOA, PIO_PERIPH_C, PIO_DEFAULT}

#define TC         					TC0
#define CHANNEL_H     			0 
#define CHANNEL_V     			1 
#define ID_TCH      				ID_TC0 
#define ID_TCV      				ID_TC1

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* PA0 - HSYNC, PA15 - VSYNC */
Pin pins_TC[] = {PIN_TIOA0, PIN_TIOA1};

Pin pins_HSMCI[] = {PIN_MCDA0, PIN_MCDA1, PIN_MCDA2, PIN_MCDA3};

extern uint32_t SystemCoreClock;

volatile uint8_t ga_Write_Block[VID_VSIZE][HID_VSIZE];


Mcid gs_hsmsi;

static volatile int8_t g_vflag = 0, g_vdraw = 0;
static volatile uint16_t g_vline = 0, g_temp_total = 0;

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  
  * @param  None
  * @retval None
  */
void TC0_IRQHandler(void)
{
volatile uint32_t dummy;


  /* Clear status bit to acknowledge interrupt */
  dummy = TC0->TC_CHANNEL[ 0 ].TC_SR;
  if( g_vflag )
  {
    HSMCI->HSMCI_PTCR = HSMCI_PTCR_TXTEN;
    HSMCI->HSMCI_IER = HSMCI_IER_TXBUFE;
  }
}


/**
  * @brief  
  * @param  None
  * @retval None
  */
void TC1_IRQHandler(void)
{
volatile uint32_t dummy;


  /* Clear status bit to acknowledge interrupt */
  dummy = TC0->TC_CHANNEL[ 1 ].TC_SR;
  g_vflag = 1;
}


/**
  * @brief  
  * @param  None
  * @retval None
  */
void HSMCI_IRQHandler( void )
{
volatile uint32_t dummy;

//LedOn();
//LedToggle();
  /* Clear status bit to acknowledge interrupt */
  dummy = HSMCI->HSMCI_SR;
	

#if 0
	g_vdraw++;
  if( g_vdraw > 2)
  {
		g_vdraw = 1;

		g_vline++;

		if( g_vline > VID_VSIZE )
    {
    	g_vline = 0;
    	g_vflag = 0;
			g_temp_total = 0;

			HSMCI->HSMCI_IDR = HSMCI_IDR_TXBUFE;
			HSMCI->HSMCI_PTCR = HSMCI_PTCR_TXTDIS;
			HSMCI->HSMCI_TPR = (uint32_t)ga_Write_Block;
			HSMCI->HSMCI_TCR = HID_VSIZE/4;			
    }
    else
    {
			HSMCI->HSMCI_IDR = HSMCI_IDR_TXBUFE;
			HSMCI->HSMCI_PTCR = HSMCI_PTCR_TXTDIS;		
	
			HSMCI->HSMCI_TPR = (uint32_t)&ga_Write_Block[g_vline][0];

			HSMCI->HSMCI_TCR = HID_VSIZE/4;
    }
  }	
	else
	{
		HSMCI->HSMCI_IDR = HSMCI_IDR_TXBUFE;
		HSMCI->HSMCI_PTCR = HSMCI_PTCR_TXTDIS;

		HSMCI->HSMCI_TPR = (uint32_t)&ga_Write_Block[g_vline][0];

		HSMCI->HSMCI_TCR = HID_VSIZE/4;		
	}
#endif

#if 1
	g_vline++;
	if( g_vline > VID_VSIZE )
  {
  	g_vline = 0;
  	g_vflag = 0;
  }

	HSMCI->HSMCI_IDR = HSMCI_IDR_TXBUFE;
	HSMCI->HSMCI_PTCR = HSMCI_PTCR_TXTDIS;
	HSMCI->HSMCI_TPR = (uint32_t)&ga_Write_Block[g_vline][0];
	HSMCI->HSMCI_TCR = HID_VSIZE/4;

#endif
}


/**
  * @brief  
  * @param  None
  * @retval None
  */
void ConfigTCPins( void )
{

	/* pin TIOA0 - HSYNC, pin TIOA1 - VSYNC */
	PIO_Configure(pins_TC, PIO_LISTSIZE(pins_TC));
}


/**
  * @brief  
  * @param  None
  * @retval None
  */
void ConfigTCInterrupt( void )
{

  /* Configure TC interrupts */
  NVIC_DisableIRQ(TC0_IRQn);
  NVIC_ClearPendingIRQ(TC0_IRQn); 
  NVIC_SetPriority(TC0_IRQn,0);
  NVIC_DisableIRQ(TC1_IRQn); 
  NVIC_ClearPendingIRQ(TC1_IRQn); 
  NVIC_SetPriority(TC1_IRQn,0);

  NVIC_EnableIRQ(TC0_IRQn);
  NVIC_EnableIRQ(TC1_IRQn); 	
}

#if 0
/**
  * @brief  
  * @param  None
  * @retval None
  */
void ConfigHVSynchroOut( void )
{

/*
SVGA Signal 800 x 600 @ 60 Hz timing 	- real in project 400x300

General timing:
Screen refresh rate	60 Hz
Vertical refresh	37.878787878788 kHz
Pixel freq.			40.0 MHz							 - real in project 20.0 MHz

Horizontal timing (line):
Polarity of horizontal sync pulse is positive.
Scanline part	Pixels	Time [µs]
Visible area	800		20
Front porch		40		1
Sync pulse		128		3.2
Back porch		88		2.2
Whole line		1056	26.4

Vertical timing (frame):
Polarity of vertical sync pulse is positive.
Frame part		Lines	Time [ms]
Visible area	600		15.84
Front porch		1		0.0264
Sync pulse		4		0.1056
Back porch		23		0.6072
Whole frame		628		16.5792
*/		
	ConfigTCPins();	
		
	PMC_EnablePeripheral(ID_TCH); 
	PMC_EnablePeripheral(ID_TCV);
	
	TC_Configure(TC, CHANNEL_H, TC_CMR_TCCLKS_TIMER_CLOCK1 | TC_CMR_ACPC_SET | TC_CMR_BCPC_SET | TC_CMR_ACPA_CLEAR | TC_CMR_BCPB_CLEAR | TC_CMR_WAVE | TC_CMR_EEVT_XC0 | TC_CMR_WAVSEL_UP_RC);
	TC_WriteRa(TC, CHANNEL_H, 196);		//164 - 100MHz
	TC_WriteRb(TC, CHANNEL_H, 290);		//278
	TC_WriteRc(TC, CHANNEL_H, 1584);	//1320
	
	TC_Configure(TC, CHANNEL_V, TC_CMR_TCCLKS_XC1 | TC_CMR_ACPC_SET | TC_CMR_BCPC_SET | TC_CMR_ACPA_CLEAR | TC_CMR_BCPB_CLEAR | TC_CMR_WAVE | TC_CMR_EEVT_XC0 | TC_CMR_WAVSEL_UP_RC);
	TC_WriteRa(TC, CHANNEL_V, 4);
	TC_WriteRb(TC, CHANNEL_V, 20);	
	TC_WriteRc(TC, CHANNEL_V, 628);
	TC_SetBlockMode(TC, TC_BMR_TC1XC1S_TIOA0);
	
	TC_EnableInterrupt(TC, CHANNEL_H, TC_IER_CPBS);            // Enable interrupt.
	TC_EnableInterrupt(TC, CHANNEL_V, TC_IER_CPBS);            // Enable interrupt.
	
	TC_Start(TC,CHANNEL_H);         														// Start the TC_H
	TC_Start(TC,CHANNEL_V);         														// Start the TC_V
	
	ConfigTCInterrupt();
}
#endif

#if 1
/**
  * @brief
  * @param  None
  * @retval None
  */
void ConfigHVSynchroOut( void )
{

/*
EGA Signal 640 x 350 @ 70 Hz timing

General timing:
Screen refresh rate	70.0 Hz
Vertical refresh		31.78 kHz
Pixel freq.					25.0 MHz

Horizonal Timing:
Horizonal Dots 				640
Vertical 	Scan Lines 	350
Horiz. Sync Polarity 	POS
Horiz. Frequency 			31.47KHz
A (us) 								31.76 Scanline time
B (us) 								3.77 	Sync pulse lenght
C (us) 								1.89 	Back porch
D (us) 								25.6  ctive video time
E (us) 								0.5 	Front porch
         ______________________          ________
________|        VIDEO         |________| VIDEO (next line)
    |-C-|----------D-----------|-E-|
   _                                _
__| |______________________________| |___________
  |B|
  |---------------A----------------|


Vertical Timing:
Horizonal Dots 			640
Vertical Scan Lines 350
Vert. Sync Polarity POS
Vertical Frequency 	70Hz
O (ms) 							14.28 	Total frame time
P (ms) 							0.06 		Sync length
Q (ms) 							1.88		Back porch
R (ms)							11.12		Active video time
S (ms) 							1.22 		Front porch
         ______________________          ________
________|        VIDEO         |________|  VIDEO (next frame)
    |-Q-|----------R-----------|-S-|
   _                                _
__| |______________________________| |___________
  |P|
  |---------------O----------------|

*/
	ConfigTCPins();

	PMC_EnablePeripheral(ID_TCH);
	PMC_EnablePeripheral(ID_TCV);

	/* In clock freq.(f)		-> TIMER_CLOCK1 = MCK/2, 				*/
	/* Out H clock period (T) 	-> A = 1/(TIMER_CLOCK1/RegC), 			*/
	/* H Sync pulse period (T)	-> B = 1/(TIMER_CLOCK1 / RegA), 		*/
	/* H Back porch period (T)	-> C = (1/(TIMER_CLOCK1 / RegB)) - B 	*/
	TC_Configure(TC, CHANNEL_H, TC_CMR_TCCLKS_TIMER_CLOCK1 | TC_CMR_ACPC_SET | TC_CMR_BCPC_SET | TC_CMR_ACPA_CLEAR | TC_CMR_BCPB_CLEAR | TC_CMR_WAVE | TC_CMR_EEVT_XC0 | TC_CMR_WAVSEL_UP_RC);
	TC_WriteRa(TC, CHANNEL_H, 94);
	TC_WriteRb(TC, CHANNEL_H, 141);
	TC_WriteRc(TC, CHANNEL_H, 1652);

	/* In clock period (T)		-> TIOA0 = A, 			*/
	/* Out V clock period (T) 	-> O = A*RegC, 			*/
	/* V Sync pulse period (T) 	-> P = A*RegA), 		*/
	/* V Back porch period (T) 	-> Q = (A*RegB) - P 	*/
	TC_Configure(TC, CHANNEL_V, TC_CMR_TCCLKS_XC1 | TC_CMR_ACPC_SET | TC_CMR_BCPC_SET | TC_CMR_ACPA_CLEAR | TC_CMR_BCPB_CLEAR | TC_CMR_WAVE | TC_CMR_EEVT_XC0 | TC_CMR_WAVSEL_UP_RC);
	TC_WriteRa(TC, CHANNEL_V, 2);
	TC_WriteRb(TC, CHANNEL_V, 52);
	TC_WriteRc(TC, CHANNEL_V, 449);
	TC_SetBlockMode(TC, TC_BMR_TC1XC1S_TIOA0);

	TC_EnableInterrupt(TC, CHANNEL_H, TC_IER_CPBS);            	/* Enable interrupt. 	*/
	TC_EnableInterrupt(TC, CHANNEL_V, TC_IER_CPBS);            	/* Enable interrupt. 	*/

	TC_Start(TC,CHANNEL_H);         							/* Start the TC_H		*/
	TC_Start(TC,CHANNEL_V);         							/* Start the TC_V		*/

	ConfigTCInterrupt();
}
#endif

/**
  * @brief  
  * @param  None
  * @retval None
  */
void HSMCI_Init( void )
{
	/*!!! HSMCI send first Hi half-byte*/
	
	PIO_Configure(pins_HSMCI, PIO_LISTSIZE(pins_HSMCI));
	MCI_Init(&gs_hsmsi, HSMCI, ID_HSMCI, SystemCoreClock);
	MCI_SetBusWidth(&gs_hsmsi, HSMCI_SDCR_SDCBUS_4);

	/* set clock speed for pixel in Hz*/
	MCI_SetSpeed(&gs_hsmsi, 30000000, SystemCoreClock);

	MCI_EnableHsMode(&gs_hsmsi, 1);
	PMC_EnablePeripheral(ID_HSMCI);
	
	HSMCI->HSMCI_IER = HSMCI_IER_TXBUFE;
	
	MCI_Enable(HSMCI);
	
	HSMCI->HSMCI_MR |= HSMCI_MR_PDCMODE;
	HSMCI->HSMCI_TPR = (uint32_t)ga_Write_Block;
	HSMCI->HSMCI_TCR = HID_VSIZE/4;
	HSMCI->HSMCI_ARGR = 0;
	HSMCI->HSMCI_CMDR = 0x00110000;	
	
	
	NVIC_DisableIRQ(HSMCI_IRQn); 
	NVIC_ClearPendingIRQ(HSMCI_IRQn);
	NVIC_SetPriority(HSMCI_IRQn,0);
	NVIC_EnableIRQ(HSMCI_IRQn);
}

#if 0
/**
  * @brief
  * @param  None
  * @retval None
  */
void ColorColumnGradation4bit( void )
{
unsigned int i,j,k = 0, m = 0;


	for( k = 0; k < 256; k += 17 )
	{
		for( j = 0; j < VID_VSIZE; j++ )
		{
			for( i = 0; i < 12; i++ )
			{
				ga_Write_Block[j][i+m] = k;
			}
		}
		m += 12;
	}

}
#endif

#if 1
/**
  * @brief  
  * @param  None
  * @retval None
  */
void ColorColumnGradation4bit( void )
{
unsigned int  i,j,k = 0;
unsigned char m, mx;


	for( j = 0; j < VID_VSIZE; j++ )
	{
		m = 0, mx = 0;
		for( k = 0; k < HID_VSIZE; k += 20 )
		{
			for( i = 0; i < 20; i++ )
			{
				ga_Write_Block[j][i+k] = mx;
			}
			m ++;
			mx = m << 4;
			mx |= m;
		}
	}
}
#endif


/**
  * @brief
  * @param  None
  * @retval None
  */
void Frame4bit( unsigned char color )
{
unsigned int  i;
unsigned char  tmp_color;


	color			&= 0x0F;
	tmp_color = color << 4;
	tmp_color |= color;

	for( i = 0; i < 640; i++ )
	{
		ga_Write_Block[0][i] = tmp_color;
	}

	for( i = 0; i < 640; i++ )
	{
		ga_Write_Block[349][i] = tmp_color;
	}

	for( i = 1; i < 350; i++ )
	{
		ga_Write_Block[i][0] = tmp_color;
	}

	for( i = 0; i < 350; i++ )
	{
		ga_Write_Block[i][639] = tmp_color;
	}
}



/* Public functions ----------------------------------------------------------*/

/**
  * @brief  
  * @param  None
  * @retval None
  */
void StartVGAOut( void )
{

#if 0
unsigned int i;

	for(i = 0; i < HID_VSIZE; i++ )
	{
		ga_Write_Block[0][i] = i+1;
	}
	ga_Write_Block[0][3] = 0x30;
#endif	

//	ColorColumnGradation4bit();
	Frame4bit(9);

	HSMCI_Init();
	ConfigHVSynchroOut();
}

/******************* (C) COPYRIGHT 2014 Dimitech Pty Ltd   *****END OF FILE****/
