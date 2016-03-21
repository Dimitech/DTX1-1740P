/**
  ******************************************************************************
  * @file     LED.c
  * @author   Spas Spasov
  * @version  V1.1.0
  * @date     05.2013
  * @brief    This file provides firmware functions necessary for management of
  *           the LCD supported processes.
  *
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "chip.h"                        /* SAM4S definitions                */
#include "LED.h"

/* Private typedef -----------------------------------------------------------*/
/* None */

/* Private define ------------------------------------------------------------*/
/** Led0 pin */
#define PIN_LED_0 {PIO_PB3, PIOB, ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT}

Pin pin_LED0 = PIN_LED_0;

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/

/**
  * @brief  This function ...
  * @param  None
  * @retval None
  */
void LedInit(void)
{
	
	
	PIO_Configure(&pin_LED0, 1);
}


/**
  * @brief  This function ...
  * @param  None
  * @retval None
  */
void LedOn( void )
{
	
	
	PIO_Set(&pin_LED0);
}


/**
  * @brief  This function ...
  * @param  None
  * @retval None
  */
void LedOff( void )
{
	
	
	PIO_Clear(&pin_LED0);
}


/**
  * @brief  This function ...
  * @param  None
  * @retval None
  */
void LedToggle( void )
{
	
	if( PIO_GetOutputDataStatus(&pin_LED0) )
	{
		PIO_Clear(&pin_LED0);
	}
	else
	{
		PIO_Set(&pin_LED0);
	}
}

/******************* (C) COPYRIGHT 2014 Dimitech Pty Ltd   *****END OF FILE****/
