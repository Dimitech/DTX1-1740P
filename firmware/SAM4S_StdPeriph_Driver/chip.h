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

#ifndef SAM4S_CHIP_H
#define SAM4S_CHIP_H

/* Define WEAK attribute */
#if defined   ( __CC_ARM   )
    #define WEAK __attribute__ ((weak))
#elif defined ( __ICCARM__ )
    #define WEAK __weak
#elif defined (  __GNUC__  )
    #define WEAK __attribute__ ((weak))
#endif

/* Define NO_INIT attribute */
#if defined   ( __CC_ARM   )
    #define NO_INIT
#elif defined ( __ICCARM__ )
    #define NO_INIT __no_init
#elif defined (  __GNUC__  )
    #define NO_INIT
#endif

/* Define RAMFUNC attribute */
#ifdef __ICCARM__
#define RAMFUNC __ramfunc
#else
#define RAMFUNC __attribute__ ((section (".ramfunc")))
#endif

/*
 * User defined chip definition
 */
#define __SAM4S8B__

//#define DONT_USE_CMSIS_INIT

/*
 * Peripherals registers definitions
 */
#include "Include/SAM4S/sam4s.h"

/*
 * Core
 */
//#include "Source/SAM4S/include/exceptions.h"

/*
 * Peripherals
 */
#include "Source/SAM4S/include/acc.h"
#include "Source/SAM4S/include/adc.h"
#include "Source/SAM4S/include/async.h"
#include "Source/SAM4S/include/crccu.h"
#include "Source/SAM4S/include/dacc.h"
#include "Source/SAM4S/include/efc.h"
#include "Source/SAM4S/include/flashd.h"
#include "Source/SAM4S/include/hsmci.h"
#include "Source/SAM4S/include/pio.h"
#include "Source/SAM4S/include/pio_it.h"
#include "Source/SAM4S/include/pio_capture.h"
#include "Source/SAM4S/include/pmc.h"
#include "Source/SAM4S/include/pwmc.h"
#include "Source/SAM4S/include/rtc.h"
#include "Source/SAM4S/include/rtt.h"
#include "Source/SAM4S/include/spi.h"
#include "Source/SAM4S/include/spi_pdc.h"
#include "Source/SAM4S/include/ssc.h"
#include "Source/SAM4S/include/tc.h"
#include "Source/SAM4S/include/twi.h"
#include "Source/SAM4S/include/twid.h"
#include "Source/SAM4S/include/usart.h"
#include "Source/SAM4S/include/wdt.h"
#include "Source/SAM4S/include/trace.h"

/* TODO: Temporay add missing definition in CMSIS Version V2.10 */
/* SCB Interrupt Control State Register Definitions */
#ifndef SCB_VTOR_TBLBASE_Pos
#define SCB_VTOR_TBLBASE_Pos               29                                             /*!< SCB VTOR: TBLBASE Position */
#define SCB_VTOR_TBLBASE_Msk               (1UL << SCB_VTOR_TBLBASE_Pos)                  /*!< SCB VTOR: TBLBASE Mask */
#endif

#define 	  Idle						__WFI

#endif /* SAM4S_CHIP_H */
