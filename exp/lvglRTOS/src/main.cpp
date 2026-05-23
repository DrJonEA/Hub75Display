#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"


extern "C"{
#include "lv_port_disp.h"
}

#include "Widgets.h"
#include <FreeRTOS.h>
#include <task.h>
#include "WifiHelper.h"

#define TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )



void main_task(void* params){
	for (;;){
		vTaskDelay(3000);
		//printf("Tick\n");
	}
}

void lvgl_task(void* params){
	Widgets widgets;

	lv_tick_set_cb(xTaskGetTickCount);
	widgets.init();
	for(;;){
	  for (int i=0; i < 100; i++){
		  lv_timer_handler();
		 vTaskDelay(1);
	  }
	  //printf("Tick\n");
	}
}

void wifi_task(void* params){

	WifiHelper::init();

	WifiHelper::sntpAddServer("uk.pool.ntp.org");
	WifiHelper::sntpAddServer("ntp.my-inbox.co.uk");
	WifiHelper::sntpAddServer("ntp.virginmedia.com");

	for (;;){
		//runTimeStats();
		if (! WifiHelper::isJoined()){
			if(WifiHelper::join(WIFI_SSID,  WIFI_PASSWORD)){
				printf("Connected to network %s\n", WIFI_SSID);
				WifiHelper::sntpStartSync();
			} else {
				printf("Failed to Connect to network %s\n", WIFI_SSID);
			}
		}

		vTaskDelay(1000);
	}

}


int main() {

	stdio_init_all();
	sleep_ms(3000);
	printf("Go\n");

	lv_init();
	lv_port_disp_init();

	TaskHandle_t mainTask,  lvglTask;

	xTaskCreate(main_task, "MainThread", 1024*4, NULL, TASK_PRIORITY, &mainTask);
	xTaskCreate(lvgl_task, "LVGLThread", 1024*2, NULL, TASK_PRIORITY, &lvglTask);
	xTaskCreate(wifi_task, "WifiThread", 1024, NULL, TASK_PRIORITY, &lvglTask);

	vTaskStartScheduler();

	for (;;){

	}

}
