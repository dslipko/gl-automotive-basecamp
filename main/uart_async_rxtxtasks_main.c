
#include "driver/gpio.h"
#include "driver/uart.h"
#include "esp_log.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl.h"
#include "lvgl_output.c"
#include "string.h"

static const int RX_BUF_SIZE = 1024;
extern char* output;

#define TXD_PIN (GPIO_NUM_17)
#define RXD_PIN (GPIO_NUM_16)

void init(void) {
  const uart_config_t uart_config = {
      .baud_rate = 115200,
      .data_bits = UART_DATA_8_BITS,
      .parity = UART_PARITY_DISABLE,
      .stop_bits = UART_STOP_BITS_1,
      .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
      .source_clk = UART_SCLK_APB,
  };
  // We won't use a buffer for sending data.
  uart_driver_install(UART_NUM_2, RX_BUF_SIZE * 2, 0, 0, NULL, 0);
  uart_param_config(UART_NUM_2, &uart_config);
  uart_set_pin(UART_NUM_2, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE,
               UART_PIN_NO_CHANGE);
}

int sendData(const char* logName, const char* data) {
  const int len = strlen(data);
  const int txBytes = uart_write_bytes(UART_NUM_2, data, len);
  ESP_LOGI(logName, "Wrote %d bytes", txBytes);
  return txBytes;
}

static void tx_task(void* arg) {
  static const char* TX_TASK_TAG = "TX_TASK";
  esp_log_level_set(TX_TASK_TAG, ESP_LOG_INFO);
  while (1) {
    sendData(TX_TASK_TAG, " Hello world !");
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

static void rx_task(void* arg) {
  static const char* RX_TASK_TAG = "RX_TASK";
  esp_log_level_set(RX_TASK_TAG, ESP_LOG_INFO);
  char* data = (char*)malloc(RX_BUF_SIZE + 1);

  while (1) {
    const int rxBytes =
        uart_read_bytes(UART_NUM_2, data, RX_BUF_SIZE, 1000 / portTICK_RATE_MS);
    if (rxBytes > 0) {
      data[rxBytes] = 0;
      output = data;

      ESP_LOGI(RX_TASK_TAG, "Read %d bytes: '%s'", rxBytes, data);
      ESP_LOG_BUFFER_HEXDUMP(RX_TASK_TAG, data, rxBytes, ESP_LOG_INFO);
    }
  }
  free(data);
}

void app_main(void) {
  init();

  xTaskCreatePinnedToCore(rx_task,        /* Function to implement the task */
                          "uart_rx_task", /* Name of the task */
                          1024 * 2,       /* Stack size in words */
                          NULL,           /* Task input parameter */
                          configMAX_PRIORITIES - 2, /* Priority of the task */
                          NULL,                     /* Task handle. */
                          0 /* Core where the task should run */
  );

  xTaskCreatePinnedToCore(tx_task,        /* Function to implement the task */
                          "uart_tx_task", /* Name of the task */
                          1024 * 2,       /* Stack size in words */
                          NULL,           /* Task input parameter */
                          configMAX_PRIORITIES - 1, /* Priority of the task */
                          NULL,                     /* Task handle. */
                          1 /* Core where the task should run */
  );

  xTaskCreatePinnedToCore(guiTask,    /* Function to implement the task */
                          "gui_task", /* Name of the task */
                          4092 * 2,   /* Stack size in words */
                          NULL,       /* Task input parameter */
                          configMAX_PRIORITIES, /* Priority of the task */
                          NULL,                 /* Task handle. */
                          0 /* Core where the task should run */
  );

}
