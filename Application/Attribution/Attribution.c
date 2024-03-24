/* --------------------------   Key attribution app for nRF51422   ----------------------------- */
/*  File      -  Key attribution application source file                                         */
/*  target    -  nRF51422                                                                        */
/*  toolchain -  IAR                                                                             */
/*  created   -  March, 2024                                                                     */
/* --------------------------------------------------------------------------------------------- */

/****************************************   INCLUDES   *******************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "Attribution.h"

/************************************   PRIVATE VARIABLES   **************************************/
static TaskHandle_t pvKeyAttTaskHandle;
static EventGroupHandle_t pvKeyAttEventGroupHandle;

/************************************   PRIVATE FUNCTIONS   **************************************/
static void vidKeyAttTaskFunction(void *pvArg)
{
    uint32_t u32Event;

    /* Key attribution task's main polling loop */
    while(1)
    {
        /* Task will remain blocked until an event is set in event group */
        u32Event = xEventGroupWaitBits(pvKeyAttEventGroupHandle,
                                       APP_KEY_ATT_EVENT_MASK,
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
App_tenuStatus enuAttribution_Init(void)
{
    App_tenuStatus enuRetVal = Application_Failure;

    /* Create task for Key attribution application */
    if(pdPASS == xTaskCreate(vidKeyAttTaskFunction,
                             "APP_KeyAtt_Task",
                             APP_KEYATT_TASK_STACK_SIZE,
                             NULL,
                             APP_KEYATT_TASK_PRIORITY,
                             &pvKeyAttTaskHandle))
    {
        /* Create event group for Key attribution application */
        pvKeyAttEventGroupHandle = xEventGroupCreate();
        enuRetVal = (NULL != pvKeyAttEventGroupHandle)?Application_Success:Application_Failure;
    }
    
    return enuRetVal;
}

App_tenuStatus enuAttribution_GetNotified(uint32_t u32Event)
{
    return xEventGroupSetBits(pvKeyAttEventGroupHandle, u32Event)?Application_Success:Application_Failure;
}