/**
  ******************************************************************************
  * @file     VGA_Out_apps.h
  * @author   Spas Spasov
  * @version  V1.1.0
  * @date     10.2014
  * @brief    This file contains all the functions prototypes for
  *           the VGA Out supported processes firmware library.
  *
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __VGA_OUT_APPS_H
#define __VGA_OUT_APPS_H

/* Includes ------------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
#define H_LINE_SIZE					640
#define V_LINE_SIZE					350

#define HID_VSIZE						H_LINE_SIZE/2
#define VID_VSIZE						V_LINE_SIZE

/* Exported types ------------------------------------------------------------*/
/* None */

/* Exported macro ------------------------------------------------------------*/
/* None */

/* Exported variables --------------------------------------------------------*/
extern volatile uint8_t ga_Write_Block[VID_VSIZE][HID_VSIZE];

/* Exported functions ------------------------------------------------------- */

void StartVGAOut(void);
//void ConfigHVSynchroOut(void);

#endif /* __VGA_OUT_APPS_H */

/******************* (C) COPYRIGHT 2014 Dimitech Pty Ltd   *****END OF FILE****/
