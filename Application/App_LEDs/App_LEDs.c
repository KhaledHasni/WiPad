#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "nrf_gpio.h"
#include "App_LEDs.h"

static TimerHandle_t pvAppLedsTimerHandle;
static TaskHandle_t pvAppLedsTaskHandle;
static QueueHandle_t pvAppLedsQueueHandle;

uint32_t u32DummyMsg = 1;
uint32_t u32DummyReceive;
volatile uint8_t u8ExpirationCount = 0;

static void vidLeds_Control(uint32_t u32Value1, uint32_t u32Value2, uint32_t u32Value3, uint32_t u32Value4)
{
  nrf_gpio_pin_write(APP_LED_1, u32Value1);
  nrf_gpio_pin_write(APP_LED_2, u32Value2);
  nrf_gpio_pin_write(APP_LED_3, u32Value3);
  nrf_gpio_pin_write(APP_LED_4, u32Value4);
}

static void vidApp_Leds_Task_Function(void *pvParam)
{
    /* unused parameter */
    (void) pvParam;

    /* Start Timer */
    BaseType_t lErrorCode = xTimerStart(pvAppLedsTimerHandle, APP_LEDs_TIMER_TICKS_TO_WAIT);

    /* Task function's main loop */
    while(1)
    {
        /* Task delay until message received */
        xQueueReceive(pvAppLedsQueueHandle, &(u32DummyReceive), portMAX_DELAY);
    }
}

static void vidAppLedsTimerCallback(TimerHandle_t pvTimerHandle)
{
    if(pvTimerHandle != NULL)
    {
        switch (u8ExpirationCount)
        {
        case 0:
        {
            u8ExpirationCount++;
            /* Turn LED1 on */
            vidLeds_Control(APP_LED_SWITCH_ON, APP_LED_SWITCH_OFF, APP_LED_SWITCH_OFF, APP_LED_SWITCH_OFF);
            /* Push message to queue */
            xQueueSend(pvAppLedsQueueHandle, (void *) &u32DummyMsg, (TickType_t) APP_LEDs_QUEUE_TICKS_TO_WAIT);
        }
        break;

        case 1:
        {
            u8ExpirationCount++;
            /* Turn LED2 on*/
            vidLeds_Control(APP_LED_SWITCH_OFF, APP_LED_SWITCH_ON, APP_LED_SWITCH_OFF, APP_LED_SWITCH_OFF);
            /* Send queue to task */
            xQueueSend(pvAppLedsQueueHandle, (void *) &u32DummyMsg, (TickType_t) APP_LEDs_QUEUE_TICKS_TO_WAIT);
        }
        break;

        case 2:
        {
            u8ExpirationCount++;
            /* Turn LED4 on*/
            vidLeds_Control(APP_LED_SWITCH_OFF, APP_LED_SWITCH_OFF, APP_LED_SWITCH_OFF, APP_LED_SWITCH_ON);
            /* Send queue to task */
            xQueueSend(pvAppLedsQueueHandle, (void *) &u32DummyMsg, (TickType_t) APP_LEDs_QUEUE_TICKS_TO_WAIT);
        }
        break;

        case 3:
        {
            u8ExpirationCount = 0;
            /* Turn LED3 on*/
            vidLeds_Control(APP_LED_SWITCH_OFF, APP_LED_SWITCH_OFF, APP_LED_SWITCH_ON, APP_LED_SWITCH_OFF);
            /* Send queue to task */
            xQueueSend(pvAppLedsQueueHandle, (void *) &u32DummyMsg, (TickType_t) APP_LEDs_QUEUE_TICKS_TO_WAIT);
        }
        break;

        default:
        {
            /* Nothing to do */
        }
        break;
        }
    }
}

void vidApp_Leds_Init(void)
{
    /* Configure pins as output */
    nrf_gpio_range_cfg_output(APP_LED_1, APP_LED_4);

    /* Turn all LEDs off */
    vidLeds_Control(APP_LED_SWITCH_OFF, APP_LED_SWITCH_OFF, APP_LED_SWITCH_OFF, APP_LED_SWITCH_OFF);

    /* Create task for LED application */
    xTaskCreate(vidApp_Leds_Task_Function, "APP_LEDs_Task", APP_LEDs_TASK_STACK_SIZE, NULL, APP_LEDs_TASK_PRIORITY, &pvAppLedsTaskHandle);

    /* Create reloading timer every 0.5s */
    pvAppLedsTimerHandle = xTimerCreate("APP_Leds_Timer", pdMS_TO_TICKS(500), pdTRUE, NULL, vidAppLedsTimerCallback);

    /* Create message queue */
    pvAppLedsQueueHandle = xQueueCreate(APP_LEDs_QUEUE_SIZE, sizeof(uint32_t));
}