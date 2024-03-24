/* -------------------------   User Registration app for nRF51422   ---------------------------- */
/*  File      -  User registration application header file                                       */
/*  target    -  nRF51422                                                                        */
/*  toolchain -  IAR                                                                             */
/*  created   -  March, 2024                                                                     */
/* --------------------------------------------------------------------------------------------- */

#ifndef _APP_USEREG_H_
#define _APP_USEREG_H_

/****************************************   INCLUDES   *******************************************/
#include "App_Types.h"
#include "system_config.h"

/*************************************   PUBLIC DEFINES   ****************************************/
#define APP_USE_REG_TEST_EVENT1 (1 << 0)
#define APP_USE_REG_TEST_EVENT2 (1 << 1)
#define APP_USE_REG_EVENT_MASK  (APP_USE_REG_TEST_EVENT1 | APP_USE_REG_TEST_EVENT2)

/************************************   PUBLIC FUNCTIONS   ***************************************/
/**
 * @brief enuRegistration_Init Creates User registration task, event group to receive
 *        notifications from other tasks or events dispatched from BLE stack and registers
 *        callback to report back to Application Manager.
 *
 * @note This function is invoked by the Application Manager.
 *
 * @pre This function requires no prerequisites.
 *
 * @return App_tenuStatus Application_Success if initialization was performed successfully,
 *         Application_Failure otherwise
 */
App_tenuStatus enuRegistration_Init(void);

/**
 * @brief enuRegistration_GetNotified Notifies User registration task of an incoming event by
 *        setting it in local event group.
 *
 * @note This function is invoked by the Application Manager signaling that another task
 *       wants to communicate with the User registration task.
 *
 * @pre This function can't be called unless User registration task is initialized and running.
 *
 * @param u32Event Event to be posted in local event group
 *
 * @return App_tenuStatus Application_Success if notification was posted successfully,
 *         Application_Failure otherwise
 */
App_tenuStatus enuRegistration_GetNotified(uint32_t u32Event);

#endif /* _APP_USEREG_H_ */