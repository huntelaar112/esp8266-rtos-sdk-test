/* Hello World Example
   This example code is in the Public Domain (or CC0 licensed, at your option.)
   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/portmacro.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"

#include "esp_system.h"
#include "esp_spi_flash.h"

static const char *TAG="APP";
#define BUILTIN_LED GPIO_NUM_2

void blink_task(void* params) {
	while(1){
	    ESP_LOGI(TAG, "Blinking ...");
		gpio_set_level(BUILTIN_LED, 0);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
		gpio_set_level(BUILTIN_LED, 1);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void app_init() {
   gpio_config_t conf = {
		   .pin_bit_mask = (1 << BUILTIN_LED),
		   .mode = GPIO_MODE_DEF_OUTPUT,
		   .pull_up_en = GPIO_PULLUP_DISABLE,
		   .pull_down_en = GPIO_PULLDOWN_ENABLE,
		   .intr_type = GPIO_INTR_DISABLE
   };
   gpio_config(&conf);
}

void app_main()
{
    ESP_LOGI(TAG, "Blink Application Stated");

    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    ESP_LOGI(TAG, "This is ESP8266 chip with %d CPU cores, WiFi,", chip_info.cores);
    ESP_LOGI(TAG, "silicon revision %d, ", chip_info.revision);
    ESP_LOGI(TAG, "%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    app_init();
    xTaskCreate(&blink_task, "Blink Task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);


}
