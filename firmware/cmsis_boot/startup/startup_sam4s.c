/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following condition is met:
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

#include "chip.h"

/* Initialize segments */
extern uint32_t _sfixed;
extern uint32_t _efixed;
extern uint32_t _etext;
extern uint32_t _srelocate;
extern uint32_t _erelocate;
extern uint32_t _szero;
extern uint32_t _ezero;
extern uint32_t _sstack;
extern uint32_t _estack;

/** \cond DOXYGEN_SHOULD_SKIP_THIS */
int main(void);
void LedOn(void);
/** \endcond */

void __libc_init_array(void);

/* Default Reset handler */
void Reset_Handler(void);

/* Default empty handler */
void Dummy_Handler(void);

/* Cortex-M4 core handlers */
void NMI_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void HardFault_Handler  ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void MemManage_Handler  ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void BusFault_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void UsageFault_Handler ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SVC_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void DebugMon_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PendSV_Handler     ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SysTick_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));

/* Peripherals handlers */
void SUPC_IRQHandler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void RSTC_IRQHandler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void RTC_IRQHandler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void RTT_IRQHandler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void WDT_IRQHandler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PMC_IRQHandler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void EFC_IRQHandler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void UART0_IRQHandler      ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void UART1_IRQHandler      ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#ifdef _SAM4S_SMC_INSTANCE_
void SMC_IRQHandler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAM4S_SMC_INSTANCE_ */
void PIOA_IRQHandler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PIOB_IRQHandler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#ifdef _SAM4S_PIOC_INSTANCE_
void PIOC_IRQHandler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAM4S_PIOC_INSTANCE_ */
void USART0_IRQHandler     ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#ifdef _SAM4S_USART1_INSTANCE_
void USART1_IRQHandler     ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAM4S_USART1_INSTANCE_ */
#ifdef _SAM4S_HSMCI_INSTANCE_
void HSMCI_IRQHandler      ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAM4S_HSMCI_INSTANCE_ */
void TWI0_IRQHandler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TWI1_IRQHandler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SPI_IRQHandler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SSC_IRQHandler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC0_IRQHandler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC1_IRQHandler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC2_IRQHandler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#ifdef _SAM4S_TC1_INSTANCE_
void TC3_IRQHandler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC4_IRQHandler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC5_IRQHandler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAM4S_TC1_INSTANCE_ */
void ADC_IRQHandler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void DACC_IRQHandler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PWM_IRQHandler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void CRCCU_IRQHandler      ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void ACC_IRQHandler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void UDP_IRQHandler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));

/* Exception Table */
__attribute__ ((section(".vectors")))
const DeviceVectors exception_table = {

	/* Configure Initial Stack Pointer, using linker-generated symbols */
	(void*) (&_estack),
	(void*) Reset_Handler,

	(void*) NMI_Handler,
	(void*) HardFault_Handler,
	(void*) MemManage_Handler,
	(void*) BusFault_Handler,
	(void*) UsageFault_Handler,
	(void*) (0UL),           /* Reserved */
	(void*) (0UL),           /* Reserved */
	(void*) (0UL),           /* Reserved */
	(void*) (0UL),           /* Reserved */
	(void*) SVC_Handler,
	(void*) DebugMon_Handler,
	(void*) (0UL),           /* Reserved */
	(void*) PendSV_Handler,
	(void*) SysTick_Handler,

	/* Configurable interrupts */
	(void*) SUPC_IRQHandler,    /* 0  Supply Controller */
	(void*) RSTC_IRQHandler,    /* 1  Reset Controller */
	(void*) RTC_IRQHandler,     /* 2  Real Time Clock */
	(void*) RTT_IRQHandler,     /* 3  Real Time Timer */
	(void*) WDT_IRQHandler,     /* 4  Watchdog Timer */
	(void*) PMC_IRQHandler,     /* 5  PMC */
	(void*) EFC_IRQHandler,     /* 6  EEFC */
	(void*) (0UL),           /* 7  Reserved */
	(void*) UART0_IRQHandler,   /* 8  UART0 */
	(void*) UART1_IRQHandler,   /* 9  UART1 */
#ifdef _SAM4S_SMC_INSTANCE_
	(void*) SMC_IRQHandler,     /* 10 SMC */
#else
	(void*) (0UL),           /* 10 Reserved */
#endif /* _SAM4S_SMC_INSTANCE_ */
	(void*) PIOA_IRQHandler,    /* 11 Parallel IO Controller A */
	(void*) PIOB_IRQHandler,    /* 12 Parallel IO Controller B */
#ifdef _SAM4S_PIOC_INSTANCE_
	(void*) PIOC_IRQHandler,    /* 13 Parallel IO Controller C */
#else
	(void*) (0UL),           /* 13 Reserved */
#endif /* _SAM4S_PIOC_INSTANCE_ */
	(void*) USART0_IRQHandler,  /* 14 USART 0 */
#ifdef _SAM4S_USART1_INSTANCE_
	(void*) USART1_IRQHandler,  /* 15 USART 1 */
#else
	(void*) (0UL),           /* 15 Reserved */
#endif /* _SAM4S_USART1_INSTANCE_ */
	(void*) (0UL),           /* 16 Reserved */
	(void*) (0UL),           /* 17 Reserved */
#ifdef _SAM4S_HSMCI_INSTANCE_
	(void*) HSMCI_IRQHandler,   /* 18 MCI */
#else
	(void*) (0UL),           /* 18 Reserved */
#endif /* _SAM4S_HSMCI_INSTANCE_ */
	(void*) TWI0_IRQHandler,    /* 19 TWI 0 */
	(void*) TWI1_IRQHandler,    /* 20 TWI 1 */
	(void*) SPI_IRQHandler,     /* 21 SPI */
	(void*) SSC_IRQHandler,     /* 22 SSC */
	(void*) TC0_IRQHandler,     /* 23 Timer Counter 0 */
	(void*) TC1_IRQHandler,     /* 24 Timer Counter 1 */
	(void*) TC2_IRQHandler,     /* 25 Timer Counter 2 */
#ifdef _SAM4S_TC1_INSTANCE_
	(void*) TC3_IRQHandler,     /* 26 Timer Counter 3 */
	(void*) TC4_IRQHandler,     /* 27 Timer Counter 4 */
	(void*) TC5_IRQHandler,     /* 28 Timer Counter 5 */
#else
	(void*) (0UL),           /* 26 Reserved */
	(void*) (0UL),           /* 27 Reserved */
	(void*) (0UL),           /* 28 Reserved */
#endif /* _SAM4S_TC1_INSTANCE_ */
	(void*) ADC_IRQHandler,     /* 29 ADC controller */
	(void*) DACC_IRQHandler,    /* 30 DAC controller */
	(void*) PWM_IRQHandler,     /* 31 PWM */
	(void*) CRCCU_IRQHandler,   /* 32 CRC Calculation Unit */
	(void*) ACC_IRQHandler,     /* 33 Analog Comparator */
	(void*) UDP_IRQHandler      /* 34 USB Device Port */
};

/**
 * \brief This is the code that gets called on processor reset.
 * To initialize the device, and call the main() routine.
 */
void Reset_Handler(void)
{
	uint32_t *pSrc, *pDest;

	/* Initialize the relocate segment */
	pSrc = &_etext;
	pDest = &_srelocate;

	if (pSrc != pDest) {
		for (; pDest < &_erelocate;) {
			*pDest++ = *pSrc++;
		}
	}

	/* Clear the zero segment */
	for (pDest = &_szero; pDest < &_ezero;) {
		*pDest++ = 0;
	}

	/* Set the vector table base address */
	pSrc = (uint32_t *) & _sfixed;
	SCB->VTOR = ((uint32_t) pSrc & SCB_VTOR_TBLOFF_Msk);

	/* Initialize the C library */
	__libc_init_array();

	/* Branch to main function */
	main();

	/* Infinite loop */
	while (1);
}

/**
 * \brief Default interrupt handler for unused IRQs.
 */
void Dummy_Handler(void)
{
//	LedOn();
	while (1) {
	}
}

