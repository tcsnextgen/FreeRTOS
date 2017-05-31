/* SPI Controller driver to communicate with ADC on Intel Galileo Gen2
 * board.
 */
#include "ADC_SPI.h"

#define SPI_INTERNAL_LOOPBACK_ENABLE  1 /* 0- To disable SPI Internal loop back test */
#define SPI_SSCR0_INIT	0x00000089
#define SPI_INTERNAL_LOOPBACK	0x00000004
#define SPI_SSCR0_OFFSET	0x00 /* SSCR0 offset address */
#define SPI_SSCR1_OFFSET	0x04 /* SSCR1 offset address */
#define SPI_STATUS_REG_OFFSET	0x08 /* SPI status register offset */
#define SPI_RW_OFFET	0x10 /* SPI read and write register offset */

static uint8_t ucbus = IOH_SPI_ADC_BUS_NUMBER;
static uint8_t ucdevice = IOH_SPI_ADC_DEVICE_NUMBER;
static uint8_t ucfunc = IOH_SPI_ADC_FUNCTION_NUMBER;
static uint32_t	ulport_baddr;

/* Get the SPI controller port base address */
static uint32_t prvGetSpiPortBaddr( void );
/* Initialize the Memory space for SPI port */
static void vprvEnableSpiMmioSpace(void);

static uint32_t prvGetSpiPortBaddr( void )
{
uint32_t ulcont_baddr = MMIO_PCI_ADDRESS(ucbus, ucdevice, ucfunc, 0);
uint32_t ulport_baddr = mem_read(ulcont_baddr, R_IOH_SPI_MEMBAR, 4);

	return ulport_baddr;
}
/*--------------------------------------------------------------------------*/

static void vprvEnableSpiMmioSpace( void )
{
uint32_t ulcont_baddr = MMIO_PCI_ADDRESS(ucbus, ucdevice, ucfunc, 0);
uint8_t ucpcicmd = mem_read(ulcont_baddr, PCI_REG_PCICMD, 1);

	mem_write(ulcont_baddr, PCI_REG_PCICMD, 1, (ucpcicmd | 0x7));

  return;
}
/*-------------------------------------------------------------------------------------------*/

uint32_t uiGalileoInitializeSpiInternal()
{
uint32_t uladdr=0;
uint32_t uldata=0;

	vprvEnableSpiMmioSpace();
	ulport_baddr = prvGetSpiPortBaddr();

	/* Configure SPI Control Register 0 (SSCR0) */
	uladdr = ulport_baddr + SPI_SSCR0_OFFSET;
	uldata = *((volatile uint32_t *) (uintn_t)(uladdr));
	uldata |= SPI_SSCR0_INIT;
	*((volatile uint32_t *) (uintn_t)(uladdr)) = uldata;

	/* Configure SPI Control Register 1 (SSCR1) */
	uladdr = ulport_baddr + SPI_SSCR1_OFFSET;
	uldata = *((volatile uint32_t *) (uintn_t)(uladdr));
#if SPI_INTERNAL_LOOPBACK_ENABLE
	uldata |= SPI_INTERNAL_LOOPBACK;  /* Loop Back Mode is enabled */
#else
	uldata = 0;
#endif
	*((volatile uint32_t *) (uintn_t)(uladdr)) = uldata;

	return 1;
}
/*--------------------------------------------------------------------------------*/

uint32_t uiGalileoSpiRead( uint32_t *uldata )
{
uint32_t uladdr =0;

	uladdr = ulport_baddr + SPI_STATUS_REG_OFFSET;
	*uldata = *((volatile uint32_t *) (uintn_t)(uladdr));
	if((*uldata) & 0x00000008)
	{
		uladdr = ulport_baddr + SPI_RW_OFFET;
		*uldata = *((volatile uint32_t *) (uintn_t)(uladdr));
		return 1; /* Data found in Read Register */
	}
	else
	{
		return 0; /* No data found */
	}
}
/*----------------------------------------------------------------------------------------*/

uint32_t vGalileoSpiWrite( uint32_t uldata )
{
uint32_t uladdr =0;
uint32_t ulval=0;

	uladdr = ulport_baddr + SPI_RW_OFFET;
	*((volatile uint32_t *) (uintn_t)(uladdr)) = uldata;
	uladdr = ulport_baddr + 0x08;
	ulval = *((volatile uint32_t *) (uintn_t)(uladdr));
	if(ulval == 0)
		return 0;/* Write Success */
	else
		return 1;/* Write Failed */
}
/*-----------------------------------------------------------------------------------*/
