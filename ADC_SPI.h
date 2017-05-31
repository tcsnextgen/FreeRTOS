
#ifndef ADC_SPI_H
#define ADC_SPI_H

#include "galileo_gen_defs.h"
#include "galileo_support.h"

#define IOH_SPI_ADC_BUS_NUMBER           0x00
#define IOH_SPI_ADC_DEVICE_NUMBER        0x15
#define IOH_SPI_ADC_FUNCTION_NUMBER      0x00
#define R_IOH_SPI_MEMBAR                 0x10


/* **********************************************
 * Initialize the SPI internal register set
 * Return 0 : Read FAiled
 * Return 1 : Read Success
 * **********************************************/
uint32_t uiGalileoInitializeSpiInternal();

/*****************************************
 * SPI read function to read data
 *  Return 0 : Read Failed
 *  Return 1 : Read Success
 *****************************************/
uint32_t uiGalileoSpiRead( uint32_t *uldata );

/***************************************
 * SPI write function to write the data
 * Return 0 : Read FAiled
 * Return 1 : Read Success
 * *************************************/
uint32_t vGalileoSpiWrite( uint32_t uldata );

#endif /* ADC_SPI_H */
