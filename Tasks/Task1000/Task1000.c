/*
 * Task1000.c
 *
 *  Created on: Sep 30, 2023
 *      Author: hugo
 */

#include "FreeRTOS.h"
#include "task.h"

#include "trice.h"
#include "timers.h"

static TaskHandle_t hTask1000;

static void Task1000(void* pvParams){
	while (1){
	//	TRICE( ID(4932), "INFO:Task1000 doing stuff\n");
		vTaskDelay(1000);
	}

}

void Task1000Init(){
	if(xTaskCreate(Task1000, "Task1000", 128, NULL, 2, &hTask1000) == pdFAIL){
		TRICE( ID(2790), "Failed to create task 1000 \n");
	}
}
