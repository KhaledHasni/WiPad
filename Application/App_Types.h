/* ----------------------------   Application types for nRF51422   ----------------------------- */
/*  File      -  Application type definition header file                                         */
/*  target    -  nRF51422                                                                        */
/*  toolchain -  IAR                                                                             */
/*  created   -  March, 2024                                                                     */
/* --------------------------------------------------------------------------------------------- */

/******************************************   TYPES   ********************************************/
/**
 * App_tenuStatus Enumeration of the different possible application operation outcomes
*/
typedef enum
{
    Application_Success = 0, /* Operation performed successfully */
    Application_Failure      /* Operation failed                 */
}App_tenuStatus;