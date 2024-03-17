#define APP_LED_1                      21
#define APP_LED_2                      22
#define APP_LED_3                      23
#define APP_LED_4                      24
#define APP_LED_SWITCH_ON              0
#define APP_LED_SWITCH_OFF             1
#define APP_LEDs_TASK_STACK_SIZE       256
#define APP_LEDs_TASK_PRIORITY         2
#define APP_LEDs_QUEUE_SIZE            5
#define APP_LEDs_TIMER_TICKS_TO_WAIT   0
#define APP_LEDs_QUEUE_TICKS_TO_WAIT   0


void vidApp_Leds_Init(void);