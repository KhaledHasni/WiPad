#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "nrf_drv_clock.h"
#include "BLE_Service.h"
#include "AppMgr.h"

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
    App_tenuStatus enuAppStatus;

    /* Initialize clocks and prepare them for requests */
    nrf_drv_clock_init();

    /* Initialize application tasks */
    enuAppStatus = AppMgr_enuInit();

    /* Initialize Ble stack task */
    Mid_tenuStatus enuMidStatus = enuBle_Init();

    /* Create timer */
    pvTimerHandle = xTimerCreate("Timer0", pdMS_TO_TICKS(1000), pdTRUE, NULL, vidTimerCallback);

    /* Start Timer */
    BaseType_t lErrorCode = xTimerStart(pvTimerHandle, 0);

    /* Start scheduler */
    vTaskStartScheduler();

    /* This loop shouldn't be reached */
    while(1)
    {

    }
}