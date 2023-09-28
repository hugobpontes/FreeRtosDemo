/*
 * TriceTaskCallbacks.c
 *
 *  Created on: Sep 28, 2023
 *      Author: hugo
 */
#include "trice.h"

#include "FreeRTOS.h"
#include "task.h"

void TriceTaskSwitchIn(TaskHandle_t CurrentTaskHandle){
	TaskStatus_t CurrentTaskStatus;
	vTaskGetInfo(CurrentTaskHandle,&CurrentTaskStatus, pdFALSE, eBlocked);
	TRICE( ID(5302), "Entering Task [%d]\n",CurrentTaskStatus.xTaskNumber);
}
