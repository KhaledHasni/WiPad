#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "nrf_sdh.h"
#include "nrf_sdh_ble.h"
#include "ble_gap.h"
#include "nrf_ble_gatt.h"

static TaskHandle_t pvBLETaskHandle;
static EventGroupHandle_t pvBLEEventGroupHandle;

#define WIPAD_MOCK_EVENT (1 << 0)
NRF_BLE_GATT_DEF(m_gatt); 

static void EventHandle(ble_evt_t const * p_ble_evt, void * p_context)
{

}

static void vidBLE_Task_Function(void *pvParam)
{
    EventBits_t u32Event = 0;
    uint32_t ram_start = 0;
    ble_gap_conn_sec_mode_t sec_mode;
    ble_gap_conn_params_t gap_conn_params;

    nrf_sdh_enable_request();
    nrf_sdh_ble_default_cfg_set(1, &ram_start);
    nrf_sdh_ble_enable(&ram_start);
    NRF_SDH_BLE_OBSERVER(nrfObserver, 3, EventHandle, NULL);

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&sec_mode);
    sd_ble_gap_device_name_set(&sec_mode, (const uint8_t *)"Nordic_HRM", strlen("Nordic_HRM") );
    sd_ble_gap_appearance_set(833);

    memset(&gap_conn_params, 0, sizeof(gap_conn_params));
    sd_ble_gap_ppcp_set(&gap_conn_params);

    nrf_ble_gatt_init(&m_gatt, NULL);

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
