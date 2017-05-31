
/************************************************************************************************
 * NOTE 1:  This project provides a demo application. A simple loop back
 * test and demo application for SPI controller in master mode. SPI_INTERNAL_LOOPBACK_ENABLE
 * macro in the ADC_SPI.c driver should be enabled before running this demo
 * application to configure the SPI controller in internal loop back mode.
 *
 * NOTE 2:  This file only contains the source code that is specific to the
 * basic demo.  Generic functions, such FreeRTOS hook functions, and functions
 * required to configure the hardware are defined in main.c.
 ******************************************************************************
 *
 * See http://www.FreeRTOS.org/RTOS_Intel_Quark_Galileo_GCC.html for usage
 * instructions.
 *
 * main_spi_loop() creates a task. It then starts the scheduler.
 *
 * SPI Internal loop back test Task:
 * A task is created to test the internal loop back of SPI controller.
 * Task sends and receives the 5 words sequentially and compares the sent and received values.
 * Test results will be printed at the end as PASS or FAIL.
 ***************************************************************************************************/

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* Added Galileo SERIAL support */
#include "galileo_support.h"

/* Added ADC SPI driver support */
#include "ADC_SPI.h"

/* Priorities at which the tasks are created. */
#define mainQUEUE_RECEIVE_TASK_PRIORITY		( tskIDLE_PRIORITY + 2 )

 /* The tasks as described in the comments at the top of this file */
static void prvSPIinternalloopbackTask( void *pvParameters );

/* Called by main() to create SPI internal loop back test application if
 * SPI_INTERNAL_LOOPBACK_ENABLE is set to 1. */
void main_spi_loop( void );
/*---------------------------------------------------------------------------------------------------------------*/

void main_spi_loop( void )
{
	uiGalileoInitializeSpiInternal();

	xTaskCreate( prvSPIinternalloopbackTask,		/* The function that implements the task. */
				"spiloopback", 						/* The text name assigned to the task - for debug only as it is not used by the kernel. */
				configMINIMAL_STACK_SIZE * 2,		/* The size of the stack to allocate to the task. */
				NULL, 								/* The parameter passed to the task - not used in this case. */
				mainQUEUE_RECEIVE_TASK_PRIORITY, 	/* The priority assigned to the task. */
				NULL );								/* The task handle is not required, so NULL is passed. */

	vTaskStartScheduler();

	for( ;; );
}
/*--------------------------------------------------------------------------------------------------------*/

static void prvSPIinternalloopbackTask( void *pvParameters )
{
uint32_t ulTxVal=1, ulCount=0, ulReadRes=0;
uint32_t *ulRxVal;

	/* Remove compiler warning about unused parameter. */
	( void ) pvParameters;

	/* Initial cursor position to skip a line) */
	g_printf_rcc( 5, 2, DEFAULT_SCREEN_COLOR, "Galileo board Spi Loop Back Test." );

	for( ;; )
	{
			if(ulCount<6)
			{
				vGalileoSpiWrite(ulTxVal);
				ulReadRes = uiGalileoSpiRead(ulRxVal);

				while(ulReadRes==0)
					ulReadRes = uiGalileoSpiRead(ulRxVal);

				g_printf_rcc(8, 2, DEFAULT_SCREEN_COLOR, "Txdata : %08x rxdata : %08x \r\n", ( int )ulTxVal,*((int *)ulRxVal ));
				ulTxVal++;
				ulCount++;
			}

			if( (( int )ulTxVal-1)==*(( int *)ulRxVal ))
				g_printf_rcc(9, 2, DEFAULT_SCREEN_COLOR, " SPI internal loop back test succeeded \r\n");
			else
				g_printf_rcc(9, 2, DEFAULT_SCREEN_COLOR, "SPI internal loop back test failed \r\n");
	}
}
/*----------------------------------------------------------------------------------------------------------------*/
