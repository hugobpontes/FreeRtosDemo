/*
 * Task500.c
 *
 *  Created on: Sep 30, 2023
 *      Author: hugo
 */

#include "FreeRTOS.h"
#include "task.h"

#include "trice.h"

static TaskHandle_t hTask500;


void Task500(void* pvParams){
	while (1){
		TRICE( ID(7393), "INFO:Task500 doing stuff\n");
		vTaskDelay(500);
	}

}


void Task500Init(){
	xTaskCreate(Task500, "Task500", 128, NULL, 2, &hTask500);
}
