#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"

static TaskHandle_t pvBLETaskHandle;
static EventGroupHandle_t pvBLEEventGroupHandle;

#define WIPAD_MOCK_EVENT (1 << 0)

static void vidBLE_Task_Function(void *pvParam)
{
    EventBits_t u32Event = 0;

    /* Task function's main busy loop */
    while (1)
    {
        /* Pull for synch events set in event group */
        u32Event = xEventGroupWaitBits(pvBLEEventGroupHandle, WIPAD_MOCK_EVENT, pdTRUE, pdTRUE, portMAX_DELAY);

        if (u32Event)
        {
            __NOP();
        }
    }
}

void BLE_Service_Init(void)
{

    /* Create task for BLE service */
    xTaskCreate(vidBLE_Task_Function, "Task0", 256, NULL, 2, &pvBLETaskHandle);
    pvBLEEventGroupHandle = xEventGroupCreate();
}
