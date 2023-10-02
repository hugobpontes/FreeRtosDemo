/*
 * Task250.c
 *
 *  Created on: Sep 30, 2023
 *      Author: hugo
 */

#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"

#include "trice.h"
#include "lwrb/lwrb.h"

#include "Common.h"
#include "Logger.h"

#define WAIT_FOR_250_FLAG_TICKS 300
#define WAIT_FOR_LOGGER_MUTEX_250_TICKS 100
#define TASK_250_DATA_SIZE 2

static uint8_t Task250Data[TASK_250_DATA_SIZE] = {0xC1,0xC2};

static TaskHandle_t hTask250;


void Task250(void* pvParams){

	EventBits_t SetFlags;
	LoggerMsg_t Task250Msg;
	Task250Msg.SenderId = 25;
	Task250Msg.Size = TASK_250_DATA_SIZE;

	while (1){
		TRICE( ID(6661), "INFO: Waiting for Tmr250 flag for %d \n",WAIT_FOR_250_FLAG_TICKS);
		SetFlags =  xEventGroupWaitBits(hEvGrp250_500,kTmr250EvMsk, pdTRUE,pdTRUE,WAIT_FOR_250_FLAG_TICKS );
		if (SetFlags & kTmr250EvMsk){
        	TRICE( ID(1776), "INFO: Received Tmr250 flag, waiting for logger mutex for %d \n",WAIT_FOR_LOGGER_MUTEX_250_TICKS);
        	if( xSemaphoreTake( hLoggerMutex, WAIT_FOR_LOGGER_MUTEX_250_TICKS ) == pdTRUE ){
        	            	TRICE( ID(7736), "INFO: Took logger mutex, writing C1C2 \n");
        	            	lwrb_write(&LogBuffer, Task250Data, TASK_250_DATA_SIZE);
        	            	HAL_Delay(150);
        	            	if (xQueueSend(hLoggerInbox,&Task250Msg,0) == pdFALSE){
        	            		 TRICE( ID(2785), "ERROR: Could not post msg to logger inbox \n");
        	            	}
        	            	TRICE( ID(1058), "INFO: Releasing logger mutex \n");
        	            	xSemaphoreGive(hLoggerMutex);
			} else {
				TRICE( ID(5747), "ERROR: Could not take logger mutex in %d \n",WAIT_FOR_LOGGER_MUTEX_250_TICKS);
			}
		} else {
            TRICE( ID(5437), "ERROR: Did not receive tm250 flag in %d \n",WAIT_FOR_250_FLAG_TICKS);
		}
	}

}



void Task250Init(){
	xTaskCreate(Task250, "Task250", 128, NULL, 3, &hTask250);
}
