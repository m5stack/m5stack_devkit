/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "multi_button.h"

struct Button btn1;
struct Button btn2;

uint8_t read_button1_GPIO() 
{
	return (uint8_t)gpio_get_level(GPIO_NUM_39);
}

uint8_t read_button2_GPIO() 
{
	return (uint8_t)gpio_get_level(GPIO_NUM_38);
}


void BTN1_PRESS_DOWN_Handler(void* btn)
{
	//do something...
	printf("BTN1_PRESS_DOWN_Handler\n");
}

void BTN1_PRESS_UP_Handler(void* btn)
{
	//do something...
	printf("BTN1_PRESS_UP_Handler\n");
}

void BTN1_PRESS_REPEAT_Handler(void* btn)
{
	printf("BTN1_PRESS_REPEAT_Handler\n");
}

void BTN1_SINGLE_Click_Handler(void* btn)
{
	printf("BTN1_SINGLE_Click_Handler\n");
}

void BTN1_DOUBLE_Click_Handler(void* btn)
{
	printf("BTN1_DOUBLE_Click_Handler\n");
}

void BTN2_PRESS_DOWN_Handler(void* btn)
{
	//do something...
	printf("BTN2_PRESS_DOWN_Handler\n");
}


void button_test(void *param)
{
	// gpio_config_t gpio_conf;
    // gpio_conf.intr_type = GPIO_INTR_ANYEDGE;
    // gpio_conf.mode = GPIO_MODE_INPUT;
    // gpio_conf.pin_bit_mask = (1 << 39);
    // gpio_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    // gpio_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    // gpio_config(&gpio_conf);
	gpio_set_direction(GPIO_NUM_39, GPIO_MODE_INPUT);
	gpio_set_direction(GPIO_NUM_38, GPIO_MODE_INPUT);

	button_init(&btn1, read_button1_GPIO, 0);
	button_init(&btn2, read_button2_GPIO, 0);
	
	// button_attach(&btn1, PRESS_DOWN,       BTN1_PRESS_DOWN_Handler);
	// button_attach(&btn1, PRESS_UP,         BTN1_PRESS_UP_Handler);
	button_attach(&btn1, PRESS_REPEAT,     BTN1_PRESS_REPEAT_Handler);
	button_attach(&btn1, SINGLE_CLICK,     BTN1_SINGLE_Click_Handler);
	button_attach(&btn1, DOUBLE_CLICK,     BTN1_DOUBLE_Click_Handler);
	// button_attach(&btn1, LONG_RRESS_START, BTN1_LONG_RRESS_START_Handler);
	// button_attach(&btn1, LONG_PRESS_HOLD,  BTN1_LONG_PRESS_HOLD_Handler);
	
	button_attach(&btn2, PRESS_DOWN,       BTN2_PRESS_DOWN_Handler);
	// button_attach(&btn2, PRESS_UP,         BTN2_PRESS_UP_Handler);
	// button_attach(&btn2, PRESS_REPEAT,     BTN2_PRESS_REPEAT_Handler);
	// button_attach(&btn2, SINGLE_CLICK,     BTN2_SINGLE_Click_Handler);
	// button_attach(&btn2, DOUBLE_CLICK,     BTN2_DOUBLE_Click_Handler);
	// button_attach(&btn2, LONG_RRESS_START, BTN2_LONG_RRESS_START_Handler);
	// button_attach(&btn2, LONG_PRESS_HOLD,  BTN2_LONG_PRESS_HOLD_Handler);
	
	button_start(&btn1);
	button_start(&btn2);
	
	//make the timer invoking the button_ticks() interval 5ms.
	//This function is implemented by yourself.
	// __timer_start(button_ticks, 0, 5); 
	
	while(1) 
	{
		button_ticks();
		vTaskDelay(10 / portTICK_PERIOD_MS);
	}
}



void app_main()
{
    xTaskCreate(&button_test, "button_test", 4096, NULL, 5, NULL);
}
