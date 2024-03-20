/* ------------------------- Peripheral configuration for nRF52832 ----------------------------- */
/*  File      -  Configuration header file for system-level defines                              */
/*  target    -  nRF52832                                                                        */
/*  toolchain -  IAR                                                                             */
/*  created   -  March, 2024                                                                     */
/* --------------------------------------------------------------------------------------------- */

/******************************************   DEFINES   ******************************************/
/* SPI */
#define SPI_AL_MAX_MASTER_INSTANCE_COUNT 3U
#define SPI_AL_MAX_SLAVE_INSTANCE_COUNT 3U
#define SPI_MOSI_PIN 29
#define SPI_MISO_PIN 30
#define SPI_CS_PIN 31
#define SPI_CLOCK_PIN 26