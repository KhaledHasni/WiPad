/* -------------------------   User registration app for nRF51422   ---------------------------- */
/*  File      -  User registration application source file                                       */
/*  target    -  nRF51422                                                                        */
/*  toolchain -  IAR                                                                             */
/*  created   -  March, 2024                                                                     */
/* --------------------------------------------------------------------------------------------- */

/****************************************   INCLUDES   *******************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "Registration.h"

/************************************   GLOBAL VARIABLES   ***************************************/
extern App_tenuStatus AppMgr_enuDispatchEvent(uint32_t u32Event);

/************************************   PRIVATE VARIABLES   **************************************/
static TaskHandle_t pvUseRegTaskHandle;
static EventGroupHandle_t pvUseRegEventGroupHandle;

/************************************   PRIVATE FUNCTIONS   **************************************/
static void vidUseRegTaskFunction(void *pvArg)
{
    uint32_t u32Event;

    /* User registration task's main polling loop */
    while(1)
    {
        /* Task will remain blocked until an event is set in event group */
        u32Event = xEventGroupWaitBits(pvUseRegEventGroupHandle,
                                       APP_USE_REG_EVENT_MASK,
                                       pdTRUE,
                                       pdTRUE,
                                       portMAX_DELAY);
        if(u32Event)
        {
            __NOP();
        }
    }
}

/************************************   PUBLIC FUNCTIONS   ***************************************/
App_tenuStatus enuRegistration_Init(void)
{
    App_tenuStatus enuRetVal = Application_Failure;

    /* Create task for User registration application */
    if(pdPASS == xTaskCreate(vidUseRegTaskFunction,
                             "APP_UseReg_Task",
                             APP_USEREG_TASK_STACK_SIZE,
                             NULL,
                             APP_USEREG_TASK_PRIORITY,
                             &pvUseRegTaskHandle))
    {
        /* Create event group for User registration application */
        pvUseRegEventGroupHandle = xEventGroupCreate();
        enuRetVal = (NULL != pvUseRegEventGroupHandle)?Application_Success:Application_Failure;
    }

    return enuRetVal;
}

App_tenuStatus enuRegistration_GetNotified(uint32_t u32Event)
{
    return xEventGroupSetBits(pvUseRegEventGroupHandle, u32Event)?Application_Success:Application_Failure;
}