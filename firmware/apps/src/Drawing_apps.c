/**
  ******************************************************************************
  * @file     Drawing_apps.c
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
#include "VGA_Out_apps.h"
#include "fonts.h"
#include "Drawing_apps.h"

/* Private typedef -----------------------------------------------------------*/
typedef struct {
	uint16_t  x1;
	uint16_t  y1;
	uint16_t  x2;
	uint16_t  y2;
}windowframe_t;

/* Private define ------------------------------------------------------------*/
#define NUM_OF_FONTS_BYTES			8
#define NUM_OF_PIXELS_OF_ROW		8
#define NUM_OF_COLLONS				8

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static windowframe_t windowframe = {0,0,H_LINE_SIZE,V_LINE_SIZE};
const unsigned char * const gap_fonts[] =
{
		Sinclair_S,
		Sinclair_Inverted_S
};

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief
  * @param  None
  * @retval None
  */
static uint8_t sDrawAPixel( draw_t *p_drawpoint )
{
uint8_t result = 1, count, tmp_colour, colour;
uint16_t x_coordinate, y_coordinate;
function_t	function;


	x_coordinate = (uint16_t)p_drawpoint->x1;
	y_coordinate = (uint16_t)p_drawpoint->y1;

	if( (x_coordinate < windowframe.x1) || (x_coordinate > windowframe.x2))
	{
		result = 0;
		return(result);
	}
	if( (y_coordinate < windowframe.y1) || (y_coordinate > windowframe.y2))
	{
		result = 0;
		return(result);
	}

	function 	= 	p_drawpoint->function;
	colour  	= 	p_drawpoint->colour;
	colour 		&= 	0x0F;
	tmp_colour = ga_Write_Block[y_coordinate][x_coordinate/2];
	if( x_coordinate & 1 )
	{
		if( function == F_OVERWRITE )
		{
			tmp_colour &= 0xF0;
			tmp_colour |= colour;
		}
		else if( function == F_OR )
		{
			tmp_colour |= colour;
		}
		else if( function == F_XOR )
		{
			tmp_colour |= (colour & (tmp_colour & 0x0F));
		}
		else if( function == F_AND )
		{
			tmp_colour |= (colour ^ (tmp_colour & 0x0F));
		}
		else
		{
			return(result);
		}
	}
	else
	{
		if( function == F_OVERWRITE )
		{
			tmp_colour &= 0x0F;
			tmp_colour |= (colour << 4);
		}
		else if( function == F_OR )
		{
			tmp_colour |= (colour << 4);
		}
		else if( function == F_XOR )
		{
			tmp_colour |= ((colour << 4) & (tmp_colour & 0xF0));
		}
		else if( function == F_AND )
		{
			tmp_colour |= ((colour << 4) ^ (tmp_colour & 0xF0));
		}
		else
		{
			return(result);
		}

	}

	for( count = 0; count < 3; count++ )
	{
		ga_Write_Block[y_coordinate][x_coordinate/2] = tmp_colour;
		if( ga_Write_Block[y_coordinate][x_coordinate/2] == tmp_colour)
		{
			result = 0;
			break;
		}
	}
	return(result);
}


/**
  * @brief
  * @param  None
  * @retval
  */
static uint8_t sDrawAHorLineColourFast( draw_t *p_draw )
{
uint8_t result = 1;


int16_t  x1, dx;

	if( p_draw->x2_rx > p_draw->x1 )
	{
	  dx = p_draw->x2_rx - p_draw->x1;
	  x1 = p_draw->x1;
	}
	else
	{
	  dx = p_draw->x1 - p_draw->x2_rx;
	  x1 = p_draw->x2_rx;
	}

	if( (p_draw->y1 < windowframe.y1) || (p_draw->y1 > windowframe.y2))
	{
		result = 0;
		return(result);
	}

register uint8_t count, tmp_colour, colour;
register uint16_t x_coordinate, y_coordinate;
register function_t	function;
register int16_t  i;

	x_coordinate 	= x1;
	y_coordinate 	= p_draw->y1;
	function 		= 	p_draw->function;
	colour  		= 	p_draw->colour;
	colour 			&= 	0x0F;

	for( i = 0; i < dx; i++ )
	{
		tmp_colour = ga_Write_Block[y_coordinate][x_coordinate/2];
		if( x_coordinate & 1 )
		{
			if( function == F_OVERWRITE )
			{
				tmp_colour &= 0xF0;
				tmp_colour |= colour;
			}
			else if( function == F_OR )
			{
				tmp_colour |= colour;
			}
			else if( function == F_XOR )
			{
				tmp_colour |= (colour & (tmp_colour & 0x0F));
			}
			else if( function == F_AND )
			{
				tmp_colour |= (colour ^ (tmp_colour & 0x0F));
			}
			else
			{
				return(result);
			}
		}
		else
		{
			if( function == F_OVERWRITE )
			{
				tmp_colour &= 0x0F;
				tmp_colour |= (colour << 4);
			}
			else if( function == F_OR )
			{
				tmp_colour |= (colour << 4);
			}
			else if( function == F_XOR )
			{
				tmp_colour |= ((colour << 4) & (tmp_colour & 0xF0));
			}
			else if( function == F_AND )
			{
				tmp_colour |= ((colour << 4) ^ (tmp_colour & 0xF0));
			}
			else
			{
				return(result);
			}

		}

		for( count = 0; count < 3; count++ )
		{
			ga_Write_Block[y_coordinate][x_coordinate/2] = tmp_colour;
			if( ga_Write_Block[y_coordinate][x_coordinate/2] == tmp_colour)
			{
				result = 0;
				break;
			}
		}
		x_coordinate++;
	}
	return(result);
}


/* Public functions ----------------------------------------------------------*/

/**
  * @brief
  * @param  None
  * @retval
  */
uint8_t gDrawAPointColour( draw_t *p_draw )
{
uint8_t result;


	if( (p_draw->x1 < 0) || (p_draw->x1 > H_LINE_SIZE) ||
		(p_draw->x2_rx < 0) || (p_draw->x2_rx > H_LINE_SIZE) ||
		(p_draw->y1 < 0) || (p_draw->y1 > V_LINE_SIZE) ||
		(p_draw->y2_ry < 0) || (p_draw->y2_ry > V_LINE_SIZE) )
	{
		result = 1;
		return(result);
	}
	result = sDrawAPixel( p_draw );
	return(result);
}


/**
  * @brief
  * @param  None
  * @retval
  */
uint8_t gReadAPointColour( draw_t *p_draw )
{
uint8_t result, tmp_colour;
uint16_t x_coordinate, y_coordinate;


	if( (p_draw->x1 < 0) || (p_draw->x1 > H_LINE_SIZE) ||
			(p_draw->x2_rx < 0) || (p_draw->x2_rx > H_LINE_SIZE) ||
			(p_draw->y1 < 0) || (p_draw->y1 > V_LINE_SIZE) ||
			(p_draw->y2_ry < 0) || (p_draw->y2_ry > V_LINE_SIZE) )
	{
		result = 1;
		return(result);
	}

	x_coordinate = (uint16_t)p_draw->x1;
	y_coordinate = (uint16_t)p_draw->y1;
	tmp_colour = ga_Write_Block[y_coordinate][x_coordinate/2];
	if( x_coordinate & 1 )
	{
		tmp_colour &= 0x0F;
	}
	else
	{
		tmp_colour &= 0xF0;
		tmp_colour >>= 4;
	}
	p_draw->colour = tmp_colour;
	result = 0;
	return(result);
}


/**
  * @brief
  * @param  None
  * @retval
  */
uint8_t gDrawALineColour( draw_t *p_draw )
{
uint8_t result;


	if( (p_draw->x1 < 0) || (p_draw->x1 > H_LINE_SIZE) ||
			(p_draw->x2_rx < 0) || (p_draw->x2_rx > H_LINE_SIZE) ||
			(p_draw->y1 < 0) || (p_draw->y1 > V_LINE_SIZE) ||
			(p_draw->y2_ry < 0) || (p_draw->y2_ry > V_LINE_SIZE) )
	{
		result = 1;
		return(result);
	}

	if( p_draw->y2_ry == p_draw->y1 )
	{
		if(p_draw->x2_rx == p_draw->x1)
		{
			result = sDrawAPixel( p_draw );
		}
		else
		{
			result = sDrawAHorLineColourFast( p_draw );
		}
		return(result);
	}

int16_t  x, y, addx, addy, dx, dy;
int32_t  P;
int16_t  i;

	if( p_draw->x2_rx >= p_draw->x1 )
	{
	  dx = p_draw->x2_rx - p_draw->x1;
	}
	else
	{
	  dx = p_draw->x1 - p_draw->x2_rx;
	}

	if( p_draw->y2_ry >= p_draw->y1 )
	{
	  dy = p_draw->y2_ry - p_draw->y1;
	}
	else
	{
		dy = p_draw->y1 - p_draw->y2_ry;
	}

	x = p_draw->x1;
	y = p_draw->y1;

	if(p_draw->x1 > p_draw->x2_rx)
	{
		addx = -1;
	}
	else
	{
		addx = 1;
	}
	if(p_draw->y1 > p_draw->y2_ry)
	{
		addy = -1;
	}
	else
	{
		addy = 1;
	}

	if(dx >= dy)
	{
	  P = 2*dy - dx;
	  for( i=0; i<=dx; i++ )
	  {
	  	p_draw->x1 = x;
	  	p_draw->y1 = y;
	  	result = sDrawAPixel( p_draw );

	  	if(P < 0)
	  	{
	  	  P += 2*dy;
	  	  x += addx;
	  	}
	  	else
	  	{
	  	  P += 2*dy - 2*dx;
	  	  x += addx;
	  	  y += addy;
	  	}
	  }
	}
	else
	{
	  P = 2*dx - dy;
	  for(i=0; i<=dy; ++i)
	  {
	  	p_draw->x1 = x;
	  	p_draw->y1 = y;
	  	result = sDrawAPixel( p_draw );

	  	if(P < 0)
	  	{
	  	  P += 2*dx;
	      y += addy;
	    }
	    else
	    {
	      P += 2*dx - 2*dy;
	      x += addx;
	      y += addy;
	    }
	  }
	}

	return(result);
}


/**
  * @brief
  * @param  None
  * @retval
  */
uint8_t gDrawARectangleColour( draw_t *p_draw )
{
uint8_t result;

	if( (p_draw->x1 < 0) || (p_draw->x1 > H_LINE_SIZE) ||
			(p_draw->x2_rx < 0) || (p_draw->x2_rx > H_LINE_SIZE) ||
			(p_draw->y1 < 0) || (p_draw->y1 > V_LINE_SIZE) ||
			(p_draw->y2_ry < 0) || (p_draw->y2_ry > V_LINE_SIZE) )
	{
		result = 1;
		return(result);
	}

uint16_t left, right, top, bottom, temp, i;
uint8_t flag_fill = 0;

	left		= p_draw->x1;
	right		= p_draw->x2_rx;
	top 		= p_draw->y1;
	bottom 	= p_draw->y2_ry;

	if( (left == right) || (top == bottom) )
	{
		result = gDrawALineColour( p_draw );
		return(result);
	}

	if( top > bottom)
	{
		temp 		= top;
		top			= bottom;
		bottom		= temp;
	}
	if( left > right )
	{
		temp		= left;
		left		= right;
		right		= temp;
	}
	do
	{
		for( i = 0; (left + i) <= right; i++ )
		{
			p_draw->x1 = left + i;
			p_draw->y1 = top;
			result |= sDrawAPixel( p_draw );
			p_draw->y1 = bottom;
			result |= sDrawAPixel( p_draw );
		}
		for( i = 0; (top + i) <= bottom; i ++ )
		{
			p_draw->y1 = top + i;
			p_draw->x1 = left;
			result |= sDrawAPixel( p_draw );
			p_draw->x1 = right;
			result |= sDrawAPixel( p_draw );
		}

		if( p_draw->type )				/* if TYPE is "Fill" ... */
		{
			flag_fill = 1;
			if( (right - left) <= 2 )
			{
				right--;
				p_draw->x1 		= left;
				p_draw->y1 		= top;
				p_draw->x2_rx	= right;
				p_draw->y2_ry	= bottom;
				result |= gDrawALineColour( p_draw );
				flag_fill = 0;
			}
			else if( (bottom - top) <= 2 )
			{
				bottom--;
				p_draw->x1 		= left;
				p_draw->y1 		= top;
				p_draw->x2_rx	= right;
				p_draw->y2_ry	= bottom;
				result |= gDrawALineColour( p_draw );
				flag_fill = 0;
			}
			else
			{
				left++;
				right--;
				top++;
				bottom--;
			}
		}
	}
	while( flag_fill );

	return(result);
}


/**
  * @brief
  * @param  None
  * @retval
  */
uint8_t gDrawAAsciiSymbolColour( draw_t *p_draw )
{
uint8_t 	result = 0;
uint8_t 	tmp_pixel;
uint8_t 	tmp_bcount, tmp_min_bcount;
uint8_t 	num_of_pixels_of_row;
uint8_t 	tmp_bytes = 0;
uint32_t 	tmp_num_of_fonts_bytes;
uint8_t 	tmp_num_of_collons;
uint8_t 	tmp_num_of_max_collons;
int16_t  	x, y;
const uint8_t* ptmp_font;
const uint8_t* ptmp_char;


	x = p_draw->x1;
	y = p_draw->y1;

	num_of_pixels_of_row = NUM_OF_PIXELS_OF_ROW;
	tmp_num_of_fonts_bytes = NUM_OF_FONTS_BYTES;
	tmp_num_of_max_collons	= NUM_OF_COLLONS;
	ptmp_font = (const uint8_t*)gap_fonts[p_draw->ascii_font];
	ptmp_char = ptmp_font + 4 + p_draw->ascii_sym * tmp_num_of_fonts_bytes;

	for( tmp_num_of_collons = 0; tmp_num_of_collons < tmp_num_of_max_collons; tmp_num_of_collons++ )
	{
			for( tmp_pixel = num_of_pixels_of_row; tmp_pixel > 0; )
			{
				if( tmp_pixel >= 8 )
				{
					tmp_min_bcount = 0;
				}
				else
				{
					tmp_min_bcount = 8 - tmp_pixel;
				}
				tmp_bcount = 8;
				do
				{
					if( (1 << (tmp_bcount-1)) & ptmp_char[tmp_bytes] )
					{
				  	p_draw->x1 = x;
				  	p_draw->y1 = y;
						result |= sDrawAPixel( p_draw );
					}
					x++;
					tmp_bcount--;
				}
				while(tmp_bcount > tmp_min_bcount);

				tmp_bytes++;
				tmp_pixel -= 8;
			}
			x -= num_of_pixels_of_row;
			y++;
	}

	return(result);
}


/**
  * @brief
  * @param  None
  * @retval
  */
uint8_t gDrawAEllipseColour( draw_t *p_draw )
{
uint8_t result = 0;
int32_t width, height;
int32_t a2, b2;
int32_t fa2, fb2;
int32_t x0, y0, x, y, sigma;


	x0 = p_draw->x1;
	y0 = p_draw->y1;
	width = p_draw->x2_rx;
	height = p_draw->y2_ry;

	a2 = width * width;
	b2 = height * height;
	fa2 = 4 * a2;
	fb2 = 4 * b2;

	/* first half */
	for (x = 0, y = height, sigma = 2*b2+a2*(1-2*height); b2*x <= a2*y; x++)
	{
		if( p_draw->type == 0 )
		{
			p_draw->x1 = (int16_t)(x0 + x);
			p_draw->y1 = (int16_t)(y0 + y);
			result |= sDrawAPixel( p_draw );

			p_draw->x1 = (int16_t)(x0 - x);
			p_draw->y1 = (int16_t)(y0 + y);
			result |= sDrawAPixel( p_draw );

			p_draw->x1 = (int16_t)(x0 + x);
			p_draw->y1 = (int16_t)(y0 - y);
			result |= sDrawAPixel( p_draw );

			p_draw->x1 = (int16_t)(x0 - x);
			p_draw->y1 = (int16_t)(y0 - y);
			result |= sDrawAPixel( p_draw );
		}

		if (sigma >= 0)
		{
			if( p_draw->type )				/* if TYPE is "Fill" ... */
			{
				p_draw->x1 		= x0 - x;
				p_draw->y1 		= y0 + y;
				p_draw->x2_rx	= x0 + x;
				p_draw->y2_ry	= y0 + y;
				result |= gDrawALineColour( p_draw );

				p_draw->x1 		= x0 - x;
				p_draw->y1 		= y0 - y;
				p_draw->x2_rx	= x0 + x;
				p_draw->y2_ry	= y0 - y;
				result |= gDrawALineColour( p_draw );
			}
			sigma += fa2 * (1 - y);
			y--;
		}
		sigma += b2 * ((4 * x) + 6);
	}

	/* second half */
	for (x = width, y = 0, sigma = 2*a2+b2*(1-2*width); a2*y <= b2*x; y++)
	{
		if( p_draw->type == 0 )
		{
			p_draw->x1 = (int16_t)(x0 + x);
			p_draw->y1 = (int16_t)(y0 + y);
			result |= sDrawAPixel( p_draw );

			p_draw->x1 = (int16_t)(x0 - x);
			p_draw->y1 = (int16_t)(y0 + y);
			result |= sDrawAPixel( p_draw );

			p_draw->x1 = (int16_t)(x0 + x);
			p_draw->y1 = (int16_t)(y0 - y);
			result |= sDrawAPixel( p_draw );

			p_draw->x1 = (int16_t)(x0 - x);
			p_draw->y1 = (int16_t)(y0 - y);
			result |= sDrawAPixel( p_draw );
		}
		else				/* if TYPE is "Fill" ... */
		{
			p_draw->x1 		= x0 - x;
			p_draw->y1 		= y0 + y;
			p_draw->x2_rx	= x0 + x;
			p_draw->y2_ry	= y0 + y;
			result |= gDrawALineColour( p_draw );

			p_draw->x1 		= x0 - x;
			p_draw->y1 		= y0 - y;
			p_draw->x2_rx	= x0 + x;
			p_draw->y2_ry	= y0 - y;
			result |= gDrawALineColour( p_draw );
		}

		if (sigma >= 0)
		{
			sigma += fb2 * (1 - x);
			x--;
		}
		sigma += a2 * ((4 * y) + 6);
	}

	return(result);
}


/**
  * @brief
  * @param  None
  * @retval
  */
uint8_t gSetADrawFrame( draw_t *p_draw )
{
uint16_t x1_coordinate, y1_coordinate, x2_coordinate, y2_coordinate;


	if( (p_draw->x1 < 0) || (p_draw->x1 > H_LINE_SIZE) ||
			(p_draw->x2_rx < 0) || (p_draw->x2_rx > H_LINE_SIZE) ||
			(p_draw->y1 < 0) || (p_draw->y1 > V_LINE_SIZE) ||
			(p_draw->y2_ry < 0) || (p_draw->y2_ry > V_LINE_SIZE) )
	{
		return(1);
	}
	x1_coordinate = (uint16_t)p_draw->x1;
	y1_coordinate = (uint16_t)p_draw->y1;
	x2_coordinate = (uint16_t)p_draw->x2_rx;
	y2_coordinate = (uint16_t)p_draw->y2_ry;

	if( x1_coordinate > x2_coordinate )
	{
		windowframe.x2 = x1_coordinate;
		windowframe.x1 = x2_coordinate;
	}
	else
	{
		windowframe.x1 = x1_coordinate;
		windowframe.x2 = x2_coordinate;
	}

	if( y1_coordinate > y2_coordinate )
	{
		windowframe.y2 = y1_coordinate;
		windowframe.y1 = y2_coordinate;
	}
	else
	{
		windowframe.y1 = y1_coordinate;
		windowframe.y2 = y2_coordinate;
	}
	return(0);
}


/******************* (C) COPYRIGHT 2014 Dimitech Pty Ltd   *****END OF FILE****/

