
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

static TaskHandle_t pvTaskHandle;
static TimerHandle_t pvTimerHandle;

static void vidTask0_Function(void *pvParam)
{
    /* Set breakpoint here */
    __NOP();

    /* Task function's main busy loop */
    while(1)
    {
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

    /* Create timer */
    pvTimerHandle = xTimerCreate("Timer0", pdMS_TO_TICKS(1000), pdTRUE, NULL, vidTimerCallback);

    /* Start Timer */
    BaseType_t lErrorCode = xTimerStart(pvTimerHandle, 0);

    /* Start Scheduler */
    vTaskStartScheduler();

    /* We should never arrive here  */
    while (1)
    {
    }
}