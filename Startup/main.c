
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

static TimerHandle_t pvTimerHandle;

void vApplicationIdleHook( void )
{
  
}

static void vidTimerCallback( TimerHandle_t xTimer )
{
    __NOP();
}

int main(void)
{
    /* Create timer */
    pvTimerHandle = xTimerCreate("Timer0", pdMS_TO_TICKS(1000), pdTRUE, NULL, vidTimerCallback);

    /* Start Timer */
    BaseType_t lErrorCode = xTimerStart(pvTimerHandle, 0);

    /* Test statement */
    vTaskStartScheduler();
    
    while(1)
    {
      
    }  
}