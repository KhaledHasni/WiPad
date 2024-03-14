
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "timers.h"

#include "BLE_Service.h"

#define WIPAD_MOCK_EVENT (1 << 0)

static TaskHandle_t pvTaskHandle;
static EventGroupHandle_t pvEventGroupHandle;
static TimerHandle_t pvTimerHandle;

static void vidTask0_Function(void *pvParam)
{
    EventBits_t u32Event = 0;

    /* Task function's main busy loop */
    while (1)
    {
        /* Pull for synch events set in event group */
        u32Event = xEventGroupWaitBits(pvEventGroupHandle, WIPAD_MOCK_EVENT, pdTRUE, pdTRUE, portMAX_DELAY);

        if (u32Event)
        {
            __NOP();
        }
    }
}

static void vidTimerCallback(TimerHandle_t pvTimerHandle)
{
    __NOP();
}

int main(void)
{
    /* Create generic task */
    xTaskCreate(vidTask0_Function, "Task0", 256, NULL, 2, &pvTaskHandle);

    /* Create event group */
    pvEventGroupHandle = xEventGroupCreate();

    /* Create timer */
    pvTimerHandle = xTimerCreate("Timer0", pdMS_TO_TICKS(1000), pdTRUE, NULL, vidTimerCallback);

    /* Call BLE_Service_Init */
    BLE_Service_Init();

    /* Start Timer */
    BaseType_t lErrorCode = xTimerStart(pvTimerHandle, 0);

    /* Start Scheduler */
    vTaskStartScheduler();

    /* We should never arrive here  */
    while (1)
    {
    }
}