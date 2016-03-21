/**
  ******************************************************************************
  * @file     Drawing_apps.h
  * @author   Spas Spasov
  * @version  V1.1.0
  * @date     10.2014
  * @brief    This file contains all the functions prototypes for
  *           the mSPI supported processes firmware library.
  *
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef DRAWING_APPS_H_
#define DRAWING_APPS_H_

/* Includes ------------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

typedef enum
{
	F_OVERWRITE = 0,
	F_OR,
	F_XOR,
	F_AND
}function_t;

#pragma pack (1)
typedef struct
{
	uint8_t  		command;
	uint8_t  		colour;
	function_t  	function;
	uint8_t  		type;
	uint8_t  		ascii_sym;
	uint8_t  		ascii_font;
	uint8_t  		ascii_type_and_size;
	int16_t  		x1;
	int16_t  		y1;
	int16_t  		x2_rx;
	int16_t  		y2_ry;
}draw_t;

/* Exported macro ------------------------------------------------------------*/
/* None */

/* Exported variables --------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
uint8_t gDrawAPointColour(draw_t *p_draw);
uint8_t gReadAPointColour(draw_t *p_draw);
uint8_t gDrawALineColour(draw_t *p_draw);
uint8_t gDrawARectangleColour(draw_t *p_draw);
uint8_t gDrawAEllipseColour(draw_t *p_draw);
uint8_t gDrawAAsciiSymbolColour(draw_t *p_draw);
uint8_t gSetADrawFrame(draw_t *p_draw);

#endif /* DRAWING_APPS_H_ */

/******************* (C) COPYRIGHT 2014 Dimitech Pty Ltd   *****END OF FILE****/

