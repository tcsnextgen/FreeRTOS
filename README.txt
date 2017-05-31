************************************************************************************************************
              SPI Driver implementation to communicate with ADC on Intel Galileo Board
************************************************************************************************************

Description : Intel Galileo has ADC which is interfaced through SPI Controller. 
              SPI based ADC driver enables the comminucation with ADC through SPI controller.
			  
	      This driver code and and sample application reference code can be used 
	      to read/write the sensor data over SPI for IOT/Industrial applications.
			  

Source Files : ADC_SPI.c and ADC_SPI.h

SPI Loopback Test Source File : main_spi_loopback.c

API List :  
    1) GalileoInitializeSpiInternal() : Initialize the SPI driver/controller.
    2) GalileoSpiRead() :           Read the data over SPI from ADC
    3) vGalileoSpiWrite() : Write the data to ADC over SPI.

Build Procedure : 
    1) Launch the Eclipse IDE and import the existing workspace directory FreeRTOSv9.0.0/FreeRTOS/Demo/IA32_flat_GCC_Galileo_Gen_2
	2) Add both ADC_SPI.c and ADC_SPI.h into the Suport_Files directory through Eclipse. 
	3)Build the source.

Test Procedure: 
    1)Create a New Directory in the Eclipse workspace and add main_spi_loop.c file to the newly created directory.
    2)Replace the main.c with one provided by us through Eclipse.
    3)Enable the SPI_INTERNAL_LOOPBACK_ENABLE macro in ADC_SPI.c for internal loopback test.
    4)Build the source and flash images on to the board.
    5)Observe the internal loopback test results through serial interface in host machine	
	
************************************************************************************************************
************************************************************************************************************
