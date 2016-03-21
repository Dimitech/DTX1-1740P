/**
  ******************************************************************************
  * @file     mspi_apps.c
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
#include "mspi_apps.h"

/* Private typedef -----------------------------------------------------------*/
/* None */

/* Private define ------------------------------------------------------------*/
/** SPI pins */
#define PIN_MSPI_MISO 						{PIO_PA12, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_MSPI_MISO_FLOW 					{PIO_PA12, PIOA, ID_PIOA, PIO_INPUT, PIO_DEFAULT}
#define PIN_MSPI_MOSI 						{PIO_PA12, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_MSPI_SPCK 						{PIO_PA14, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

/** mSPI mSS pin */
#define PIN_MSPI_MSS 						{PIO_PA11, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

#define MSPI         						SPI
#define MSPI_CS_NUM         				0

#define MSPI_DTX_1740_ADDRESS				0x17
#define EPTY_TX_SPI_BUFF					0

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
Pin pins_MSPI[] = {PIN_MSPI_MSS, PIN_MSPI_MISO_FLOW, PIN_MSPI_MOSI, PIN_MSPI_SPCK};

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
 * \brief Interrupt handler for PIOA Controller.
 */
void PIOA_IRQHandler( void )
{
volatile uint32_t dummy;

	dummy = PIOA->PIO_ISR;
}


/**
 * \brief Interrupt handler for SPI.
 */
void SPI_IRQHandler( void )
{
volatile uint32_t dummy;

	dummy = SPI->SPI_SR;
}


/**
  * @brief
  * @param  None
  * @retval None
  */
static void mSpiPinsInit( void )
{


	/* pin PA11 - mSS, pin PA12 - MISO, pin PA12 - MOSI, pin PA12 - SPCK,  */
	PIO_Configure(pins_MSPI, PIO_LISTSIZE(pins_MSPI));
}


/* Public functions ----------------------------------------------------------*/

/**
  * @brief
  * @param  None
  * @retval None
  */
void mSpiSart( void )
{


	mSpiPinsInit();
	SPI_Configure( MSPI, ID_SPI, SPI_MR_PCS(0) | SPI_MR_DLYBCS(6));
	SPI_ConfigureNPCS( MSPI,MSPI_CS_NUM, SPI_CSR_CPOL | SPI_CSR_BITS_8_BIT | SPI_CSR_SCBR(20) );
	SPI_Read( MSPI );
	SPI_Write( MSPI, MSPI_CS_NUM, EPTY_TX_SPI_BUFF );
	SPI_EnableIt( MSPI, SPI_IER_RDRF );
	SPI_Enable( MSPI );
}


/******************* (C) COPYRIGHT 2014 Dimitech Pty Ltd   *****END OF FILE****/
