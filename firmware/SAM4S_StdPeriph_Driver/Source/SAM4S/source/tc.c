/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2011, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

/**
 * \file
 *
 * Implementation of Timer Counter (TC).
 *
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "chip.h"

#include <assert.h>

/*------------------------------------------------------------------------------
 *         Global functions
 *------------------------------------------------------------------------------*/

/**
 * \brief Configures a Timer Counter Channel
 *
 * Configures a Timer Counter to operate in the given mode. Timer is stopped
 * after configuration and must be restarted with TC_Start(). All the
 * interrupts of the timer are also disabled.
 *
 * \param pTc  Pointer to a Tc instance.
 * \param channel Channel number.
 * \param mode  Operating mode (TC_CMR value).
 */
extern void TC_Configure( Tc *pTc, uint32_t dwChannel, uint32_t dwMode )
{
    TcChannel* pTcCh ;

    assert( dwChannel < (sizeof( pTc->TC_CHANNEL )/sizeof( pTc->TC_CHANNEL[0] )) ) ;
    pTcCh = pTc->TC_CHANNEL+dwChannel ;

    /*  Disable TC clock */
    pTcCh->TC_CCR = TC_CCR_CLKDIS ;

    /*  Disable interrupts */
    pTcCh->TC_IDR = 0xFFFFFFFF ;

    /*  Clear status register */
    pTcCh->TC_SR ;

    /*  Set mode */
    pTcCh->TC_CMR = dwMode ;
}


/**
 * \brief Configure TC Block mode.
 * \note tc_init() must be called first.
 *
 * \param p_tc Pointer to a TC instance.
 * \param ul_blockmode Block mode register value to set.
 *
 */
void TC_SetBlockMode( Tc *p_tc, uint32_t ul_blockmode )
{
	
	
	p_tc->TC_BMR = ul_blockmode;
}


/**
 * \brief Write RA TC counter on the selected channel.
 *
 * \param p_tc Pointer to a TC instance.
 * \param ul_channel Channel to configure.
 * \param ul_value Value to set in register.
 */
void TC_WriteRa( Tc *p_tc, uint32_t ul_channel, uint32_t ul_value )
{
	assert(ul_channel <
			(sizeof(p_tc->TC_CHANNEL) / sizeof(p_tc->TC_CHANNEL[0])));

	p_tc->TC_CHANNEL[ul_channel].TC_RA = ul_value;
}


/**
 * \brief Write RB TC counter on the selected channel.
 *
 * \param p_tc Pointer to a TC instance.
 * \param ul_channel Channel to configure.
 * \param ul_value Value to set in register.
 */
void TC_WriteRb( Tc *p_tc, uint32_t ul_channel, uint32_t ul_value )
{
	assert(ul_channel <
			(sizeof(p_tc->TC_CHANNEL) / sizeof(p_tc->TC_CHANNEL[0])));

	p_tc->TC_CHANNEL[ul_channel].TC_RB = ul_value;
}


/**
 * \brief Write RC TC counter on the selected channel.
 *
 * \param p_tc Pointer to a TC instance.
 * \param ul_channel Channel to configure.
 * \param ul_value Value to set in register.
 */
void TC_WriteRc( Tc *p_tc, uint32_t ul_channel, uint32_t ul_value )
{
	assert(ul_channel <
			(sizeof(p_tc->TC_CHANNEL) / sizeof(p_tc->TC_CHANNEL[0])));

	p_tc->TC_CHANNEL[ul_channel].TC_RC = ul_value;
}


/**
 * \brief Enable TC interrupts on the selected channel.
 *
 * \param p_tc Pointer to a TC instance.
 * \param ul_channel Channel to configure.
 * \param ul_sources Interrupt sources bit map.
 */
void TC_EnableInterrupt(Tc *p_tc, uint32_t ul_channel, uint32_t ul_sources)
{
TcChannel *tc_channel;

	assert(ul_channel <
			(sizeof(p_tc->TC_CHANNEL) / sizeof(p_tc->TC_CHANNEL[0])));
			
	tc_channel = p_tc->TC_CHANNEL + ul_channel;
	tc_channel->TC_IER = ul_sources;
}


/**
 * \brief Disable TC interrupts on the selected channel.
 *
 * \param p_tc Pointer to a TC instance.
 * \param ul_channel Channel to configure.
 * \param ul_sources Interrupt sources bit map.
 */
void TC_DisableInterrupt( Tc *p_tc, uint32_t ul_channel, uint32_t ul_sources )
{
TcChannel *tc_channel;

	assert(ul_channel <
			(sizeof(p_tc->TC_CHANNEL) / sizeof(p_tc->TC_CHANNEL[0])));
			
	tc_channel = p_tc->TC_CHANNEL + ul_channel;
	tc_channel->TC_IDR = ul_sources;
}

/**
 * \brief Read TC interrupt mask on the selected channel.
 *
 * \param p_tc Pointer to a TC instance.
 * \param ul_channel Channel to configure.
 *
 * \return The interrupt mask value.
 */
uint32_t TC_GetInterruptMask( Tc *p_tc, uint32_t ul_channel )
{
TcChannel *tc_channel;

	assert(ul_channel <
			(sizeof(p_tc->TC_CHANNEL) / sizeof(p_tc->TC_CHANNEL[0])));
			
	tc_channel = p_tc->TC_CHANNEL + ul_channel;
	return tc_channel->TC_IMR;
}

/**
 * \brief Get current status on the selected channel.
 *
 * \param p_tc Pointer to a TC instance.
 * \param ul_channel Channel to configure.
 *
 * \return The current TC status.
 */
uint32_t TC_GetStatus( Tc *p_tc, uint32_t ul_channel )
{
TcChannel *tc_channel;

	assert(ul_channel <
			(sizeof(p_tc->TC_CHANNEL) / sizeof(p_tc->TC_CHANNEL[0])));
			
	tc_channel = p_tc->TC_CHANNEL + ul_channel;
	return tc_channel->TC_SR;
}


/**
 * \brief Reset and Start the TC Channel
 *
 * Enables the timer clock and performs a software reset to start the counting.
 *
 * \param pTc  Pointer to a Tc instance.
 * \param dwChannel Channel number.
 */
extern void TC_Start( Tc *pTc, uint32_t dwChannel )
{
    TcChannel* pTcCh ;

    assert( dwChannel < (sizeof( pTc->TC_CHANNEL )/sizeof( pTc->TC_CHANNEL[0] )) ) ;

    pTcCh = pTc->TC_CHANNEL+dwChannel ;
    pTcCh->TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG ;
}

/**
 * \brief Stop TC Channel
 *
 * Disables the timer clock, stopping the counting.
 *
 * \param pTc     Pointer to a Tc instance.
 * \param dwChannel Channel number.
 */
extern void TC_Stop(Tc *pTc, uint32_t dwChannel )
{
    TcChannel* pTcCh ;

    assert( dwChannel < (sizeof( pTc->TC_CHANNEL )/sizeof( pTc->TC_CHANNEL[0] )) ) ;

    pTcCh = pTc->TC_CHANNEL+dwChannel ;
    pTcCh->TC_CCR = TC_CCR_CLKDIS ;
}

/**
 * \brief Find best MCK divisor
 *
 * Finds the best MCK divisor given the timer frequency and MCK. The result
 * is guaranteed to satisfy the following equation:
 * \code
 *   (MCK / (DIV * 65536)) <= freq <= (MCK / DIV)
 * \endcode
 * with DIV being the highest possible value.
 *
 * \param dwFreq  Desired timer frequency.
 * \param dwMCk  Master clock frequency.
 * \param dwDiv  Divisor value.
 * \param dwTcClks  TCCLKS field value for divisor.
 * \param dwBoardMCK  Board clock frequency.
 *
 * \return 1 if a proper divisor has been found, otherwise 0.
 */
extern uint32_t TC_FindMckDivisor( uint32_t dwFreq, uint32_t dwMCk, uint32_t *dwDiv, uint32_t *dwTcClks, uint32_t dwBoardMCK )
{
//    uint32_t adwDivisors[5] = { 2, 8, 32, 128, dwBoardMCK / 32768 } ;
		uint32_t adwDivisors[5];
    uint32_t dwIndex = 0 ;


		adwDivisors[0] = 2;
		adwDivisors[1] = 8;
		adwDivisors[2] = 32;
		adwDivisors[3] = 128;
		adwDivisors[4] = dwBoardMCK / 32768;
		
    /*  Satisfy lower bound */
    while ( dwFreq < ((dwMCk / adwDivisors[dwIndex]) / 65536) )
    {
        dwIndex++ ;

        /*  If no divisor can be found, return 0 */
        if ( dwIndex == (sizeof( adwDivisors )/sizeof( adwDivisors[0] ))  )
        {
            return 0 ;
        }
    }

    /*  Try to maximize DIV while satisfying upper bound */
    while ( dwIndex < 4 )
    {

        if ( dwFreq > (dwMCk / adwDivisors[dwIndex + 1]) )
        {
            break ;
        }
        dwIndex++ ;
    }

    /*  Store results */
    if ( dwDiv )
    {
        *dwDiv = adwDivisors[dwIndex] ;
    }
    if ( dwTcClks )
    {
        *dwTcClks = dwIndex ;
    }

    return 1 ;
}


/**
 * \brief Enable or disable write protection of TC registers.
 *
 * \param p_tc Pointer to a TC instance.
 * \param ul_enable 1 to enable, 0 to disable.
 */
void TC_SetWriteprotect( Tc *p_tc, uint32_t ul_enable )
{
	
	
	if( ul_enable ) 
	{
		p_tc->TC_WPMR = TC_WPMR_WPKEY_PASSWD | TC_WPMR_WPEN;
	} 
	else 
	{
		p_tc->TC_WPMR = TC_WPMR_WPKEY_PASSWD;
	}
}



