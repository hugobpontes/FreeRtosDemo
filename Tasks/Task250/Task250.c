/*
 * Task250.c
 *
 *  Created on: Sep 30, 2023
 *      Author: hugo
 */

#include "FreeRTOS.h"
#include "task.h"

#include "trice.h"

static TaskHandle_t hTask250;


static void Task250(void* pvParams){
	while (1){
		TRICE( ID(4714), "INFO:Task250 doing stuff\n");

		vTaskDelay(250);
	}
}


void Task250Init(){
	xTaskCreate(Task250, "Task250", 128, NULL, 2, &hTask250);
}
