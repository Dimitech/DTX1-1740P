/**
  ******************************************************************************
  * @file     LED.h
  * @author   Spas Spasov
  * @version  V1.1.0
  * @date     10.2014
  * @brief    This file contains all the functions prototypes for
  *           the LED supported processes firmware library.
  *
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED_H
#define __LED_H

/* Includes ------------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* None */

/* Exported macro ------------------------------------------------------------*/
/* None */

/* Exported variables --------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */

void LedInit(void);
void LedOn(void);
void LedOff(void);
void LedToggle(void);

#endif /* __LED_H */

/******************* (C) COPYRIGHT 2014 Dimitech Pty Ltd   *****END OF FILE****/
