#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "nrf_sdh.h"
#include "nrf_sdh_ble.h"
#include "ble_gap.h"
#include "nrf_ble_gatt.h"
#include "ble_advertising.h"
#include "ble_conn_params.h"

static TaskHandle_t pvBLETaskHandle;
static TaskHandle_t m_softdevice_task;


NRF_BLE_GATT_DEF(m_gatt); 
BLE_ADVERTISING_DEF(m_advertising);

static void EventHandle(ble_evt_t const * p_ble_evt, void * p_context)
{

}

void SD_EVT_IRQHandler(void)
{
    BaseType_t yield_req = pdFALSE;

    vTaskNotifyGiveFromISR(m_softdevice_task, &yield_req);

    /* Switch the task if required. */
    portYIELD_FROM_ISR(yield_req);
}

static void vidBLE_Task_Function(void *pvParam)
{
    uint32_t ram_start = 0;
    ble_gap_conn_sec_mode_t sec_mode;
    ble_gap_conn_params_t gap_conn_params;
    ble_advertising_init_t init;
    ble_conn_params_init_t cp_init;

    memset(&init, 0, sizeof(init));
    memset(&cp_init, 0, sizeof(cp_init));

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

    ble_advertising_init(&m_advertising, &init);
    ble_advertising_conn_cfg_tag_set(&m_advertising, 1);

    ble_conn_params_init(&cp_init);


    /* Task function's main busy loop */
    while (1)
    {
        /* Pull for synch BLE events */
        nrf_sdh_evts_poll();

        (void) ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    }
}

void BLE_Service_Init(void)
{

    /* Create task for BLE service */
    xTaskCreate(vidBLE_Task_Function, "Task0", 256, NULL, 2, &pvBLETaskHandle);

}
