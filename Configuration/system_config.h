/* --------------------------- System configuration for nRF51422 ------------------------------- */
/*  File      -  Configuration header file for system-level defines                              */
/*  target    -  nRF51422                                                                        */
/*  toolchain -  IAR                                                                             */
/*  created   -  March, 2024                                                                     */
/* --------------------------------------------------------------------------------------------- */

/************************************   APPLICATION DEFINES   ************************************/
#define APPLICATION_COUNT 3

/*************************************   PERIPHERAL DEFINES   ************************************/
/* SPI */
#define SPI_MOSI_PIN 2
#define SPI_MISO_PIN 3
#define SPI_CS_PIN 4
#define SPI_CLOCK_PIN 1