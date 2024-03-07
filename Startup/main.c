
#include "FreeRTOS.h"
#include "task.h"

static TaskHandle_t pvTaskHandle;

static void vidTask0_Function(void *pvParam)
{
    /* Set breakpoint here */
    __NOP();

    /* Task function's main busy loop */
    while(1)
    {

    }
}

int main(void)
{
    /* Create generic task */
    xTaskCreate(vidTask0_Function, "Task0", 256, NULL, 2, &pvTaskHandle);

    /* Start Scheduler */
    vTaskStartScheduler();

    /* We should never arrive here  */
    while (1)
    {
    }
}