/**
  ******************************************************************************
  * @file     main.c
  * @author   Spas Spasov
  * @version  V1.0.0
  * @date     10.2014
  * @brief
  *
  *
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "chip.h"             			/* Device header			*/
#include "LED.h"
#include "VGA_Out_apps.h"
#include "mspi_apps.h"
#include "Drawing_apps.h"

/* Private typedef -----------------------------------------------------------*/
/* None */

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
draw_t draw_init;


/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/

void mydelay(uint32_t delay)
{
uint32_t i;


	for(i = 0; i < delay; i++)
	{

	}
}


/**
  * @brief  This is a "main()" function of the project.
  * @param  None
  * @retval int
  */
int main( void )
{


	SystemInit();
	SystemCoreClockUpdate();

	LedInit();


//	gDrawALineColour(&draw_init);
//	gDrawAPointColour(&draw_init);
	StartVGAOut();

	SysTick_Config(SystemCoreClock/100);  /* Generate interrupt each 10 ms      */
//	mSpiSart();

	while(1)
	{
		mydelay(20000000);
		draw_init.x1 			= 10;
		draw_init.y1 			= 10;
		draw_init.x2_rx 		= 630;
		draw_init.y2_ry 		= 320;
		draw_init.function 		= F_OVERWRITE;
		draw_init.colour 		= 0x0F;
		gDrawALineColour(&draw_init);

		mydelay(10000000);
		draw_init.x1 			= 10;
		draw_init.y1 			= 320;
		draw_init.x2_rx 		= 630;
		draw_init.y2_ry 		= 10;
		draw_init.function 		= F_OVERWRITE;
		draw_init.colour 		= 0x0A;
		gDrawALineColour(&draw_init);
#if 1
		mydelay(10000000);
		draw_init.x1 			= 320;
		draw_init.y1 			= 175;
		draw_init.x2_rx 		= 220;
		draw_init.y2_ry 		= 100;
		draw_init.function 		= F_OVERWRITE;
		draw_init.type			= 1;
		draw_init.colour 		= 0x0D;
		gDrawAEllipseColour(&draw_init);

		mydelay(10000000);
		draw_init.x1 			= 320;
		draw_init.y1 			= 175;
		draw_init.x2_rx 		= 50;
		draw_init.y2_ry 		= 50;
		draw_init.function 		= F_OVERWRITE;
		draw_init.type			= 1;
		draw_init.colour 		= 0x03;
		gDrawAEllipseColour(&draw_init);
#endif
		mydelay(10000000);
		draw_init.x1 			= 5;
		draw_init.y1 			= 5;
		draw_init.x2_rx 		= 635;
		draw_init.y2_ry 		= 315;
		draw_init.function 		= F_OVERWRITE;
		draw_init.type			= 0;
		draw_init.colour 		= 0x0E;
		gDrawARectangleColour(&draw_init);

		mydelay(10000000);
		draw_init.x1 			= 50;
		draw_init.y1 			= 50;
		draw_init.x2_rx 		= 400;
		draw_init.y2_ry 		= 200;
		draw_init.function 		= F_OVERWRITE;
		draw_init.type			= 0;
		draw_init.colour 		= 0x04;
		gDrawARectangleColour(&draw_init);

		mydelay(10000000);
		draw_init.x1 			= 52;
		draw_init.y1 			= 52;
		draw_init.x2_rx 		= 0;
		draw_init.y2_ry 		= 0;
		draw_init.ascii_sym		= 'a';
		draw_init.ascii_font	= 0;
		draw_init.function 		= F_OVERWRITE;
		draw_init.type			= 0;
		draw_init.colour 		= 0x0F;
		gDrawAAsciiSymbolColour(&draw_init);

		draw_init.x1 			= 60;
		draw_init.y1 			= 52;
		draw_init.x2_rx 		= 0;
		draw_init.y2_ry 		= 0;
		draw_init.ascii_sym		= 'B';
		draw_init.ascii_font	= 1;
		draw_init.function 		= F_OVERWRITE;
		draw_init.type			= 0;
		draw_init.colour 		= 0x0E;
		gDrawAAsciiSymbolColour(&draw_init);

		draw_init.x1 			= 68;
		draw_init.y1 			= 52;
		draw_init.x2_rx 		= 0;
		draw_init.y2_ry 		= 0;
		draw_init.ascii_sym		= 'c';
		draw_init.ascii_font	= 0;
		draw_init.function 		= F_OVERWRITE;
		draw_init.type			= 0;
		draw_init.colour 		= 0x0D;
		gDrawAAsciiSymbolColour(&draw_init);

		draw_init.x1 			= 76;
		draw_init.y1 			= 52;
		draw_init.x2_rx 		= 0;
		draw_init.y2_ry 		= 0;
		draw_init.ascii_sym		= 'D';
		draw_init.ascii_font	= 1;
		draw_init.function 		= F_OVERWRITE;
		draw_init.type			= 0;
		draw_init.colour 		= 0x0C;
		gDrawAAsciiSymbolColour(&draw_init);

		draw_init.x1 			= 84;
		draw_init.y1 			= 52;
		draw_init.x2_rx 		= 0;
		draw_init.y2_ry 		= 0;
		draw_init.ascii_sym		= 'e';
		draw_init.ascii_font	= 0;
		draw_init.function 		= F_OVERWRITE;
		draw_init.type			= 0;
		draw_init.colour 		= 0x0B;
		gDrawAAsciiSymbolColour(&draw_init);

		draw_init.x1 			= 92;
		draw_init.y1 			= 52;
		draw_init.x2_rx 		= 0;
		draw_init.y2_ry 		= 0;
		draw_init.ascii_sym		= 'F';
		draw_init.ascii_font	= 1;
		draw_init.function 		= F_OVERWRITE;
		draw_init.type			= 0;
		draw_init.colour 		= 0x0A;
		gDrawAAsciiSymbolColour(&draw_init);



#if 1
		mydelay(20000000);
		draw_init.x1 			= 120;
		draw_init.y1 			= 120;
		draw_init.x2_rx 		= 240;
		draw_init.y2_ry 		= 240;
		draw_init.function 		= F_OVERWRITE;
		draw_init.type			= 1;
		draw_init.colour 		= 0x05;
		gDrawARectangleColour(&draw_init);
#endif
		mydelay(20000000);
		draw_init.x1 			= 50;
		draw_init.y1 			= 50;
		draw_init.x2_rx 		= 400;
		draw_init.y2_ry 		= 200;
		gSetADrawFrame(&draw_init);
		draw_init.x1 			= 10;
		draw_init.y1 			= 10;
		draw_init.x2_rx 		= 630;
		draw_init.y2_ry 		= 320;
		draw_init.function 		= F_OVERWRITE;
		draw_init.colour 		= 0x00;
		gDrawALineColour(&draw_init);

		mydelay(20000000);
		draw_init.x1 			= 10;
		draw_init.y1 			= 320;
		draw_init.x2_rx 		= 630;
		draw_init.y2_ry 		= 10;
		draw_init.function 		= F_OVERWRITE;
		draw_init.colour 		= 0x00;
		gDrawALineColour(&draw_init);

	  /* Select Idle mode entry -------------------------------------------------*/
	  /* Request Wait For Interrupt	*/
//		Idle();
	}
}

/******************* (C) COPYRIGHT 2014 Dimitech Pty Ltd   *****END OF FILE****/
