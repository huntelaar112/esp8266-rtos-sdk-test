/* gpio example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "driver/gpio.h"

#include "esp_log.h"
#include "esp_system.h"


#define GPIO_OUTPUT_IO_0    5
#define GPIO_OUTPUT_IO_1    16
#define GPIO_OUTPUT_PIN_SEL  ((1ULL<<GPIO_OUTPUT_IO_0) | (1ULL<<GPIO_OUTPUT_IO_1))
#define GPIO_INPUT_IO_0     4
#define GPIO_INPUT_IO_1     5
#define GPIO_INPUT_PIN_SEL  ((1ULL<<GPIO_INPUT_IO_0) | (1ULL<<GPIO_INPUT_IO_1))


void TaskBlink1( void *pvParameters );
void TaskBlink2( void *pvParameters );
void Taskprint( void *pvParameters );

int app_main(){
	xTaskCreate(TaskBlink1, "task1", 128, NULL, 1, NULL);
	xTaskCreate(TaskBlink2, "task2", 128, NULL, 1, NULL);
	xTaskCreate(Taskprint, "task3", 128, NULL, 1, NULL);
	vTaskStartScheduler();

	gpio_config_t io_conf;
	//disable interrupt
	io_conf.intr_type = GPIO_INTR_DISABLE;
	//set as output mode
	io_conf.mode = GPIO_MODE_OUTPUT;
	//bit mask of the pins that you want to set,e.g.GPIO15/16
	io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
	//disable pull-down mode
	io_conf.pull_down_en = 0;
	//disable pull-up mode
	io_conf.pull_up_en = 0;
	//configure GPIO with the given settings
	gpio_config(&io_conf);

	while(1){
		;
	}

	return 0;
}

void TaskBlink1(void *pvParameters)  {
	while(1){
		printf("Task1");
		gpio_set_level(GPIO_OUTPUT_IO_1, 1);
		vTaskDelay( 2000 / portTICK_PERIOD_MS );
		gpio_set_level(GPIO_OUTPUT_IO_1, 0);
		vTaskDelay( 2000 / portTICK_PERIOD_MS );
	}
}

void TaskBlink2(void *pvParameters){
	while(1){
		printf("Task2");
		gpio_set_level(GPIO_OUTPUT_IO_0, 1);
		vTaskDelay( 1000 / portTICK_PERIOD_MS );
		gpio_set_level(GPIO_OUTPUT_IO_0, 0);
		vTaskDelay( 1000 / portTICK_PERIOD_MS );
	}
}

void Taskprint(void *pvParameters)  {
	int counter = 0;
	while(1){
		counter++;
		printf("%d", counter);
		vTaskDelay(500 / portTICK_PERIOD_MS);
	}
}




