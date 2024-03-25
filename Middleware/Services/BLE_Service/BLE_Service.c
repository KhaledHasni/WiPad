/* -----------------------------   BLE Service for nRF51422   ---------------------------------- */
/*  File      -  BLE Service source file                                                         */
/*  target    -  nRF51422                                                                        */
/*  toolchain -  IAR                                                                             */
/*  created   -  March, 2024                                                                     */
/* --------------------------------------------------------------------------------------------- */

/****************************************   INCLUDES   *******************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "BLE_Service.h"
#include "softdevice_handler.h"

/************************************   PRIVATE VARIABLES   **************************************/
static TaskHandle_t pvBleTaskHandle;
static SemaphoreHandle_t pvBleSemaphoreHandle;

/************************************   PRIVATE FUNCTIONS   **************************************/
static void vidBleTaskFunction(void *pvArg)
{
    BaseType_t lSemaphoreAvailable;

    /* Ble task's main loop */
    while(1)
    {
        /* Wait for event from SoftDevice */
        lSemaphoreAvailable = xSemaphoreTake(pvBleSemaphoreHandle, portMAX_DELAY);

        if(pdTRUE == lSemaphoreAvailable)
        {
            /* Process Ble stack incoming events by invoking .............................*/
            intern_softdevice_events_execute();
        }
    }
}

/************************************   PUBLIC FUNCTIONS   ***************************************/
Mid_tenuStatus enuBle_Init(void)
{
    Mid_tenuStatus enuRetVal = Middleware_Failure;

    /* Create task for Ble stack */
    if(pdPASS == xTaskCreate(vidBleTaskFunction,
                             "MID_Ble_Task",
                             MID_BLE_TASK_STACK_SIZE,
                             NULL,
                             MID_BLE_TASK_PRIORITY,
                             &pvBleTaskHandle))
    {
        /* Create synchronization semaphore for Ble task */
        pvBleSemaphoreHandle = xSemaphoreCreateBinary();
        enuRetVal = (NULL != pvBleSemaphoreHandle)?Middleware_Success:Middleware_Failure;
    }

    return enuRetVal;
}