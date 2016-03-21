/**
  ******************************************************************************
  * @file     IRQ.c
  * @author   Spas Spasov
  * @version  V1.1.0
  * @date     10.2014
  * @brief    This file provides firmware functions ...
  *
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "chip.h"                        /* chip definitions                */
#include "LED.h"

/* Private typedef -----------------------------------------------------------*/
/* None */

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Systick Interrupt Handler,
  * 				SysTick interrupt happens every 10 ms.
  * @param  None
  * @retval None
  */
void SysTick_Handler( void ) 
{
 static unsigned long ticks = 0;
 static unsigned int  led_state = 0x00;


  if (ticks++ >= 99) 					/* Set Clock1s to 1 every second */
	{                       
    ticks    = 0;
		
		/* Blink the LED */
		if( led_state ) 
		{
			LedOff();
			led_state = 0;
		}
		else
		{
			LedOn();
			led_state++;
		}
  }
}

/* Public functions ----------------------------------------------------------*/

/******************* (C) COPYRIGHT 2014 Dimitech Pty Ltd   *****END OF FILE****/
