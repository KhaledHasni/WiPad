/* ------------------------------   Driver types for nRF51422   -------------------------------- */
/*  File      -  Driver type definition header file                                              */
/*  target    -  nRF51422                                                                        */
/*  toolchain -  IAR                                                                             */
/*  created   -  March, 2024                                                                     */
/* --------------------------------------------------------------------------------------------- */

/******************************************   TYPES   ********************************************/
/**
 * Drivers_tenuStatus Enumeration of the different possible driver operation outcomes
*/
typedef enum
{
    Driver_Success = 0, /* Operation performed successfully */
    Driver_Failure      /* Operation failed                 */
}Drivers_tenuStatus;